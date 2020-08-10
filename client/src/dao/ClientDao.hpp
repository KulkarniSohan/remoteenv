#ifndef __CLIENT_DAO_HPP__
#define __CLIENT_DAO_HPP__


#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

using namespace std;
class Client;
class Application;


class ClientDao
{
	private :
		Application& m_app;
		unordered_map<int, shared_ptr<Client>> m_client_map;
		ClientDao(Application& app);
	public :
		~ClientDao();
		static ClientDao* mp_instance;
        static ClientDao* get_instance(Application& app);
		void add_client_map(int client_no, shared_ptr<Client> p_client);
		shared_ptr<Client> get_client_map(int client_no);
		void remove_client_map(int client_no);
};


#endif
