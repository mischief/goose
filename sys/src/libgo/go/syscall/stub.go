package syscall

const (
	O_RDONLY = 0x0
	O_WRONLY = 0x1
	O_RDWR   = 0x2
	O_APPEND = 0x8
	O_CREAT  = 0x200
	O_EXCL   = 0x800
	O_SYNC   = 0x80
	O_TRUNC  = 0x400
)

var (
    Envs []string
)

func Getenv(s string) (string, error) {
	return "", ENOTIMPL
}

func Setenv(key, value string) error {
	return ENOTIMPL
}

func Clearenv() {
}

func Environ() []string {
	return nil
}

func Getpagesize() int {
	return 0x1000
}
