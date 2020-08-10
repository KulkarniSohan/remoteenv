#include "ExitEvent.hpp"
#include "Application.hpp"
#include "controller/MessageController.hpp"
#include "dao/ClientDao.hpp"
#include <cstring>


ExitEvent :: ExitEvent(Application& app, string& ip, uint16_t port, int client_no, string& cwd) : BaseEvent(app, ip, port, client_no)
{
	cout << "ExitEvent :: ExitEvent" << endl;
	mp_buf = new char[strlen("bye") + 1];
	strncpy(mp_buf, "bye", strlen("bye"));
	m_size = strlen("bye");
	set_msg_type(4);
	process();	
}

ExitEvent :: ExitEvent(Application& app, string& ip, uint16_t port, int client_no, char* buffer, int size) : BaseEvent(app, ip, port, client_no)
{
	cout << "ExitEvent :: ExitEvent Incoming Packet " << endl;
	m_app . get_client_dao() . remove_client_map(get_client_no());
	mp_buf = new char[size+1];
	strncpy(mp_buf, buffer, size);	
	load();
}

BaseEvent*
ExitEvent :: get_instance(Application& app, string& ip, uint16_t port, int client_no, char* buffer, int size)
{
	return new ExitEvent(app, ip, port, client_no, buffer, size);
}

ExitEvent :: ~ExitEvent()
{
	cout << "ExitEvent :: ~ExitEvent" << endl;
}

void
ExitEvent :: load()
{
	cout << "ExitEvent :: load " << endl;
	printf ("\n Client No : %d\n", get_client_no());
	printf ("OUTPUT : %s\n", mp_buf);
}

void
ExitEvent :: process()
{
	cout << "ExitEvent :: process" << endl;
	queue<void*>& l_cntrler_to_iface_queue = m_app . get_mesg_cntrler() . get_cntrler_to_iface_queue();
	l_cntrler_to_iface_queue . push((void*)this); 
}

char*
ExitEvent :: get_buf()
{
	cout << "ExitEvent :: get_buf" << endl;
	return mp_buf;
}

int
ExitEvent :: get_buf_size()
{
	cout << "ExitEvent :: get_buf_size " << endl;
	return m_size;
}

int
ExitEvent :: get_msg_type()
{
	return m_msg_type;
}

void
ExitEvent :: set_msg_type(int msg_type)
{
	m_msg_type = msg_type;
}

