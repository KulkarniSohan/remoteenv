#include "RespMessage.hpp"
#include <cstring>
#include "include/global.hpp"
#include <linux/limits.h>

RespMessage :: RespMessage()
{
	cout << "RespMessage :: RespMessage" << endl;
}

RespMessage :: ~RespMessage()
{
	cout << "RespMessage :: ~RespMessage" << endl;
}

RespMessage*
RespMessage :: extract_message(void* lp_event)
{
	cout << "RespMessage :: extract_message" << endl;
	RespMessage* lp_rcvd_event = (RespMessage*)lp_event;
	this -> m_msg_type = lp_rcvd_event -> get_mesg_type();
	this -> m_client_no = lp_rcvd_event -> get_client_no();
	strncpy(this -> m_ip, lp_rcvd_event -> get_ip(), 16);
	//this -> m_ip = lp_rcvd_event -> get_ip();
	this -> m_port = lp_rcvd_event -> get_port();
	strncpy(this -> str, lp_rcvd_event -> get_string(), PATH_MAX);
	//this -> set_buf(lp_rcvd_event -> get_buf(), this -> m_no_strings);
	printf ("Str : %s\n", this -> str);

	return this;
}

void
RespMessage :: set_mesg_type(int msg_type)
{
	m_msg_type = msg_type;
}

int
RespMessage :: get_mesg_type()
{
	return m_msg_type;
}

void
RespMessage :: set_ip(char* ip)
{
	//inet_pton(AF_INET, ip . c_str(), &m_ip);
	//m_ip = ip;
	strncpy(m_ip, ip, 16);
}

char*
RespMessage :: get_ip()
{
	return m_ip;
}

void
RespMessage :: set_port(uint16_t port)
{
	m_port = port;
}

uint16_t
RespMessage :: get_port()
{
	return m_port;
}
/*
struct Buffer*
RespMessage :: get_buf()
{
    return mp_buf;
}

void
RespMessage :: set_buf(struct Buffer* p_buf, int no_of_strings)
{
	mp_buf = (struct Buffer* ) malloc(sizeof(struct Buffer) * no_of_strings);
	int k = no_of_strings;
	int i = 0;
    while (k > 0)
    {
        strncpy(mp_buf[i].str, p_buf[i].str, PATH_MAX);
		printf ("STR : %s\n", p_buf[i] .str);
        i++;
        k--;
    }
}

void
RespMessage :: set_size(int size)
{
    m_size = size;
}

int
RespMessage :: get_size()
{
    return m_size;
}
*/
int 
RespMessage :: get_client_no()
{
	return m_client_no;
}

void
RespMessage :: set_client_no(int client_no)
{
	m_client_no = client_no;
}
/*
int
RespMessage :: get_no_strings()
{
	return m_no_strings;
}

void
RespMessage :: set_no_strings(int no_strings)
{
	m_no_strings = no_strings;
}
*/
/*
void
RespMessage :: display()
{
	for (int i = 0; i < m_no_strings; i++)
	{
		printf ("Str : %s\n", mp_buf[i]);
	}
}
*/


char*
RespMessage :: get_string()
{
	return str;
}
