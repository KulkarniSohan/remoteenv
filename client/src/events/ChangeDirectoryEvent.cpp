#include "ChangeDirectoryEvent.hpp"
#include "Application.hpp"
#include "controller/MessageController.hpp"
#include <cstring>


ChangeDirectoryEvent :: ChangeDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no, string& cwd) : BaseEvent(app, ip, port, client_no)
{
	cout << "ChangeDirectoryEvent :: ChangeDirectoryEvent" << endl;
	//string l_cwd = "cd " + cwd;
	mp_buf = new char[strlen(cwd.c_str()) + 1];
	strncpy(mp_buf, cwd.c_str(), strlen(cwd.c_str()));
	m_size = strlen(cwd . c_str());
	set_msg_type(2);
	printf ("Str : %s\n", mp_buf);
	process();	
}

ChangeDirectoryEvent :: ChangeDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no, char* buffer, int size) : BaseEvent(app, ip, port, client_no)
{
	cout << "ListDirectory :: ListDirectory Incoming Packet " << endl;
	mp_buf = new char[size+1];
	strncpy(mp_buf, buffer, size);	
	load();
}

BaseEvent*
ChangeDirectoryEvent :: get_instance(Application& app, string& ip, uint16_t port, int client_no, char* buffer, int size)
{
	return new ChangeDirectoryEvent(app, ip, port, client_no, buffer, size);
}

ChangeDirectoryEvent :: ~ChangeDirectoryEvent()
{
	cout << "ChangeDirectoryEvent :: ~ChangeDirectoryEvent" << endl;
	delete mp_buf;
}

void
ChangeDirectoryEvent :: load()
{
	cout << "ChangeDirectoryEvent :: load " << endl;
	printf ("\n Client No : %d\n", get_client_no());
	printf ("OUTPUT : %s\n", mp_buf);
}

void
ChangeDirectoryEvent :: process()
{
	cout << "ChangeDirectoryEvent :: process" << endl;
	queue<void*>& l_cntrler_to_iface_queue = m_app . get_mesg_cntrler() . get_cntrler_to_iface_queue();
	l_cntrler_to_iface_queue . push((void*)this); 
}

char*
ChangeDirectoryEvent :: get_buf()
{
	cout << "ChangeDirectoryEvent :: get_buf" << endl;
	return mp_buf;
}

int
ChangeDirectoryEvent :: get_buf_size()
{
	cout << "ChangeDirectoryEvent :: get_buf_size " << endl;
	return m_size;
}

int
ChangeDirectoryEvent :: get_msg_type()
{
	return m_msg_type;
}

void
ChangeDirectoryEvent :: set_msg_type(int msg_type)
{
	m_msg_type = msg_type;
}

