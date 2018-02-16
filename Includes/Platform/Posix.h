#ifndef _POSIX_H_
#define _POSIX_H_

#include <unistd.h>
#include <pthread.h>
#include <time.h>
#if OS_MAC
#include <errno.h>
#endif


#include "Posix/Posix_Console.cpp"
#include "Posix/Posix_Timer.cpp"
#include "Posix/Posix_Thread.cpp"
#include "Posix/Posix_Hardware.cpp"
#include "Posix/Posix_Mutex.cpp"

#endif
