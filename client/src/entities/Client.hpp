#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <iostream>
#include <string>

using namespace std;

class Client
{
	private :
		int m_client_no;
		string m_cwd;
		string m_ip_addr;
		uint16_t m_port;
	public :
		Client(int client_no, string& ip_addr, uint16_t port);
		~Client();
		void set_client_no(int client_no);
		int get_client_no();
		void set_cwd(string& cwd);
		string& get_cwd();
		string& get_ip();
		uint16_t get_port();
		void set_ip(string& ip);
		void set_port(uint16_t port);
};



#endif
