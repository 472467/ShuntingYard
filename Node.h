#pragma warning
#ifndef NODE_H
#define NODE_H

#include <string.h>

class Node
{
	private:
		char* c;
		Node* next;
		Node* previous;
	public:
		Node(char*);
		~Node();
		void setChar(char*);
		char* getChar();
		Node* getNext();
		void setNext(Node*);
		Node* getPrevious();
		void setPrevious(Node*);
};
#endif

