#ifndef __UDP_WORKER_HPP__
#define __UDP_WORKER_HPP__

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

class UdpSocket;
class Application;

using namespace std;

class UdpWorker
{
	private :
		Application& m_app;
		UdpSocket* mp_udp_server;
		UdpWorker(Application& app);
		string m_client_ip;
		char* m_server_buf;
		int m_server_buf_size;

	public :
		static UdpWorker* mp_instance;
		static UdpWorker* get_instance(Application& app);
		~UdpWorker();
		pthread_t init();
		void on_receive(string client_ip, char* buf, int buf_size);
		void on_send(string& ip_addr, uint16_t port, char* buf, int buf_size);
};



#endif
