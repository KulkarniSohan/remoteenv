#ifndef __UDP_SOCKET_HPP__
#define __UDP_SOCKET_HPP__

class UdpWorker;

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

using namespace std;

class UdpServerSocket
{
	private :
		int m_sock_fd;
		string m_local_ip;
		uint32_t m_local_port;
		struct sockaddr_in m_servaddr;
		struct sockaddr_in m_cliaddr;
		pthread_t m_server_thread_id;
		UdpWorker* mp_udp_worker;
	public :
		~UdpServerSocket();
		UdpServerSocket(UdpWorker* udp_worker, string local_ip, uint32_t port);

		void set_local_ip(string& local_ip);
		string& get_local_ip();

		void set_local_port(uint32_t local_port);
		uint32_t get_local_port();

		void init();

		pthread_t get_server_thread_id();
	
		static void* receive_from_helper(void* args);	
		void* receive_from();

		void send_to(string& ip_addr, uint16_t port, char* buf, int buf_size);
	
	
};




#endif
