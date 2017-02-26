/*  linux_port.c

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2013 Warren Pratt, NR0V and John Melton, G0ORX/N6LYT

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

The author can be reached by email at  

warren@wpratt.com
john.d.melton@googlemail.com

*/

#include "comm.h"

/********************************************************************************************************
*													*
*	Linux Port Utilities										*
*													*
********************************************************************************************************/

#ifdef linux

void QueueUserWorkItem(void *function,void *context,int flags) {
	pthread_t t;
	pthread_create(&t, NULL, function, context);
	pthread_join(t, NULL);
}

void InitializeCriticalSectionAndSpinCount(pthread_mutex_t *mutex,int count) {
	pthread_mutexattr_t mAttr;
	pthread_mutexattr_init(&mAttr);
	pthread_mutexattr_settype(&mAttr,PTHREAD_MUTEX_RECURSIVE_NP);
	pthread_mutex_init(mutex,&mAttr);
	pthread_mutexattr_destroy(&mAttr);
	// ignore count
}

void EnterCriticalSection(pthread_mutex_t *mutex) {
	pthread_mutex_lock(mutex);
}

void LeaveCriticalSection(pthread_mutex_t *mutex) {
	pthread_mutex_unlock(mutex);
}

void DeleteCriticalSection(pthread_mutex_t *mutex) {
	pthread_mutex_destroy(mutex);
}

int LinuxWaitForSingleObject(sem_t *sem,int ms) {
	int result=0;
	if(ms==INFINITE) {
		// wait for the lock
		result=sem_wait(sem);
	} else {
		// try to get the lock
		result=sem_trywait(sem);
		if(result!=0) {
			// didn't get the lock
			if(ms!=0) {
				// sleep if ms not zero
				sleep(ms);
				// try to get the lock again
				result=sem_trywait(sem);
			}
		}
	}
	
	return result;
}

sem_t *LinuxCreateSemaphore(int attributes,int initial_count,int maximum_count,char *name) {
        sem_t *sem;
        sem=malloc(sizeof(sem_t));
	int result;
	result=sem_init(sem, 0, 0);
	return sem;
}

void LinuxReleaseSemaphore(sem_t* sem,int release_count, int* previous_count) {
	while(release_count>0) {
		sem_post(sem);
		release_count--;
	}
}

sem_t *CreateEvent(void* security_attributes,int bManualReset,int bInitialState,char* name) {
	int result;
        sem_t *sem;
	sem=LinuxCreateSemaphore(0,0,0,0);
	// need to handle bManualReset and bInitialState
	return sem;
}

void LinuxSetEvent(sem_t* sem) {
	sem_post(sem);
}

pthread_t wdsp_beginthread( void( __cdecl *start_address )( void * ), unsigned stack_size, void *arglist, char *name) {
        pthread_t threadid;
	pthread_attr_t  attr;
	int             rc = 0;

	if (rc = pthread_attr_init(&attr)) {
 	    return -1;
	}
      
	if(stack_size!=0) {
	    if (rc = pthread_attr_setstacksize(&attr, stack_size)) {
	        return -1;
	    }
	}

        if( rc = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED)) {
            return -1;
        }
     
	if (rc = pthread_create(&threadid, &attr, (void*(*)(void*))start_address, arglist)) {
	     return -1;
	}

        //pthread_attr_destroy(&attr);
        rc=pthread_setname_np(threadid, name);

	return threadid;

}

void _endthread() {
	int res;
	pthread_exit((void *)&res);
}

void SetThreadPriority(pthread_t thread, int priority)  {
/*
	int policy;
	struct sched_param param;

	pthread_getschedparam(thread, &policy, &param);
	param.sched_priority = sched_get_priority_max(policy);
	pthread_setschedparam(thread, policy, &param);
*/
}

int CloseHandle(HANDLE hObject) {
}

#endif
