#ifndef __CHANGE_DIRECTORY_EVENT_HPP__
#define __CHANGE_DIRECTORY_EVENT_HPP__


#include "BaseEvent.hpp"
#include <iostream>
#include <string>
#include <queue>

class Application;

using namespace std;


class ChangeDirectoryEvent : public BaseEvent
{
	private :
		int m_msg_type;
		char* mp_buf;
		int m_size;
		int m_cnt;
	public :
		static BaseEvent* get_instance(Application& app, string& m_ip, uint16_t port, int client_no, char* buf, int size);
		ChangeDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no, char* buf, int size);
		~ChangeDirectoryEvent();
		void load();
		void process();
		char** get_buf();
		int get_buf_size();
		int get_mesg_type();
		void set_msg_type(int msg_type);
		void set_no_strings(int cnt)
		{
			m_cnt = cnt;
		}
		int get_no_strings()
		{
			return m_cnt;
		}
};


#endif
