#ifndef __PRESENT_WORKING_DIRECTORY_EVENT_HPP__
#define __PRESENT_WORKING_DIRECTORY_EVENT_HPP__


#include "BaseEvent.hpp"
#include <iostream>
#include <string>
#include <queue>

class Application;

using namespace std;


class PresentWorkingDirectoryEvent : public BaseEvent
{
	private :
		int m_msg_type;
		char* mp_buf;
		int m_size;
	public :
		static BaseEvent* get_instance(Application& app, string& m_ip, uint16_t port, int client_no, char* buffer, int size);
		PresentWorkingDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no, string& cwd);
		PresentWorkingDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no, char* buffer, int size);
		~PresentWorkingDirectoryEvent();
		void load();
		void process();
		char* get_buf();
		int get_buf_size();
		int get_msg_type();
		void set_msg_type(int msg_type);
};


#endif
