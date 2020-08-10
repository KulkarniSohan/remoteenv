#include "PresentWorkingDirectoryEvent.hpp"
#include "Application.hpp"
#include "controller/MessageController.hpp"
#include <cstring>


PresentWorkingDirectoryEvent :: PresentWorkingDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no, string& cwd) : BaseEvent(app, ip, port, client_no)
{
	cout << "PresentWorkingDirectoryEvent :: PresentWorkingDirectoryEvent" << endl;
	mp_buf = new char[strlen("pwd") + 1];
	strncpy(mp_buf, "pwd", strlen("pwd"));
	m_size = strlen("pwd");
	set_msg_type(3);
	process();	
}

PresentWorkingDirectoryEvent :: PresentWorkingDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no, char* buffer, int size) : BaseEvent(app, ip, port, client_no)
{
	cout << "ListDirectory :: ListDirectory Incoming Packet " << endl;
	mp_buf = new char[size+1];
	strncpy(mp_buf, buffer, size);	
	load();
}

BaseEvent*
PresentWorkingDirectoryEvent :: get_instance(Application& app, string& ip, uint16_t port, int client_no, char* buffer, int size)
{
	return new PresentWorkingDirectoryEvent(app, ip, port, client_no, buffer, size);
}

PresentWorkingDirectoryEvent :: ~PresentWorkingDirectoryEvent()
{
	cout << "PresentWorkingDirectoryEvent :: ~PresentWorkingDirectoryEvent" << endl;
}

void
PresentWorkingDirectoryEvent :: load()
{
	cout << "PresentWorkingDirectoryEvent :: load " << endl;
	printf ("\n Client No : %d\n", get_client_no());
	printf ("OUTPUT : %s\n", mp_buf);
}

void
PresentWorkingDirectoryEvent :: process()
{
	cout << "PresentWorkingDirectoryEvent :: process" << endl;
	queue<void*>& l_cntrler_to_iface_queue = m_app . get_mesg_cntrler() . get_cntrler_to_iface_queue();
	l_cntrler_to_iface_queue . push((void*)this); 
}

char*
PresentWorkingDirectoryEvent :: get_buf()
{
	cout << "PresentWorkingDirectoryEvent :: get_buf" << endl;
	return mp_buf;
}

int
PresentWorkingDirectoryEvent :: get_buf_size()
{
	cout << "PresentWorkingDirectoryEvent :: get_buf_size " << endl;
	return m_size;
}

int
PresentWorkingDirectoryEvent :: get_msg_type()
{
	return m_msg_type;
}

void
PresentWorkingDirectoryEvent :: set_msg_type(int msg_type)
{
	m_msg_type = msg_type;
}

