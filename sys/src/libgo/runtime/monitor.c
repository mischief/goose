#include "runtime.h"
#include "go-string.h"
#include "monitor.h"

static short *video_memory = (short*) 0xB8000;
static uint16 cursor_x = 0;
static uint16 cursor_y = 0;
// Updates the hardware cursor.
static void
move_cursor(void)
{
  // The screen is 80 characters wide...
  u16int cursorLocation = cursor_y * 80 + cursor_x;
  outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
  outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
  outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
  outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}

// Scrolls the text on the screen up by one line.
static void
scroll()
{
  // Get a space character with the default colour attributes.
  u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
  u16int blank = 0x20 /* space */ | (attributeByte << 8);

  // Row 25 is the end, this means we need to scroll up
  if(cursor_y >= 25) {
    // Move the current text chunk that makes up the screen
    // back in the buffer by a line
    int i;
    for (i = 0*80; i < 24*80; i++) {
      video_memory[i] = video_memory[i+80];
    }

    // The last line should now be blank. Do this by writing
    // 80 spaces to it.
    for (i = 24*80; i < 25*80; i++) {
      video_memory[i] = blank;
    }
    // The cursor should now be on the last line.
    cursor_y = 24;
  }
}

// Writes a single character out to the screen.
void
monitor_put(char c)
{
  // The background colour is black (0), the foreground is white (15).
  u8int backColour = 0;
  u8int foreColour = 15;

  // The attribute byte is made up of two nibbles - the lower being the
  // foreground colour, and the upper the background colour.
  u8int  attributeByte = (backColour << 4) | (foreColour & 0x0F);
  // The attribute byte is the top 8 bits of the word we have to send to the
  // VGA board.
  u16int attribute = attributeByte << 8;
  u16int *location;

  // Handle a backspace, by moving the cursor back one space
  if (c == 0x08 && cursor_x) {
    cursor_x--;
  }

  // Handle a tab by increasing the cursor's X, but only to a point
  // where it is divisible by 8.
  else if (c == 0x09) {
    cursor_x = (cursor_x+8) & ~(8-1);
  }

  // Handle carriage return
  else if (c == '\r') {
    cursor_x = 0;
  }

  // Handle newline by moving cursor back to left and increasing the row
  else if (c == '\n') {
    cursor_x = 0;
    cursor_y++;
  }
  // Handle any other printable character.
  else if(c >= ' ') {
    location = (uint16*) video_memory + (cursor_y*80 + cursor_x);
    *location = c | attribute;
     cursor_x++;
  }

  // Check if we need to insert a new line because we have reached the end
  // of the screen.
  if (cursor_x >= 80) {
    cursor_x = 0;
    cursor_y ++;
  }

  // Scroll the screen if needed.
  if(cursor_y >= 25) {
    scroll();
  }
  // Move the hardware cursor.
  move_cursor();
}

//void monitor_clear() __asm__ (GOSYM_PREFIX "runtime.MonitorClear");

// Clears the screen, by copying lots of spaces to the framebuffer.
void
monitor_clear()
{
   // Make an attribute byte for the default colours
   u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   u16int blank = 0x20 /* space */ | (attributeByte << 8);

   int i;
   for (i = 0; i < 80*25; i++)
   {
       video_memory[i] = blank;
   }

   // Move the hardware cursor back to the start.
   cursor_x = 0;
   cursor_y = 0;
   move_cursor();
}

// Outputs a null-terminated ASCII string to the monitor.
void
monitor_write(char *c)
{
  int i = 0;
  while (c[i]) {
    monitor_put(c[i++]);
  }
}

void monitor_string(String s) __asm__ (GOSYM_PREFIX "runtime.MonitorString");

void
monitor_string(String s)
{
  int i;
  for(i = 0; i < s.len; i++) {
    monitor_put(s.str[i]);
  }
}

/*
type VGA struct {
	x, y int
	attr byte
	mem  *[25][80][2]byte
}

func (v *VGA) WriteByte(c byte) {
	if c == 0x08 && v.x > 0 {
		v.x--
	} else if c == 0x09 {
		v.x = (v.x + 8) & ^(8 - 1)
	} else if c == '\r' {
		v.x = 0
	} else if c == '\n' {
		v.x = 0
		v.y++
	} else if c >= ' ' {
		v.mem[v.y][v.x][0] = c
		v.mem[v.y][v.x][1] = v.attr
		v.x++
	}

	if v.x > 80 {
		v.x = 0
		v.y++
	}

	v.scroll()
	v.movecursor()
}

func (v *VGA) movecursor() {
	var loc uint16
	loc = uint16(v.y*80 + v.x)

	outb(0x3D4, 14)
	outb(0x3D5, uint8(loc>>8))
	outb(0x3D4, 15)
	outb(0x3D5, uint8(loc))
}

func (v *VGA) scroll() {
	var attr uint8

	attr = (0 << 4) | (15 & 0x0F)

	if v.y >= 25 {
		for y := 0; y < 24; y++ {
			for x := 0; x < 80; x++ {
				v.mem[y][x][0] = v.mem[y+1][x][0]
				v.mem[y][x][1] = v.mem[y+1][x][1]
			}
		}

		for y := 24; y < 25; y++ {
			for x := 0; x < 80; x++ {
				v.mem[y][x][0] = ' '
				v.mem[y][x][1] = attr
			}
		}

		v.y = 24
	}
}

func (v *VGA) Write(p []byte) (int, error) {
	for i := 0; i < len(p); i++ {
		v.WriteByte(p[i])
	}

	return len(p), nil
}

func (v *VGA) Line(l string) {
	for i := 0; i < len(l); i++ {
		v.WriteByte(l[i])
	}
}

func (v *VGA) Clear() {
	for i := 0; i < 80; i++ {
		for j := 0; j < 25; j++ {
			v.mem[j][i][0] = 0
			v.mem[j][i][1] = 0
		}
	}
	v.x = 0
	v.y = 0

	v.movecursor()
}

var itoabuf [32]byte

func (v *VGA) Number(val uint32, base uint32) {
	i := 30
	chars := "0123456789abcdef"

	for i := 0; i < len(itoabuf); i++ {
		itoabuf[i] = 0
	}

	for val > 0 && i > 0 {
		itoabuf[i] = chars[val%base]
		i--
		val /= base
	}

	for _, r := range itoabuf {
		if r != 0 {
			v.WriteByte(r)
		}
	}
}

var (
	V VGA
)

func Init() {
	V = VGA{
		attr: (0 << 4) | (15 & 0x0F),
		mem: getAddr(0xB8000),
	}

	V.Clear()
	V.Line("video..\n")
}

func Line(s string) {
  V.Line(s)
}
*/
