#ifndef __EXIT_EVENT_HPP__
#define __EXIT_EVENT_HPP__


#include "BaseEvent.hpp"
#include <iostream>
#include <string>
#include <queue>

class Application;

using namespace std;


class ExitEvent : public BaseEvent
{
	private :
		int m_msg_type;
		char* mp_buf;
		int m_size;
	public :
		static BaseEvent* get_instance(Application& app, string& m_ip, uint16_t port, int client_no, char* buffer, int size);
		ExitEvent(Application& app, string& ip, uint16_t port, int client_no, string& cwd);
		ExitEvent(Application& app, string& ip, uint16_t port, int client_no, char* buffer, int size);
		~ExitEvent();
		void load();
		void process();
		char* get_buf();
		int get_buf_size();
		int get_msg_type();
		void set_msg_type(int msg_type);
};


#endif
