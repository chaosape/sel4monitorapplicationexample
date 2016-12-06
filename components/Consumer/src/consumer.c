#include <camkes.h>
#include <stdio.h>
#include <msgtype.h>
#include <stdbool.h>
// Andrew has suggested that by making the q1work and q2work variables
// volatile I can remove the need for mutexes.

// Used to determine which QueueEvent initiated the qd_handler
// callback.
int cb1 = 1;
int cb2 = 2;

// Used to indicate whether there is a potential for work.
bool q1work = false;
bool q2work = false;

static void qd_handler(void * vp) {
  int cb = *((int*)vp);
  printf("consumer:qd_handler: received QueueData(%i) event.\n",cb);
  if(cb == 1) {
    q1work_mut_lock();
    q1work = true;
    q1work_mut_unlock();
    qd1_reg_callback(&qd_handler, &cb1);
  } else if(cb == 2){
    q2work_mut_lock();
    q2work = true;
    q2work_mut_unlock();
    qd2_reg_callback(&qd_handler, &cb2);
  } else {
    printf("consumer:qd_handler: invalid input cb = %i.\n", cb);
    assert(false);
  }

  // The semaphores are counting ones. If we allow this semaphore to
  // increment past one we may end up in a scenario where we dispatch
  // many times yet there is no work to do. The trywait call bounds
  // the maximum semaphore count to one. Doing so should restrict
  // vacuous dispatches to no more than one.
  dispatch_sem_trywait();
  dispatch_sem_post(); }

void pre_init(void) {
  qd1_reg_callback(&qd_handler, &cb1);
  qd2_reg_callback(&qd_handler, &cb2);
}

int run(void) {
  msg_t m;

  // Used to indicate that at least one queue has more work to do.
  bool work;

  while(1) {

    dispatch_sem_wait();
    printf("consumer:run: dispatch initiated.\n");

    // Here we are trying to service queues containing more than one
    // message fairly within a loop. If we were guaranteed to receive
    // a notification for each message queued this would not be
    // necessary. Unfortunately, there is no such guarantee so we must
    // empty queues once dispatched.
    work = true;
    while(work) {

      work = false;

      q1work_mut_lock();
      if(q1work) {
        q1work_mut_unlock();
        if(mon1_dequeue(&m)) {
          // Actual work pertaining to input from monitor 1 goes here.
          printf("consumer:run: dequeued(1) message %u.\n",m.data);
          work = true;
        }
      } else {
        q1work = false;
        q1work_mut_unlock();
      }

      q2work_mut_lock();
      if(q2work) {
        q2work_mut_unlock();
        if(mon2_dequeue(&m)) {
          // Actual work pertaining to input from monitor 2 goes here.
          printf("consumer:run: dequeued(2) message %u.\n",m.data);
          work = true;
        }
      } else {
        q2work = false;
        q2work_mut_unlock();
      }
      
    }
    printf("consumer:run: dispatch completed.\n");
  }
  return 0;
}
