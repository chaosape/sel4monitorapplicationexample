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
    printf("monitor:mon_dequeue: Failed to dequeue.\n");
    return false;
  } else {
    *m = contents[front];
    printf("monitor:mon_dequeue: dequeued message %u.\n",m->data);
    front = (front + 1) % 10;
    length--;
    return true;
  }
}

bool mon_enqueue(const msg_t * m) {
  if (is_full()) {
    printf("monitor:mon_enqueue: Failed to queue message %u.\n",m->data);
    return false;
  } else {
    printf("monitor:mon_enqueue: queued message %u.\n",m->data);
    contents[(front + length) % 10] = *m;
    length++;
    printf("monitor:mon_enqueue: sending QueueData event.\n");
    qd_emit();
    return true;
  }
}

void run(void) {}
