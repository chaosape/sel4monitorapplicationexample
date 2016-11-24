#include <stdbool.h>
#include <msgtype.h>
#include <stdio.h>

bool enqueue(msg_t * m) {
  return false;
}

bool dequeue(msg_t m) {
  return false;
}


int post_init() {
  printf("Monitor started.\n");
  return 0;
}

