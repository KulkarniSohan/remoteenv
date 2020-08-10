#ifndef __ECHO_REQ_EVENT_HPP__
#define __ECHO_REQ_EVENT_HPP__


#include "BaseEvent.hpp"
#include <iostream>
#include <string>
#include <queue>

class Application;

using namespace std;


class ListDirectoryEvent : public BaseEvent
{
	private :
		int m_msg_type;
		char* mp_buf;
		int m_size;
	public :
		static BaseEvent* get_instance(Application& app, string& m_ip, uint16_t port, int client_no, char* buffer, int size);
		ListDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no);
		ListDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no, char* buffer, int size);
		~ListDirectoryEvent();
		void load();
		void process();
		char* get_buf();
		int get_buf_size();
		int get_msg_type();
		void set_msg_type(int msg_type);
};


#endif
