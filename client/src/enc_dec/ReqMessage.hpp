#ifndef __REQ_MESSAGE_HPP__
#define __REQ_MESSAGE_HPP__


#include <iostream>
#include <string>
#include <linux/limits.h>


using namespace std;


class ReqMessage
{
	private :
		int m_msg_type;
		int m_client_no;
		uint32_t m_ip;
		uint16_t m_port;
		int m_size;
		uint16_t m_self_port;
		char mp_buf[PATH_MAX];
	public :
		ReqMessage();
		~ReqMessage();
		ReqMessage* extract_message(void* lp_event);
		int get_mesg_type();
		uint32_t get_ip();
		uint16_t get_port();
		char* get_buf();
		int get_size();
		int get_client_no();
		uint16_t get_self_port();
		

		void set_mesg_type(int msg_type);
		void set_ip(string& ip);
		void set_port(uint16_t port);
		void set_buf(char* p_buf);
		void set_size(int size);
		void set_client_no(int client_no);
		void set_self_port(uint16_t self_port);

};


#endif
