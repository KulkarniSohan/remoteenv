#include "PresentWorkingDirectoryEvent.hpp"
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

PresentWorkingDirectoryEvent :: PresentWorkingDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no, char* buf, int size) : BaseEvent(app, ip, port, client_no)
{
	cout << "PresentWorkingDirectoryEvent :: PresentWorkingDirectoryEvent " << endl;
	// implement the ls code from here.
	//mp_queue = new MyQueue();
	mp_buf = NULL;
}

BaseEvent*
PresentWorkingDirectoryEvent :: get_instance(Application& app, string& ip, uint16_t port, int client_no, char* buf, int size)
{
	return new PresentWorkingDirectoryEvent(app, ip, port, client_no, buf, size);
}

PresentWorkingDirectoryEvent :: ~PresentWorkingDirectoryEvent()
{
	cout << "PresentWorkingDirectoryEvent :: ~PresentWorkingDirectoryEvent" << endl;
	free(mp_buf);
}

void
PresentWorkingDirectoryEvent :: load()
{
	cout << "PresentWorkingDirectoryEvent :: load " << endl;
	shared_ptr<Client> lp_client = m_app . get_client_dao() . get_client_map(get_client_no());
	string dir_path = lp_client -> get_cwd();
	printf ("&&&&&&&&&&&&&&&& PATH = %s\n", dir_path.c_str());
	mp_buf = new char[strlen(dir_path.c_str()) + 1];
    strncpy(mp_buf, dir_path.c_str(), strlen(dir_path.c_str()));
	m_mesg_type = 4;
	m_cnt = 1;
	queue<void*>& l_ad_cntrler_to_iface_queue = m_app . get_mesg_cntrler() . get_cntrler_to_iface_queue();
	l_ad_cntrler_to_iface_queue . push((void*)this);
}


char** 
PresentWorkingDirectoryEvent :: get_buf()
{
	return &mp_buf;
}
        
void 
PresentWorkingDirectoryEvent :: set_buf(char* lp_buf)
{
	mp_buf = lp_buf;
}

int 
PresentWorkingDirectoryEvent :: get_no_strings()
{
	return m_cnt;
}

void 
PresentWorkingDirectoryEvent :: set_no_strings(int cnt)
{
	m_cnt = cnt;
}

void
PresentWorkingDirectoryEvent :: set_mesg_type(int mesg_type)
{
	m_mesg_type = mesg_type;
}

int
PresentWorkingDirectoryEvent :: get_mesg_type()
{
	return m_mesg_type;
}

int
PresentWorkingDirectoryEvent :: get_size()
{
	return m_size;
}
