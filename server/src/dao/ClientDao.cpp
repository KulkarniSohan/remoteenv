#include "ClientDao.hpp"
#include "entities/Client.hpp"
#include "Application.hpp"

ClientDao* ClientDao :: mp_instance = NULL;

ClientDao :: ClientDao (Application& app) : m_app(app)
{
	cout << "ClientDao :: ClientDao" << endl;
}

ClientDao :: ~ClientDao()
{
	cout << "ClientDao :: ~ClientDao" << endl;
}

ClientDao*
ClientDao :: get_instance(Application& app)
{
	cout << "ClientDao :: get_instance" << endl;
	if (mp_instance == NULL)
	{
		mp_instance = new ClientDao(app);
	}
	return mp_instance;
}

void 
ClientDao :: add_client_map(int client_no, shared_ptr<Client> p_client)
{
	cout << "ClientDao :: add_client_map" << endl;
	m_client_map[client_no] = p_client;
}

shared_ptr<Client>
ClientDao :: get_client_map(int client_no)
{
    cout << "ClientDao :: get_client_map " << endl;
    //find logic
    auto itr = m_client_map . find(client_no);
    if (itr == m_client_map . end())
    {
        return nullptr;
    }
    return itr -> second;
}

void
ClientDao :: remove_client_map(int client_no)
{
    cout << "ClientDao :: remove_client_map" << endl;
    m_client_map . erase(client_no);
}
