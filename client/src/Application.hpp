#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__
class MessageController;
class UdpWorker;
class ClientDao;

class Application
{
    private :
        UdpWorker* mp_udp_worker_instance;
		MessageController* mp_mesg_cntrler;
		ClientDao* mp_client_dao;
    public :
        UdpWorker& get_udp_worker()
        {
            return (*mp_udp_worker_instance);
        }
		MessageController& get_mesg_cntrler()
		{
			return (*mp_mesg_cntrler);
		}
		ClientDao& get_client_dao()
		{
			return (*mp_client_dao);
		}
        void startup();
};


#endif
