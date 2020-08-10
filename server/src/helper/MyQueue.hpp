#ifndef __MY_QUEUE_HPP__
#define __MY_QUEUE_HPP__


#include <iostream>
#include <string>
#include <cstring>
#include <linux/limits.h>

using namespace std;


struct Node
{
	char path[PATH_MAX];
	struct Node* next;
};

class MyQueue
{
	private :
		struct Node* head;
	public :
		MyQueue();
		~MyQueue();
		void Append(char* path);
		char* Pop();
		struct Node* get_head_node();
		int count_node();
		void Display();
};


#endif
