package main

import (
  "runtime"
	"fmt"
)

//extern outb
func outb(port uint16, value uint8)

type Registers struct {
	ds                                     uint32
	edi, esi, ebp, esp, ebx, edx, ecx, eax uint32
	int_no, err_code                       uint32
	eip, cs, eflags, useresp, ss           uint32
}

func IsrHandler(regs Registers) {
//	fmt.Printf("isr %x:\n", regs.int_no)
  println("isr ", regs.int_no, " error ", regs.err_code)
}

type IrqHandlerFn func(Registers)

var (
	irqhandlers map[uint32]IrqHandlerFn
)

func SetIrqHandler(n uint32, fn IrqHandlerFn) {
	irqhandlers[n] = fn
}

func IrqHandler(regs Registers) {
	if regs.int_no >= 40 {
		outb(0xA0, 0x20)
	}

	outb(0x20, 0x20)

	if fn, ok := irqhandlers[regs.int_no]; ok {
		fn(regs)
	}
}

var (
	tick uint32 = 0
)

func TimerCallback(regs Registers) {
//	fmt.Printf("tick %d\n", tick)
	tick++
}

func init_timer(freq uint32) {
	var div uint32
	var l, h uint8

	SetIrqHandler(32, TimerCallback)

	div = 1193180 / freq

	outb(0x43, 0x36)

	l = uint8(div & 0xFF)
	h = uint8((div >> 8) & 0xFF)

	outb(0x40, l)
	outb(0x40, h)
}

func init() {
	irqhandlers = make(map[uint32]IrqHandlerFn)
	init_timer(50)
}

func main() {
  var stats runtime.MemStats
	fmt.Printf("Hello, x86 world!\n")

  runtime.ReadMemStats(&stats)

  fmt.Printf("Alloc: %d ", stats.Alloc)
  fmt.Printf("TotalAlloc: %d\n", stats.TotalAlloc)
  fmt.Printf("Sys: %d ", stats.Sys)
  fmt.Printf("Lookups: %d\n", stats.Lookups)
  fmt.Printf("Mallocs: %d ", stats.Mallocs)
  fmt.Printf("Frees: %d\n", stats.Frees)
  fmt.Println("")
  fmt.Printf("HeapAlloc: %d ", stats.HeapAlloc)
  fmt.Printf("HeapSys: %d\n", stats.HeapSys)
  fmt.Printf("HeapIdle: %d ", stats.HeapIdle)
  fmt.Printf("HeapInuse: %d\n", stats.HeapInuse)
  fmt.Printf("HeapReleased: %d ", stats.HeapReleased)
  fmt.Printf("HeapObjects: %d\n", stats.HeapObjects)
  fmt.Println("")
  fmt.Printf("StackInuse: %d ", stats.StackInuse)
  fmt.Printf("StackSys: %d\n", stats.StackSys)
  fmt.Printf("MSpanInuse: %d ", stats.MSpanInuse)
  fmt.Printf("MSpanSys: %d\n", stats.MSpanSys)
  fmt.Printf("MCacheInuse: %d ", stats.MCacheInuse)
  fmt.Printf("MCacheSys: %d\n", stats.MCacheSys)
  fmt.Printf("BuckHashSys: %d\n", stats.BuckHashSys)

  go func(){
    for {
      println("cocks\n")
    }
  }()

  select{}

/*
  fmt.Printf("GCSys: %d ", stats.GCSys)
  fmt.Printf("OtherSys: %d\n", stats.OtherSys)
*/
}
