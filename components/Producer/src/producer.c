#include <stdio.h>
#include <msgtype.h>
#include <unistd.h>

void run(void) {
  msg_t m;
  m.data = 0;
  while(m.data<100) {
    m.data++;
    printf("producer:run: attempting to send message %u ... ",m.data);  
    if(mon_enqueue(&m)) {
      printf("successful!\n");  
    } else {
      printf("failure!\n");  
    }
    int c = 0;
    for(;c<1000000;c++){}
  }
}
