#include "Node.h"

Node::Node(char* c2){
	c = new char[2];
	strcpy(c, c2);
	next = NULL;
	previous = NULL;
	
}

Node::~Node(){
	delete c;
	//delete next;
	//delete previous;
	delete this;
}

bool Node::safeDelete(){
	if(getNext() != NULL && getPrevious() != NULL){
		getNext()->setPrevious(previous);
		getPrevious()->setNext(getNext());
		delete this;
		return true;
		
	}else if(getNext() != NULL){//localPrevious is NULL, means its head of NODE
		setChar((getNext())->getChar());
		if(getNext()->getNext() != NULL){//this kills the next one and takes data of its next
			setNext((getNext())->getNext());
			(getNext()->getNext())->setPrevious(this);
			delete getNext();
			return true;
		}else{
			delete getNext();
			setNext(NULL);
			return true;
		}
	}else if(getPrevious() != NULL){
		getPrevious()->setNext(NULL);
		delete this;
		return true;
	}else{
		delete this;
		return true;
	}
	return true;
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