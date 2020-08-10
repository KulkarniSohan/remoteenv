#include "interface/UdpWorker.hpp"
#include "interface/UdpServerSocket.hpp"
#include "controller/MessageController.hpp"
#include "dao/ClientDao.hpp"
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
#include "Application.hpp"

using namespace std;

//typedef void * (*THREAD_FUNCTION) (void*);

void
Application :: startup ()
{
	pthread_t l_sock_recv_thread, l_mesg_cntrler_thread, l_mesg_iface_thread;
	mp_client_dao = ClientDao :: get_instance(*this);
    mp_udp_worker_instance = UdpWorker :: get_instance(*this);
    l_sock_recv_thread = mp_udp_worker_instance -> init();
	mp_mesg_cntrler = MessageController :: get_instance(*this);
	mp_mesg_cntrler -> init();
	l_mesg_cntrler_thread = mp_mesg_cntrler -> get_mesg_cntrler_id();
	l_mesg_iface_thread = mp_mesg_cntrler -> get_mesg_iface_id();
	
    pthread_join(l_sock_recv_thread, NULL);
	pthread_join(l_mesg_cntrler_thread, NULL);
	pthread_join(l_mesg_iface_thread, NULL);
}


Application g_app;

int main(int argc, char* argv[])
{

	g_app . startup();
	/*
	pthread_t l_sock_recv_thread;
	UdpWorker* l_worker_instance = UdpWorker::get_instance();
	l_sock_recv_thread = l_worker_instance -> init();

	pthread_join(l_sock_recv_thread, NULL);*/
}
