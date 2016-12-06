#include <stdio.h>
#include <msgtype.h>
#include <unistd.h>

void run(void) {
  msg_t m;
  int c;
  m.data = 0;
  while(m.data<100) {
    m.data++;

    printf("producer:run: attempting to send(1) message %u ... ",m.data);  
    if(mon1_enqueue(&m)) {
      printf("successful!\n");  
    } else {
      printf("failure!\n");  
    }

    printf("producer:run: attempting to send(2) message %u ... ",m.data);  
    if(mon2_enqueue(&m)) {
      printf("successful!\n");  
    } else {
      printf("failure!\n");  
    }

    for(c=0;c<1000000;c++){}
  }
}
