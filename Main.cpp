#include "Node.h"
#include <string.h>
#include <iostream>

using namespace std;

void shiftHead(Node*&, Node*);
char* removeSpaces(char*);
char* convertToPostfix(char*);
void printNode(Node*, Node*);
void stringToStack(Node*, char*);

int main(){
	Node* stack = new Node("dank");
	char* input = "5 + ((1 + 2) x 4) - 3";//correct -> 5 1 2 + 4 × + 3 −
	char* inputSpaceless = removeSpaces(input);
	char* postfix;
	
	strcpy(inputSpaceless, inputSpaceless);
	cout << inputSpaceless << endl;
	
	stringToStack(stack, inputSpaceless);
	
	Node* current = stack;
	printNode(stack, current);
	
}
void stringToStack(Node* head, char* string){
	int counter = 0;
	//cout << counter << endl;
	Node* current = NULL;
	while(string[counter] != '\0'){
		
		if(current != NULL){
			char c = string[counter];
			char* c2 = new char[2];
			strcpy(c2, &c);
			c2[2] = '\0';
			Node* n = new Node(c2);
			
			n->setPrevious(current);
						
			current->setNext(n);
			current = n;
			
		}else{
			char c = string[counter];
			char* c2 = new char[2];
			strcpy(c2, &c);
			c2[2] = '\0';
			head->setChar(c2);// = new Node(c);
			
			current = head;
		}
		
		counter++;
		
	}
	
	
}

void printNode(Node* sourceNode, Node* currentNode){//prints node thr
	if((currentNode)->getPrevious() == NULL) {//if the currentNode is the first node in the list
		try{//this runs to prevent an error when list is empty, probably never fails here
			cout << currentNode->getChar();
			if(sourceNode->getNext() != NULL){
				currentNode = sourceNode->getNext();
				printNode(sourceNode, currentNode);
			}
			
		}catch (const exception& e){
			cout << "StudentList is empty.";
		}

	}else{
		cout << currentNode->getChar();
		
		if(currentNode->getNext() != NULL){
			currentNode = currentNode->getNext();
			printNode(sourceNode, currentNode);
		}
	}
}


char* convertToPostfix(char* in){
	char* out;
	
	
	
}


char* removeSpaces(char* in){//works
	int count = 0;
	while(in[count] != '\0'){	
		count++;
	}
	
	char* out = new char[count+1];
	count = 0;
	int count2 = 0;
	cout << "test"<< endl;
	while(in[count] != '\0'){
		//cout << in[count] << endl;;
		if(in[count] != ' ' && in[count] != '\0'){
			out[count2] = in[count];
			count2++;
		}
		count++;
	}
	out[count2] = '\0';
	
	return out;
}

void shiftHead(Node*& oldHead, Node* newHead){//works
	newHead->setNext(oldHead->getNext());
	newHead->setPrevious(NULL);
	delete oldHead->getChar();
	oldHead = newHead;
}