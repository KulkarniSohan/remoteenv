#include "ChangeDirectoryEvent.hpp"
#include "Application.hpp"
#include "controller/MessageController.hpp"
#include <cstring>
#include "entities/Client.hpp"
#include "dao/ClientDao.hpp"

ChangeDirectoryEvent :: ChangeDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no, char* buf, int size) : BaseEvent(app, ip, port, client_no)
{
	cout << "ChangeDirectory :: ChangeDirectory Incoming Packet " << endl;
	mp_buf = new char[strlen(buf) + 1];
	strncpy(mp_buf, buf, strlen(buf));
}

BaseEvent*
ChangeDirectoryEvent :: get_instance(Application& app, string& ip, uint16_t port, int client_no, char* buf, int size)
{
	return new ChangeDirectoryEvent(app, ip, port, client_no, buf, size);
}

ChangeDirectoryEvent :: ~ChangeDirectoryEvent()
{
	cout << "ChangeDirectoryEvent :: ~ChangeDirectoryEvent" << endl;
}

void
ChangeDirectoryEvent :: load()
{
	cout << "ChangeDirectoryEvent :: load " << endl;
	shared_ptr<Client> lp_client = m_app . get_client_dao() . get_client_map(get_client_no());

	string cwd(mp_buf);
	printf ("################### DIR : %s\n", cwd.c_str());
	if (chdir(cwd.c_str()) != 0)
	{
		cout << "Error *** Occurred Changing cwd" << endl;
		return;
	}
	lp_client -> set_cwd(cwd);
	m_msg_type = 3;
	m_cnt = 1;
	queue<void*>& l_ad_cntrler_to_iface_queue = m_app . get_mesg_cntrler() . get_cntrler_to_iface_queue();
    l_ad_cntrler_to_iface_queue . push((void*)this);
}

void
ChangeDirectoryEvent :: process()
{
	cout << "ChangeDirectoryEvent :: process" << endl;
	queue<void*>& l_cntrler_to_iface_queue = m_app . get_mesg_cntrler() . get_cntrler_to_iface_queue();
	l_cntrler_to_iface_queue . push((void*)this); 
}

char**
ChangeDirectoryEvent :: get_buf()
{
	cout << "ChangeDirectoryEvent :: get_buf" << endl;
	return &mp_buf;
}

int
ChangeDirectoryEvent :: get_buf_size()
{
	cout << "ChangeDirectoryEvent :: get_buf_size " << endl;
	return m_size;
}

int
ChangeDirectoryEvent :: get_mesg_type()
{
	return m_msg_type;
}

void
ChangeDirectoryEvent :: set_msg_type(int msg_type)
{
	m_msg_type = msg_type;
}

