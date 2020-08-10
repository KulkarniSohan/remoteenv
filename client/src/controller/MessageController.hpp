#ifndef __MESSAGE_CONTROLLER_HPP__
#define __MESSAGE_CONTROLLER_HPP__

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
class BaseEvent;
class Application;
class ReqMessage;
class RespMessage;

using namespace std;


/*
* Message Type :
* 	1. Echo Request
* 	2. Echo Response
*	3. Firefox Kill Request
* 	4. Firefox kill Response
*	5. Calc Kill Request
*	6. Calc Kill Response
*/

class MessageController
{
	private :
		Application& m_app;
		pthread_t m_mesg_cntrler_id;
		pthread_t m_send_mesg_cntrler_id;
		int m_msg_type;
		queue<void*> m_ad_iface_to_cntrler_queue;
		queue<void*> m_ad_cntrler_to_iface_queue;
		MessageController(Application& app);
		unordered_map<int, BaseEvent* (*) (Application&, string&, uint16_t, int, char*, int)> m_instance_map;
	public :
		~MessageController();
		static MessageController* mp_instance;
		static MessageController* get_instance(Application& app);
		std::queue<void*>& get_iface_to_cntrler_queue();
		std::queue<void*>& get_cntrler_to_iface_queue();
		void init();
		void* queue_listen_thread();
		void* queue_send_thread();
		static void* queue_listen_thread_helper(void* args);
		static void* queue_send_thread_helper(void* args);
		pthread_t get_mesg_cntrler_id();
		pthread_t get_send_mesg_cntrler_id();
		RespMessage* extract_msg_type(void* lp_event);
		
};


#endif
