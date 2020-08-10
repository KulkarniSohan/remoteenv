#include "interface/UdpWorker.hpp"
#include "interface/UdpSocket.hpp"
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
#include "events/BaseEvent.hpp"
#include "events/ListDirectoryEvent.hpp"
#include "events/ChangeDirectoryEvent.hpp"
#include "entities/Client.hpp"
#include <linux/limits.h>

using namespace std;

//typedef void * (*THREAD_FUNCTION) (void*);


int menu()
{
	int ch;
	printf ("\n\t Display Menu");
	printf ("\t 1. LS");
	printf ("\t 2. cd");
	printf ("\t 3. pwd");
	printf ("\n\t Enter Option : ");
	scanf ("%d", &ch);
	return ch;
}

void
Application :: startup ()
{
	pthread_t l_sock_recv_thread, l_mesg_cntrler_thread, l_mesg_cntrler_send_thread;
	int ch;
	mp_client_dao = ClientDao :: get_instance(*this);
    mp_udp_worker_instance = UdpWorker :: get_instance(*this);
    l_sock_recv_thread = mp_udp_worker_instance -> init();
	mp_mesg_cntrler = MessageController :: get_instance(*this);
	mp_mesg_cntrler -> init();
	l_mesg_cntrler_thread = mp_mesg_cntrler -> get_mesg_cntrler_id();
	l_mesg_cntrler_send_thread = mp_mesg_cntrler -> get_send_mesg_cntrler_id();


	while ((ch = menu()) != 0) 
	{
		if (ch == 1)
		{
			char ip_addr[16] = {0};
			char* cd;
			int port, l_client_no = 0;
			printf ("\nEnter Server IP Address : ");
			scanf ("%s", ip_addr);
			printf ("\nEnter Port : ");
			scanf ("%d", &port);
			printf ("\nEnter Client No : ");
			scanf ("%d", &l_client_no);
			shared_ptr <Client>lp_client;
			lp_client = mp_client_dao -> get_client_map(l_client_no);
			if (lp_client == nullptr)
			{
				string l_ip(ip_addr);
				lp_client = make_shared<Client>(l_client_no, l_ip, port);
				cd = getenv("PWD");
				string cwd(cd);
                lp_client -> set_cwd(cwd);
				mp_client_dao -> add_client_map(l_client_no, lp_client); 
			}
			new ListDirectoryEvent((*this), lp_client -> get_ip(), lp_client -> get_port(), lp_client -> get_client_no());	
		}
		else
		if (ch == 2)
		{
			char ip_addr[16] = {0};
			char cd[PATH_MAX];
            int port, l_client_no = 0;
            printf ("\nEnter Server IP Address : ");
            scanf ("%s", ip_addr);
            printf ("\nEnter Port : ");
            scanf ("%d", &port);
            printf ("\nEnter Client No : ");
            scanf ("%d", &l_client_no);
			printf ("\nEnter Change Directory : ");
			scanf ("%s", cd); 
            shared_ptr <Client>lp_client;
            lp_client = mp_client_dao -> get_client_map(l_client_no);
			if (lp_client == nullptr)
            {
                string l_ip(ip_addr);
                lp_client = make_shared<Client>(l_client_no, l_ip, port);
				string cwd(cd);
				lp_client -> set_cwd(cwd);
                mp_client_dao -> add_client_map(l_client_no, lp_client);
            }
			new ChangeDirectoryEvent((*this), lp_client -> get_ip(), lp_client -> get_port(), lp_client -> get_client_no(), lp_client -> get_cwd());
		}
		else
		if (ch == 3)
		{
		}
	}
	
    pthread_join(l_sock_recv_thread, NULL);
	pthread_join(l_mesg_cntrler_thread, NULL);
	pthread_join(l_mesg_cntrler_send_thread, NULL);	
	
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
