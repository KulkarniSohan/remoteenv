#ifndef __RESP_MESSAGE_HPP__
#define __RESP_MESSAGE_HPP__


#include <iostream>
#include <string>
#include <linux/limits.h>

using namespace std;

struct Buffer
{
	char str[PATH_MAX];
};

class RespMessage
{
	private :
		int m_msg_type;
		int m_client_no;
		char m_ip[16];
		uint16_t m_port;
		char str[PATH_MAX];
	public :
		RespMessage();
		~RespMessage();
		RespMessage* extract_message(void* lp_event);
		int get_mesg_type();
		char* get_ip();
		uint16_t get_port();
		//struct Buffer* get_buf();
        int get_size();
		int get_client_no();
		int get_no_strings();
		char* get_string();

		void set_mesg_type(int msg_type);
		void set_ip(string& ip);
		void set_port(uint16_t port);
		//void set_buf(char** p_buf, int no_of_strings);
		void set_client_no(int client_no);
		void set_no_strings(int no_strings);
        void set_size(int size);
		void set_string(char* str);
};


#endif
