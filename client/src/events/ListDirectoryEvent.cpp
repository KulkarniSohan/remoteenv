#include "ListDirectoryEvent.hpp"
#include "Application.hpp"
#include "controller/MessageController.hpp"
#include <cstring>


ListDirectoryEvent :: ListDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no) : BaseEvent(app, ip, port, client_no)
{
	cout << "ListDirectoryEvent :: ListDirectoryEvent" << endl;
	mp_buf = new char[strlen("ls") + 1];
	strncpy(mp_buf, "ls", strlen("ls"));
	m_size = strlen("ls");
	set_msg_type(1);
	process();	
}

ListDirectoryEvent :: ListDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no, char* buffer, int size) : BaseEvent(app, ip, port, client_no)
{
	cout << "ListDirectory :: ListDirectory Incoming Packet " << endl;
	mp_buf = new char[size+1];
	strncpy(mp_buf, buffer, size);	
	load();
}

BaseEvent*
ListDirectoryEvent :: get_instance(Application& app, string& ip, uint16_t port, int client_no, char* buffer, int size)
{
	return new ListDirectoryEvent(app, ip, port, client_no, buffer, size);
}

ListDirectoryEvent :: ~ListDirectoryEvent()
{
	cout << "ListDirectoryEvent :: ~ListDirectoryEvent" << endl;
}

void
ListDirectoryEvent :: load()
{
	cout << "ListDirectoryEvent :: load " << endl;
	printf ("\n Client No : %d\n", get_client_no());
	printf ("OUTPUT : %s\n", mp_buf);
	delete mp_buf;
}

void
ListDirectoryEvent :: process()
{
	cout << "ListDirectoryEvent :: process" << endl;
	queue<void*>& l_cntrler_to_iface_queue = m_app . get_mesg_cntrler() . get_cntrler_to_iface_queue();
	l_cntrler_to_iface_queue . push((void*)this); 
}

char*
ListDirectoryEvent :: get_buf()
{
	cout << "ListDirectoryEvent :: get_buf" << endl;
	return mp_buf;
}

int
ListDirectoryEvent :: get_buf_size()
{
	cout << "ListDirectoryEvent :: get_buf_size " << endl;
	return m_size;
}

int
ListDirectoryEvent :: get_msg_type()
{
	return m_msg_type;
}

void
ListDirectoryEvent :: set_msg_type(int msg_type)
{
	m_msg_type = msg_type;
}

