#ifndef __DISPLAY_MENU_HPP__
#define __DISPLAY_MENU_HPP__


#include <iostream>

using namespace std;


class DisplayMenu
{
	private :
		Application& m_app;
		pthread_t m_display_thread;
		
	public :
		DisplayMenu();
		~DisplayMenu();
		void init();
		
};



#endif
