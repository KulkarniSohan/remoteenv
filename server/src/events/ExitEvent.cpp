#include "ExitEvent.hpp"
#include "Application.hpp"
#include<dirent.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include "helper/MyQueue.hpp"
#include <linux/limits.h>
#include "entities/Client.hpp"
#include "dao/ClientDao.hpp"
#include "controller/MessageController.hpp"

ExitEvent :: ExitEvent(Application& app, string& ip, uint16_t port, int client_no, char* buf, int size) : BaseEvent(app, ip, port, client_no)
{
	cout << "ExitEvent :: ExitEvent " << endl;
	// implement the ls code from here.
	//mp_queue = new MyQueue();
	mp_buf = NULL;
}

BaseEvent*
ExitEvent :: get_instance(Application& app, string& ip, uint16_t port, int client_no, char* buf, int size)
{
	return new ExitEvent(app, ip, port, client_no, buf, size);
}

ExitEvent :: ~ExitEvent()
{
	cout << "ExitEvent :: ~ExitEvent" << endl;
	free(mp_buf);
}

void
ExitEvent :: load()
{
	cout << "ExitEvent :: load " << endl;
	m_app . get_client_dao() . remove_client_map(get_client_no());
	mp_buf = new char[strlen("bye") + 1];
    strncpy(mp_buf, "bye", strlen("bye"));
	m_mesg_type = 5;
	m_cnt = 1;
	queue<void*>& l_ad_cntrler_to_iface_queue = m_app . get_mesg_cntrler() . get_cntrler_to_iface_queue();
	l_ad_cntrler_to_iface_queue . push((void*)this);
}


char** 
ExitEvent :: get_buf()
{
	return &mp_buf;
}
        
void 
ExitEvent :: set_buf(char* lp_buf)
{
	mp_buf = lp_buf;
}

int 
ExitEvent :: get_no_strings()
{
	return m_cnt;
}

void 
ExitEvent :: set_no_strings(int cnt)
{
	m_cnt = cnt;
}

void
ExitEvent :: set_mesg_type(int mesg_type)
{
	m_mesg_type = mesg_type;
}

int
ExitEvent :: get_mesg_type()
{
	return m_mesg_type;
}

int
ExitEvent :: get_size()
{
	return m_size;
}
