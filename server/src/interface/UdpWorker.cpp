#include "UdpWorker.hpp"
#include "UdpServerSocket.hpp"
#include "Application.hpp"
#include "events/BaseEvent.hpp"
#include "controller/MessageController.hpp"
#include <queue>

//UdpWorker :: mp_instance = NULL;
UdpWorker* UdpWorker :: mp_instance = NULL;

UdpWorker :: UdpWorker(Application& app) : m_app(app)
{
	cout << "UdpWorker :: UdpWorker" << endl;
	string l_local_ip = "127.0.0.1";
	uint32_t l_local_port = 1234;
	mp_udp_server = new UdpServerSocket(this, l_local_ip, l_local_port);
}


UdpWorker*
UdpWorker :: get_instance(Application& app)
{
	cout << "UdpWorker :: get_instance" << endl;
	if (mp_instance == NULL)
	{
		mp_instance = new UdpWorker(app);
	}
	return mp_instance;
}

pthread_t
UdpWorker :: init()
{
	cout << "UdpWorker :: init" << endl;
	pthread_t l_serv_thread;
	mp_udp_server -> init();
	l_serv_thread = mp_udp_server -> get_server_thread_id();
	return l_serv_thread;
}

void
UdpWorker :: on_receive(string client_ip, char* buf, int buf_size)
{
	cout << "UdpWorker :: on_receive" << endl;
	m_client_ip = client_ip;
	m_server_buf_size = buf_size;
	m_server_buf = new char[m_server_buf_size];
	std::memcpy(m_server_buf, buf, buf_size);
	std::queue<void*>& l_ad_iface_to_cntrler_queue = m_app . get_mesg_cntrler() . get_iface_to_cntrler_queue();
	l_ad_iface_to_cntrler_queue . push((void*)m_server_buf);
}

void
UdpWorker :: on_send(string& ip_addr, uint16_t port, char* buf, int buf_size)
{
	cout << "UdpWorker :: on_send" << endl;
	cout << "UdpWorker :: on_send : IP " << ip_addr << "Port : " << port << endl; 
	mp_udp_server -> send_to(ip_addr, port, buf, buf_size);
}

void
UdpWorker :: clear_buf()
{
	cout << "UdpWorker :: clear_buf " << endl;
	delete m_server_buf;
}
