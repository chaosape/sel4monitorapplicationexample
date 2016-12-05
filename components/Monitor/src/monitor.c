#include <stdbool.h>
#include <msgtype.h>
#include <stdio.h>


msg_t contents[10];
uint32_t front = 0;
uint32_t length = 0;

bool is_full(void) {
    return length == 10;
}

bool is_empty(void) {
    return length == 0;
}

bool mon_dequeue(msg_t * m) {
  if (is_empty()) {
    return false;
  } else {
    *m = contents[front];
    front = (front + 1) % 10;
    length--;
    return true;
  }
}

bool mon_enqueue(const msg_t * m) {
  if (is_full()) {
    return false;
  } else {
    contents[(front + length) % 10] = *m;
    length++;
    qd_emit();
    return true;
  }
}
