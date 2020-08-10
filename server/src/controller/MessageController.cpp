#include "MessageController.hpp"
#include "events/BaseEvent.hpp"
#include "Application.hpp"
#include "include/global.hpp"
#include "events/BaseEvent.hpp"
#include "events/ListDirectoryEvent.hpp"
#include "events/ChangeDirectoryEvent.hpp"
#include "events/PresentWorkingDirectoryEvent.hpp"
#include "events/ExitEvent.hpp"
#include "enc_dec/ReqMessage.hpp"
#include "enc_dec/RespMessage.hpp"
#include <memory>
#include "entities/Client.hpp"
#include "dao/ClientDao.hpp"
#include "interface/UdpWorker.hpp"
#include <linux/limits.h>

MessageController* MessageController :: mp_instance = NULL;

MessageController :: MessageController (Application& app) : m_app(app)
{
	cout << "MessageController :: MessageController " << endl;
	// initialize the unorderd map of the MesgTypes
	m_instance_map[1] = ListDirectoryEvent :: get_instance;
	m_instance_map[2] = ChangeDirectoryEvent :: get_instance;
	m_instance_map[3] = PresentWorkingDirectoryEvent :: get_instance;
	m_instance_map[4] = ExitEvent :: get_instance;
}

MessageController*
MessageController :: get_instance(Application& app)
{
	if (mp_instance == NULL)
	{
		mp_instance = new MessageController(app);
	}
	return mp_instance;
}

MessageController :: ~MessageController()
{
	cout << "MessageController :: ~MessageController " << endl;
}

std::queue<void*>&
MessageController :: get_iface_to_cntrler_queue()
{
	return m_ad_iface_to_cntrler_queue;
}

std::queue<void*>&
MessageController :: get_cntrler_to_iface_queue()
{
	return m_ad_cntrler_to_iface_queue;
}

void
MessageController :: init()
{
	int l_err = pthread_create(&m_mesg_cntrler_id, NULL, (THREAD_FUNCTION) &MessageController :: queue_listen_thread_helper, this);
	int l_err_1 = pthread_create(&m_mesg_iface_id, NULL, (THREAD_FUNCTION) &MessageController :: queue_send_thread_helper, this);
}

void*
MessageController :: queue_listen_thread()
{
	cout << "MessageController :: queue_listen_thread" << endl;
	void* lp_void_event = NULL;
	while(1)
	{
	while (this -> m_ad_iface_to_cntrler_queue . empty())
	{
	}
	lp_void_event = this -> m_ad_iface_to_cntrler_queue . front();
	if (lp_void_event == NULL)
	{
		cout << "************************************* SOME PROBLEM OCCURRED WHILE RETERIVING EVENT *************************" << endl;
		return NULL;
	}
	//ReqMessage* lp_msg = extract_msg_type(lp_void_event);
	ReqMessage* lp_msg = new ReqMessage();
    lp_msg -> extract_message((void*)lp_void_event);
	char ip_addr[16];
	uint32_t l_ui_ip = lp_msg -> get_ip();
	inet_ntop(AF_INET, (void*)&l_ui_ip, ip_addr, 16);
	string ip(ip_addr);
	cout << "MessageController :: queue_listen_thread : IP " << ip << "UINT32 IP " << l_ui_ip << endl;
	shared_ptr<Client> lp_client = m_app . get_client_dao() . get_client_map(lp_msg -> get_client_no());
	if (lp_client == nullptr)
	{
		shared_ptr<Client> lp_l_client = make_shared<Client>(lp_msg -> get_client_no(), ip, lp_msg -> get_rcvd_port());
		m_app . get_client_dao() . add_client_map(lp_msg -> get_client_no(), lp_l_client);
	}
	BaseEvent* lp_event =  m_instance_map[lp_msg -> get_mesg_type()](m_app, ip, lp_msg -> get_rcvd_port(), lp_msg -> get_client_no(), lp_msg -> get_buf(), lp_msg -> get_size());
	lp_event -> load();
	this -> m_ad_iface_to_cntrler_queue . pop();
	delete lp_msg;
	m_app . get_udp_worker() . clear_buf();
	}
}


void*
MessageController :: queue_listen_thread_helper(void* args)
{
	cout << "MessageController :: queue_listen_thread_helper" << endl;
	return ((MessageController*) args) -> queue_listen_thread();
}

void*
MessageController :: queue_send_thread()
{
	cout << "MessageController :: queue_send_thread" << endl;
	void* lp_void_event = NULL;
	while(1)
	{
    while (this -> m_ad_cntrler_to_iface_queue . empty())
    {
    }
    lp_void_event = this -> m_ad_cntrler_to_iface_queue . front();
    if (lp_void_event == NULL)
    {
		cout << "************************************* SOME PROBLEM OCCURRED WHILE RETERIVING EVENT *************************" << endl;
        return NULL;
    }
	BaseEvent* lp_rcvd_event = (BaseEvent*) lp_void_event;
	RespMessage* lp_msg = new RespMessage();
	lp_msg -> set_mesg_type(lp_rcvd_event -> get_mesg_type());
	lp_msg -> set_ip(lp_rcvd_event -> get_ip());
	lp_msg -> set_port(lp_rcvd_event -> get_port());
	//lp_msg -> set_buf(lp_rcvd_event -> get_buf(), lp_rcvd_event -> get_no_strings());
	lp_msg -> set_client_no(lp_rcvd_event -> get_client_no());
	for (int i = 0; i < lp_rcvd_event -> get_no_strings(); i++)
	{
		char** str = lp_rcvd_event -> get_buf();
		bzero(lp_msg -> get_string(), PATH_MAX);
		lp_msg -> set_string (*(str+i));
		m_app . get_udp_worker() . on_send(lp_rcvd_event -> get_ip(), lp_msg -> get_port(), (char*)lp_msg, sizeof(RespMessage));
	}
	this -> m_ad_cntrler_to_iface_queue . pop();
	delete lp_rcvd_event;
	delete lp_msg;
	}
}

void*
MessageController :: queue_send_thread_helper(void* args)
{
	cout << "MessageController :: queue_listen_thread_helper" << endl;
	return ((MessageController*) args) -> queue_send_thread();
}

pthread_t
MessageController :: get_mesg_cntrler_id()
{
	return m_mesg_cntrler_id;
}

pthread_t
MessageController :: get_mesg_iface_id()
{
	return m_mesg_iface_id;
}


ReqMessage*
MessageController :: extract_msg_type(void* lp_event)
{
	cout << "MessageController :: extract_message" << endl;
	ReqMessage* lp_msg = new ReqMessage();
	lp_msg -> extract_message((void*)lp_event);
	return lp_msg;
	
}
