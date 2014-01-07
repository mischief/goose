// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Process etc.

package os

import "runtime"

// Args hold the command-line arguments, starting with the program name.
var Args []string

// Getuid returns the numeric user id of the caller.
func Getuid() int { return 0 }

// Geteuid returns the numeric effective user id of the caller.
func Geteuid() int { return 0 }

// Getgid returns the numeric group id of the caller.
func Getgid() int { return 0 }

// Getegid returns the numeric effective group id of the caller.
func Getegid() int { return 0 }

// Getgroups returns a list of the numeric ids of groups that the caller belongs to.
func Getgroups() ([]int, error) {
	return []int{0}, nil
	/*
		gids, e := syscall.Getgroups()
		return gids, NewSyscallError("getgroups", e)
	*/
}

// Exit causes the current program to exit with the given status code.
// Conventionally, code zero indicates success, non-zero an error.
// The program terminates immediately; deferred functions are
// not run.
func Exit(code int) { runtime.Exit(code) }
