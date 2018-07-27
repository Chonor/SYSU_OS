#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"
static thread_func a_thread_func;
static thread_func b_thread_func;

void
test_priority_donate_lower2 (void) 
{
  struct lock lock;

  /* This test does not work with the MLFQS. */
  ASSERT (!thread_mlfqs);

  /* Make sure our priority is the default. */
  ASSERT (thread_get_priority () == PRI_DEFAULT);

  lock_init (&lock);
  lock_acquire (&lock);
  msg ("Main thread create a thread have priority 30.");
  thread_create ("a", PRI_DEFAULT -1, a_thread_func, &lock);
  msg ("Main thread have priority 31 and sleep 10 ticks.");
  timer_sleep(10);
  msg ("Main thread awake and set the priority = 20.");
  thread_set_priority(20);
  msg ("Main thread should have priority %d.  Actual priority: %d.",
       PRI_DEFAULT -1, thread_get_priority ());
  thread_create ("b", PRI_DEFAULT -6, b_thread_func, NULL);
  msg ("Main thread should have priority %d.  Actual priority: %d.",
       PRI_DEFAULT -1, thread_get_priority ());
  lock_release (&lock);
  msg ("Main thread should have priority %d.  Actual priority: %d.",
       PRI_DEFAULT -11, thread_get_priority ());
  msg("a , b must already have finished.");
}

static void
a_thread_func (void *lock_) 
{
  struct lock *lock = lock_;
  msg("a: begin try acquire lcok and it have priority %d.",thread_get_priority ());
  lock_acquire (lock);
  msg ("a: got the lock.");
  lock_release (lock);
  msg ("a: done.");
}

static void
b_thread_func (void *arg_ UNUSED) 
{
  msg("b: done.");
}
