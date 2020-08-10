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
	strncpy(this -> m_ip, lp_rcvd_event -> get_ip(), 16);
	//this -> m_ip = lp_rcvd_event -> get_ip();
	this -> m_port = lp_rcvd_event -> get_port();
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
RespMessage :: set_ip(string& ip)
{
	//inet_pton(AF_INET, ip . c_str(), &m_ip);
	strncpy(m_ip, ip.c_str(), strlen(ip.c_str()));
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
*/

/*
void
RespMessage :: set_buf(char** p_buf, int no_of_strings)
{	
	mp_buf = (struct Buffer*) malloc(sizeof(struct Buffer) * no_of_strings);
	int k = no_of_strings;
	int i = 0;
    while (k > 0)
    {
        strncpy(mp_buf[i].str, p_buf[i], strlen(p_buf[i]));
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
void
RespMessage :: set_string(char* str)
{
	strncpy(this -> str, str, strlen(str));
	char* lp_str = this -> str;
	*(lp_str + strlen(str) + 1) = '\0';
	//printf ("Str : %s\n", this -> str);
}

char*
RespMessage :: get_string()
{
	return str;
}
