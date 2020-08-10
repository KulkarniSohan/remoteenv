#ifndef __BASE_EVENT_HPP__
#define __BASE_EVENT_HPP__


#include <iostream>
#include <string>
using namespace std;

class Application;

class BaseEvent 
{
	protected :
		Application& m_app;
	private :
		string m_ip;
		uint16_t m_port;
		int m_client_no;
	public :
		BaseEvent(Application& app, string& ip, uint16_t port, int client_no) : m_app(app), m_ip(ip), m_port(port), m_client_no(client_no)
		{
			cout << "BaseEvent :: BaseEvent " << endl;
		}
		BaseEvent(Application& app, uint16_t port) : m_app(app),  m_port(port)
		{
			cout << "BaseEvent :: BaseEvent " << endl;
			m_ip = "127.0.0.1";
		}
		BaseEvent(Application& app) : m_app(app)
		{
			cout << "BaseEvent :: BaseEvent " << endl;
		}
		virtual ~BaseEvent()
		{
			cout << "BaseEvent :: ~BaseEvent " << endl;
		}
		string& get_ip()
		{
			cout << "BaseEvent :: get_ip" << endl;
			return m_ip;
		}
		uint16_t get_port()
		{
			cout << "BaseEvent :: get_port" << endl;
			return m_port;
		}
		int get_client_no()
		{
			cout << "BaseEvent :: get_client_no " << endl;
			return m_client_no;
		}
		virtual char* get_buf()
		{
			cout << "BaseEvent :: get_buf" << endl;
			return NULL;
		}
		virtual int get_buf_size()
		{
			cout << "BaseEvent :: get_buf_size" << endl;
			return 0;
		}
		virtual int get_msg_type()
		{
			cout << "BaseEvent :: get_msg_type" << endl;
			return 0;
		}
		virtual void process()
		{
			cout << "BaseEvent :: process" << endl;
		}
		virtual void load()
		{
			cout << "BaseEvent :: load" << endl;
		}
};


#endif
