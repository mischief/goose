#ifndef SIGNAL_H
#define SIGNAL_H

typedef struct sigset_t {
  void *unused;
} sigset_t;

typedef struct stack_t {
  void *ss_sp; /* stack ptr */
  void *ss_bp; /* base ptr */
  int ss_size; /* stack size */
  int ss_flags; /* flags */
} stack_t;

#endif
