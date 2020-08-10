#include "ReqMessage.hpp"
#include <cstring>
#include "include/global.hpp"

ReqMessage :: ReqMessage()
{
	cout << "ReqMessage :: ReqMessage" << endl;
}

ReqMessage :: ~ReqMessage()
{
	cout << "ReqMessage :: ~ReqMessage" << endl;
}

ReqMessage*
ReqMessage :: extract_message(void* lp_event)
{
	cout << "ReqMessage :: extract_message" << endl;
	ReqMessage* lp_rcvd_event = (ReqMessage*)lp_event;
	this -> m_msg_type = lp_rcvd_event -> get_mesg_type();
	this -> m_client_no = lp_rcvd_event -> get_client_no();
	//strncpy(this -> m_ip, lp_rcvd_event -> get_ip(), strlen(lp_rcvd_event -> get_ip()));
	this -> m_ip = lp_rcvd_event -> get_ip();
	this -> m_port = lp_rcvd_event -> get_port();
	this -> m_rcvd_port = lp_rcvd_event -> get_rcvd_port();
	this -> m_size = lp_rcvd_event -> get_size();
	this -> set_buf(lp_rcvd_event -> get_buf());
	//strncpy(this -> mp_buf, lp_rcvd_event -> get_buf(), strlen(lp_rcvd_event -> get_buf()) + 1);
	//*(str + strlen(lp_rcvd_event -> get_buf() + 1) = '\0';
	printf ("REQ BUFFER : %s\n", this -> mp_buf);
	return this;
}

void
ReqMessage :: set_mesg_type(int msg_type)
{
	m_msg_type = msg_type;
}

int
ReqMessage :: get_mesg_type()
{
	return m_msg_type;
}

void
ReqMessage :: set_ip(string& ip)
{
	inet_pton(AF_INET, ip . c_str(), &m_ip);
}

uint32_t
ReqMessage :: get_ip()
{
	return m_ip;
}

void
ReqMessage :: set_port(uint16_t port)
{
	m_port = port;
}

uint16_t
ReqMessage :: get_port()
{
	return m_port;
}

char*
ReqMessage :: get_buf()
{
    return mp_buf;
}

void
ReqMessage :: set_buf(char* p_buf)
{
	strncpy(mp_buf, p_buf, strlen(p_buf));
	char* lp_str = this -> mp_buf;
    *(lp_str + strlen(p_buf) + 1) = '\0';
}

void
ReqMessage :: set_size(int size)
{
    m_size = size;
}

int
ReqMessage :: get_size()
{
    return m_size;
}

int 
ReqMessage :: get_client_no()
{
	return m_client_no;
}

void
ReqMessage :: set_client_no(int client_no)
{
	m_client_no = client_no;
}

uint16_t
ReqMessage :: get_rcvd_port()
{
	return m_rcvd_port;
}

void
ReqMessage :: set_rcvd_port(uint16_t rcvd_port)
{
	m_rcvd_port = rcvd_port;
}
