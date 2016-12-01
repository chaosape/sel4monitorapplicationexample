#include <camkes.h>
#include <stdio.h>
#include <msgtype.h>

static void qd_handler(void* unused) {
  static int fired = 0;
  printf("consumer:qd_handler: received QueueData event.\n");
  qd_sem_post();
  if (!fired) {
    fired = 1;
    qd_reg_callback(&qd_handler, NULL);
  }
  dispatch_sem_post();
}

void pre_init(void) {
  qd_reg_callback(&qd_handler, NULL);
  dispatch_sem_wait();
  qd_sem_wait();

}

int run(void) {
  while(1) {
    dispatch_sem_wait();
    printf("consumer:run: dispatch initiated.\n");
    if(qd_sem_trywait()==0) {
      msg_t m;
      mon_dequeue(&m);
      printf("consumer:run: dequeued message %u.\n",m.data);
    }
    printf("consumer:run: dispatch completed.\n");
  }
  return 0;
}
