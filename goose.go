package kernel

var Vidmem *[1024]byte

func Kmain() {
	Vidmem[0] = 65
	Vidmem[1] = 0x7f
}
