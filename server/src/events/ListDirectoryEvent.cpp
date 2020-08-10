#include "ListDirectoryEvent.hpp"
#include "Application.hpp"
#include<dirent.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include "helper/MyQueue.hpp"
#include <linux/limits.h>
#include "entities/Client.hpp"
#include "dao/ClientDao.hpp"
#include "controller/MessageController.hpp"

ListDirectoryEvent :: ListDirectoryEvent(Application& app, string& ip, uint16_t port, int client_no, char* buf, int size) : BaseEvent(app, ip, port, client_no)
{
	cout << "ListDirectoryEvent :: ListDirectoryEvent " << endl;
	// implement the ls code from here.
	mp_queue = new MyQueue();
	mp_buf = NULL;
}

BaseEvent*
ListDirectoryEvent :: get_instance(Application& app, string& ip, uint16_t port, int client_no, char* buf, int size)
{
	return new ListDirectoryEvent(app, ip, port, client_no, buf, size);
}

ListDirectoryEvent :: ~ListDirectoryEvent()
{
	cout << "ListDirectoryEvent :: ~ListDirectoryEvent" << endl;
	for (int i = 0; i < m_cnt; i++)
	{
		free(mp_buf[i]);
	}
	free(mp_buf);
	mp_buf = NULL;
	delete mp_queue;	
}

void
ListDirectoryEvent :: load()
{
	cout << "ListDirectoryEvent :: load " << endl;
	shared_ptr<Client> lp_client = m_app . get_client_dao() . get_client_map(get_client_no());
	string dir_path = lp_client -> get_cwd();
	printf ("&&&&&&&&&&&&&&&& PATH = %s\n", dir_path.c_str());
	//char* dir_path = getenv("PWD");
	list_directory((char*)dir_path.c_str());
	mp_queue -> Display();
	m_cnt = mp_queue -> count_node();
	int i = 0;
	mp_buf = (char**) malloc(sizeof(char*) * m_cnt);
	int k = m_cnt;
	int size = 0;
	while (k > 0)
	{
		mp_buf[i] = (char*) calloc (sizeof(char), PATH_MAX);
		char* str = mp_queue -> Pop();
		strncpy(mp_buf[i], str, strlen(str));
		char* l_ptr = mp_buf[i];
		*(l_ptr + strlen(str) + 1) = '\0';
		size = size + strlen(str) + 1;
		i++;
		k--;
	}
	size = size + sizeof(mp_buf);
	m_size = size;
	m_mesg_type = 2;
	queue<void*>& l_ad_cntrler_to_iface_queue = m_app . get_mesg_cntrler() . get_cntrler_to_iface_queue();
	l_ad_cntrler_to_iface_queue . push((void*)this);
}


void
ListDirectoryEvent :: list_directory(char* dir_path)
{
	DIR *dp;
	struct dirent *directory;
	char path[PATH_MAX];
	
	dp = opendir(dir_path);
	if (dp != NULL)
	{
		mp_queue -> Append(dir_path);
		while ((directory = readdir(dp)) != NULL)
		{
			if (strncmp(directory->d_name, ".", strlen(".")) == 0)
        	{
            	continue;
        	}
        	else
        	if (strncmp(directory -> d_name, "..", strlen("..")) == 0)
        	{
            	continue;
        	}
			mp_queue -> Append(directory -> d_name);
			if(directory->d_type == 4)
            {
				sprintf(path,"%s/%s",dir_path,directory->d_name);
				list_directory(path);
			}
		}
	}
}

char** 
ListDirectoryEvent :: get_buf()
{
	return mp_buf;
}
        
void 
ListDirectoryEvent :: set_buf(char** lp_buf)
{
	mp_buf = lp_buf;
}

int 
ListDirectoryEvent :: get_no_strings()
{
	return m_cnt;
}

void 
ListDirectoryEvent :: set_no_strings(int cnt)
{
	m_cnt = cnt;
}

void
ListDirectoryEvent :: set_mesg_type(int mesg_type)
{
	m_mesg_type = mesg_type;
}

int
ListDirectoryEvent :: get_mesg_type()
{
	return m_mesg_type;
}

int
ListDirectoryEvent :: get_size()
{
	return m_size;
}
