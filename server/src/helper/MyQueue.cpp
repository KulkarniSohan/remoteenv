#include "MyQueue.hpp"

MyQueue :: MyQueue()
{
	cout << "MyQueue :: MyQueue" << endl;
	head = NULL;
}

MyQueue :: ~MyQueue()
{
	cout << "MyQueue :: ~MyQueue" << endl;
	head = NULL;
}

void
MyQueue :: Append(char* path)
{
	//cout << "MyQueue :: Append" << endl;
	struct Node* newnode = (struct Node*) malloc(sizeof (struct Node));
	strncpy(newnode->path, path, strlen(path));
	newnode -> next = NULL;
	if (head == NULL)
    {
        head = newnode;
    }
	else
	{
		struct Node* temp = head;
        newnode -> next = temp;
        head = newnode;
	}
}

char*
MyQueue :: Pop()
{
	//cout << "MyQueue :: Delete" << endl;
	struct Node *temp = head;
    if(temp != NULL)
    {
        head = temp->next;
		char* list_str = new char[strlen(temp -> path) + 1];
        strncpy(list_str, temp -> path, strlen(temp -> path));
		//*(list_str + strlen(temp -> path) + 1) = '\0';
        free(temp);
        return list_str;
    }
    else
    {
        return NULL;
    }
}

struct Node*
MyQueue :: get_head_node()
{
	return head;
}

int
MyQueue :: count_node()
{
	int count = 0;
	struct Node* temp = head;
	while (temp != NULL)
	{
		count++;
		temp = temp -> next;
	}
	return count;
}

void
MyQueue :: Display()
{
	struct Node* temp = head;
	while (temp != NULL)
	{
		printf ("%s\n", temp -> path);
		temp = temp -> next;
	}
}

