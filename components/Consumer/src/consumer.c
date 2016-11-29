#include <camkes.h>
#include <stdio.h>

static void qd_handler(void* unused) {
  static int fired = 0;
  printf("consumer:qd_handler: received QueueData event.\n");
  if (!fired) {
    fired = 1;
    qd_reg_callback(&qd_handler, NULL);
  }
}

void pre_init(void) {
  qd_reg_callback(&qd_handler, NULL);
}

int run(void) {
  return 0;
}
