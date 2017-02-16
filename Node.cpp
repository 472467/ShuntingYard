#include "Node.h"

Node::Node(char* c2){
	c = new char[2];
	strcpy(c, c2);
	next = NULL;
	previous = NULL;
	
}

Node::~Node(){
	delete c;
	delete next;
	delete previous;
	delete this;
}

void Node::setChar(char* c2){
	strcpy(c, c2);
}

char* Node::getChar(){
	return c;
}

Node* Node::getPrevious(){
	return previous;
}

void Node::setPrevious(Node* p){
	previous = p;
}

Node* Node::getNext(){
	return next;
}

void Node::setNext(Node* n){
	next = n;
	
}