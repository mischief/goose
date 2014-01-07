// monitor.h -- Defines the interface for monitor.h
// From JamesM's kernel development tutorials.

#ifndef MONITOR_H
#define MONITOR_H

// Write a single character out to the screen.
void monitor_put(char c) __asm__ (GOSYM_PREFIX "runtime.MonitorPut");

// Clear the screen to all black.
void monitor_clear() __asm__ (GOSYM_PREFIX "runtime.MonitorClear");

// Output a null-terminated ASCII string to the monitor.
void monitor_write(char *s);

// write Go String
void monitor_string(String s) __asm__ (GOSYM_PREFIX "runtime.MonitorString");

#endif // MONITOR_H
