#include "Client.hpp"

Client :: Client(int client_no, string& ip_addr, uint16_t port) : m_client_no(client_no), m_ip_addr(ip_addr), m_port(port)
{
	cout << "Client :: Client" << endl;
	char s[100];
	getcwd(s, 100);
	string str(s);
	m_cwd = str;	
}

Client :: ~Client()
{
	cout << "Client :: ~Client" << endl;
}

int 
Client :: get_client_no()
{
	return m_client_no;
}

void
Client :: set_client_no(int client_no)
{
	m_client_no = client_no;
}

string&
Client :: get_cwd()
{
	return m_cwd;
}

void
Client :: set_cwd(string& cwd)
{
	m_cwd = cwd;
}

void
Client :: set_port (uint16_t port)
{
	m_port = port;
}

void
Client :: set_ip(string& ip)
{
	m_ip_addr = ip;
}

uint16_t
Client :: get_port()
{
	return m_port;
}

string& 
Client :: get_ip()
{
	return m_ip_addr;
}
