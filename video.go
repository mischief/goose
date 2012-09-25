package video

var x, y int
var vidmem *[80][24][2]byte

func Print(line string) {
	for _, c := range line {
		PutChar(c)	
	}
}

func PutChar(c rune) {
	if c == '\n' {
		x = 0
		y++ 
	} else {
		vidmem[x][y][0] = byte(c)
		vidmem[x][y][1] = 0x07
		x++
		if x > 24 {
			x = 0
			y++
		}
	}
	// todo: no scrolling support
}

func Clear() {
	for i := 0; i < 80; i++ {
		for j := 0; j < 25; j++ {
			vidmem[i][j][0] = 0
			vidmem[i][j][1] = 0
		}
	}
	x = 0
	y = 0
}
