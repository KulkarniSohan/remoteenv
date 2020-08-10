#include "MessageController.hpp"
#include "events/BaseEvent.hpp"
#include "Application.hpp"
#include "include/global.hpp"
#include "events/BaseEvent.hpp"
#include "events/ListDirectoryEvent.hpp"
#include "events/ChangeDirectoryEvent.hpp"
#include "enc_dec/ReqMessage.hpp"
#include "enc_dec/RespMessage.hpp"
#include "interface/UdpWorker.hpp"

MessageController* MessageController :: mp_instance = NULL;

MessageController :: MessageController (Application& app) : m_app(app)
{
	cout << "MessageController :: MessageController " << endl;
	// initialize the unorderd map of the MesgTypes
	m_instance_map[2] = ListDirectoryEvent :: get_instance;
	m_instance_map[3] = ChangeDirectoryEvent :: get_instance;
	
	//m_instance_map[2] = EchoRespEvent :: get_instance;
	/*
	m_instance_map[3] = FirefoxKillReqEvent :: get_instance;
	m_instance_map[4] = FirefoxKillRespEvent :: get_instance;
	m_instance_map[5] = CalcKillReqEvent :: get_instance;
	m_instance_map[6] = CalcKillRespEvent :: get_instance;
	*/
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
	int l_err1 = pthread_create(&m_send_mesg_cntrler_id, NULL, (THREAD_FUNCTION) &MessageController :: queue_send_thread_helper, this);
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
	lp_void_event = m_ad_iface_to_cntrler_queue . front();
	if (lp_void_event == NULL)
	{
		return NULL;
	}
	RespMessage* lp_msg = extract_msg_type(lp_void_event);
	string ip(lp_msg -> get_ip());
	BaseEvent* lp_event =  m_instance_map[lp_msg -> get_mesg_type()](m_app, ip, lp_msg -> get_port(), lp_msg -> get_client_no(), lp_msg -> get_string(), strlen(lp_msg -> get_string()));
	cout << "MessageController :: queue_listen_thread : IP " << lp_msg -> get_ip() << endl;
	this -> m_ad_iface_to_cntrler_queue . pop();
	delete lp_event;
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
		return NULL;
		//continue;
	}	
	BaseEvent* lp_event = (BaseEvent*)lp_void_event;
	ReqMessage* lp_msg = new ReqMessage();
	lp_msg -> set_mesg_type(lp_event -> get_msg_type());
	lp_msg -> set_ip(lp_event -> get_ip());
	lp_msg -> set_port(lp_event -> get_port());
	lp_msg -> set_buf(lp_event -> get_buf());
	lp_msg -> set_size(lp_event -> get_buf_size());
	lp_msg -> set_client_no(lp_event -> get_client_no());
	lp_msg -> set_self_port(4321);
	m_app . get_udp_worker() . on_send(lp_event -> get_ip(), lp_event -> get_port(), (char*)lp_msg, sizeof(ReqMessage));
	delete lp_event;	
	m_ad_cntrler_to_iface_queue . pop();
	}
}

void*
MessageController :: queue_send_thread_helper(void* args)
{
	cout << "MessageController :: queue_send_thread_helper" << endl;
	return ((MessageController*)args) -> queue_send_thread();
}

pthread_t
MessageController :: get_mesg_cntrler_id()
{
	return m_mesg_cntrler_id;
}

pthread_t
MessageController :: get_send_mesg_cntrler_id()
{
	return m_send_mesg_cntrler_id;
}


RespMessage*
MessageController :: extract_msg_type(void* lp_event)
{
	cout << "MessageController :: extract_message" << endl;
	RespMessage* lp_msg = new RespMessage();
	lp_msg -> extract_message((void*)lp_event);
	return lp_msg;
	
}
