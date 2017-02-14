#include "Node.h"
#include <string.h>
#include <iostream>

using namespace std;

void shiftHead(Node*&, Node*);
char* removeSpaces(char*);
char* convertToPostfix(char*);

int main(){
	Node* stack = new Node("dank");
	char* input = "5 + ((1 + 2) x 4) - 3";//correct -> 5 1 2 + 4 × + 3 −
	char* inputSpaceless = removeSpaces(input);
	char* postfix;
	
	strcpy(inputSpaceless, inputSpaceless);
	cout << inputSpaceless;
	
	
	
}
Node* stringToStack(Node*& head, char* string){
	
	
	
}

char* convertToPostfix(char* in){
	char* out;
	
	
	
}


char* removeSpaces(char* in){
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

void shiftHead(Node*& oldHead, Node* newHead){
	newHead->setNext(oldHead->getNext());
	newHead->setPrevious(NULL);
	delete oldHead->getChar();
	oldHead = newHead;
}