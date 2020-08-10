#include "UdpSocket.hpp"
#include "UdpWorker.hpp"
#include "include/global.hpp"

//UdpSocket :: mp_instance = NULL;


UdpSocket :: UdpSocket(UdpWorker* udp_worker, string local_ip, uint32_t local_port) : m_local_ip(local_ip), m_local_port(local_port), mp_udp_worker(udp_worker)
{
	cout << "UdpSocket :: UdpSocket " << endl;
	bzero(&m_servaddr, sizeof (struct sockaddr_in));
	bzero(&m_cliaddr, sizeof (struct sockaddr_in));
    m_sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    m_servaddr . sin_family = AF_INET;
    m_servaddr . sin_addr . s_addr = htonl(INADDR_ANY);
    m_servaddr . sin_port = htons(m_local_port);

    int l_ret = ::bind(m_sock_fd, (struct sockaddr* )&m_servaddr, (socklen_t)sizeof (m_servaddr));
    if (l_ret < 0)
    {
        perror("Error:");
        exit(1);
    }
}

UdpSocket :: ~UdpSocket()
{
	cout << "UdpSocket :: ~UdpSocket" << endl;
}

/*
UdpSocket*
UdpSocket :: get_instance(string local_ip, uint32_local_port)
{
	cout << "UdpSocket get_instance function" << endl;
	if (mp_instance == NULL)
	{
		mp_instance = new UdpSocket(local_ip, local_port);
	}
	return mp_instance;
}
*/

void 
UdpSocket :: set_local_ip(string& local_ip)
{
	m_local_ip = local_ip;
}

string&
UdpSocket :: get_local_ip()
{
	return m_local_ip;
}

void
UdpSocket :: set_local_port(uint32_t local_port)
{
	m_local_port = local_port;
}

uint32_t
UdpSocket :: get_local_port()
{
	return m_local_port;
}

void
UdpSocket :: init()
{
	cout << "UdpSocket :: init_socket_thread" << endl;
	int l_err = pthread_create(&m_server_thread_id, NULL, (THREAD_FUNCTION) &UdpSocket :: receive_from_helper, this);
} 

pthread_t
UdpSocket :: get_server_thread_id()
{
	return m_server_thread_id;
}

void*
UdpSocket :: receive_from()
{
	cout << "UdpSocket :: receive_from" << endl;
	int l_read;
    uint32_t l_cli_size = sizeof(struct sockaddr_in);
    char buffer[2048] = "\0";
    while(1)
    {
        bzero(buffer, sizeof(buffer));
        l_cli_size = sizeof(struct sockaddr_in);
        l_read = recvfrom(m_sock_fd, buffer, 2048, 0, (struct sockaddr*)&m_cliaddr, &l_cli_size);
        char l_ip[4];
        inet_ntop (AF_INET, &(m_cliaddr . sin_addr), l_ip, sizeof (l_ip));
        string l_client_ip(l_ip);
        mp_udp_worker -> on_receive(l_client_ip, buffer, l_read);
    }
}

void*
UdpSocket :: receive_from_helper(void* args)
{
	return ((UdpSocket*)args) -> receive_from();
}

void
UdpSocket :: sendto(string& ip_addr, uint16_t port, char* p_buf, int buf_size)
{
	cout << "UdpSocket :: send_to" << endl;
	// send directly on to the socket;
	int l_send, l_serv_size, l_sock_fd;
	struct sockaddr_in l_servaddr;
	bzero(&l_servaddr, sizeof(struct sockaddr_in));
	l_servaddr . sin_family = AF_INET;
	l_servaddr . sin_port = htons(port);
	inet_pton(AF_INET, ip_addr . c_str(), &l_servaddr . sin_addr);
	
	l_sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	l_serv_size = sizeof(struct sockaddr_in);
		
	l_send = ::sendto(l_sock_fd, p_buf, buf_size, 0, (struct sockaddr*)&l_servaddr, l_serv_size);
}


