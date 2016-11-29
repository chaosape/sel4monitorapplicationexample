#include <stdio.h>
#include <msgtype.h>

void run(void) {
  msg_t m;
  m.data = 1;
  printf("producer:run: sending message %u.\n",m.data);  
  mon_enqueue(&m);
}
