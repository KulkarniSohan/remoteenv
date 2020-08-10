#ifndef __GLOBAL_HPP__
#define __GLOBAL_HPP__

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <queue>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include <cstring>

#define REQ_SENT 1
#define RESP_RCVD 0


typedef void * (*THREAD_FUNCTION) (void*);

#endif
