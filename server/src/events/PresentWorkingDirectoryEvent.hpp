#ifndef __PRESENT_WORKING_DIRECTORY_EVENT_HPP__
#define __PRESENT_WORKING_DIRECTORY_EVENT_HPP__


#include "BaseEvent.hpp"
#include <iostream>
#include <string>
#include <queue>
#include <cstring>

class Application;
class MyQueue;

using namespace std;


class PresentWorkingDirectoryEvent : public BaseEvent
{
	private :
		//MyQueue* mp_queue;
		char* mp_buf;
		int m_cnt;
		int m_mesg_type;
		int m_size;
	public :
		static BaseEvent* get_instance(Application& app, string& m_ip, uint16_t port, int client_no, char* buf, int size);
		PresentWorkingDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no, char* buf, int size);
		~PresentWorkingDirectoryEvent();
		void load();
		char** get_buf();
		void set_buf(char* lp_buf);
		int get_no_strings();
		void set_no_strings(int cnt);
		int get_mesg_type();
		void set_mesg_type(int mesg_type);
		int get_size();
};


#endif
