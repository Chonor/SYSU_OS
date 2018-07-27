/* Tests timer_sleep(0), which should return immediately. */

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

static thread_func lock_fun;
static thread_func PV_fun;
static int64_t wake_time;
static struct semaphore wait_sema;
static struct lock locks;
void
test_lock_PV (void) 
{
	int i;
	ASSERT (!thread_mlfqs);
	lock_init (&locks);
	wake_time = timer_ticks () +  TIMER_FREQ;
  	sema_init (&wait_sema, 3);
  	for(i=0;i<5;i++){
  		char name[16];
      	snprintf (name, sizeof name, "%d", i);
      	thread_create (name, PRI_DEFAULT, lock_fun, NULL);
  	}
  	for(i=5;i<10;i++){
  		char name[16];
      	snprintf (name, sizeof name, "%d", i);
      	thread_create (name, PRI_DEFAULT, PV_fun, NULL);
  	}
  	timer_sleep (1000);
}

static 
void lock_fun (void *aux UNUSED)
{
	lock_acquire (&locks);
    printf("thread %s use lock and it sleep 50.\n",thread_name());
    timer_sleep(50);
    lock_release (&locks);
    printf("thread %s release lock.\n",thread_name());
}

static 
void lock_PV (void *aux UNUSED)
{
	sema_down (&wait_sema)
    printf("thread %s P and it sleep 50.\n",thread_name());
    timer_sleep(50);
    sema_up (&wait_sema);
    printf("thread %s V.\n",thread_name());
}
