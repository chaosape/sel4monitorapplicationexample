#include <stdio.h>
#include <msgtype.h>
#include <unistd.h>

void run(void) {
  msg_t m;
  m.data = 0;
//  while(1) {
    m.data++;
    printf("producer:run: sending message %u.\n",m.data);  
    mon_enqueue(&m);
//    sleep(1);
//  }
}
