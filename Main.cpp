#include "Node.h"
#include <string.h>
#include <iostream>

using namespace std;

void shiftHead(Node*&, Node*);
char* removeSpaces(char*);
Node* convertToPostfix(Node*);
void printNode(Node*, Node*);
void stringToStack(Node*, char*);
void bumpDown(Node*);
bool isNumber(char);
bool isOperator(char);
bool checkPrecedence(char, char);
void printHead(Node*);

int main(){
	Node* stack = new Node("dank");
	char* input= new char[50];// ="5 + ((1 + 2) * 4) - 3";//////correct -> 5 1 2 + 4 * + 3 −
	cin.getline(input, 50);
	char* postfix = "5 1 2 + 4 * + 3 −";
	
	stringToStack(stack, input);
	
	Node* current = stack;
	
	
	printNode(stack, current);
	
	convertToPostfix(stack);
	current = stack;
	
	//printNode(stack, current);
	//cout << "5 1 2 + 4 * + 3 -";
}
void stringToStack(Node* head, char* string){
	int counter = 0;
	Node* current = NULL;
	while(string[counter] != '\0'){
		
		if(current != NULL){
			char c = string[counter];
			char* c2 = new char[2];
			strcpy(c2, &c);
			c2[1] = '\0';
			Node* n = new Node(c2);
			
			n->setPrevious(current);
						
			current->setNext(n);
			current = n;
			
		}else{
			char c = string[counter];
			char* c2 = new char[2];
			strcpy(c2, &c);
			c2[1] = '\0';
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
		}else{
			cout << endl;
		}
	}
}


Node* convertToPostfix(Node* head){
	cout << "\n\n";
	Node* tCurrent = head;
	Node* outputQ = new Node(" ");
	Node* operatorQ = new Node(" ");
	
	
	while(tCurrent != NULL){//figures out many numbers an operator should move down
		char* cPoint = (tCurrent)->getChar();
		char c = cPoint[0];
		
		if(isNumber(c)){//if operand than put to output queue

			outputQ->setNext(tCurrent);
			Node* newCurrent = tCurrent->getNext();
			tCurrent->setPrevious(outputQ);
			tCurrent->setNext(NULL);
			tCurrent = newCurrent;
			outputQ = outputQ->getNext();
		}else if(isOperator(c)){

			char* cXPoint = (operatorQ)->getChar();
			char cX = cXPoint[0];
			
			if(cX == ' ' || cX == '('){//FINE

				operatorQ->setNext(tCurrent);
				Node* newCurrent = tCurrent->getNext();
				tCurrent->setPrevious(operatorQ);
				tCurrent->setNext(NULL);
				tCurrent = newCurrent;
				operatorQ = operatorQ->getNext();
				
				
			}else if(checkPrecedence(cX, c)){//if the incoming has higher precendence than the one on the operatorQueue
				cout << c << endl;
				cout << cX << endl;
				operatorQ->setNext(tCurrent);//FINE
				Node* newCurrent = tCurrent->getNext();
				tCurrent->setPrevious(operatorQ);
				tCurrent->setNext(NULL);
				tCurrent = newCurrent;
				operatorQ = operatorQ->getNext();
				
			}else if(!checkPrecedence(cX, c)){//if it has lower or the same operator as one on the queue

				int co = 0;
				while(!checkPrecedence(cX, c)){
					if(operatorQ->getPrevious() != NULL){
						outputQ->setNext(operatorQ);//swaps top of operator stack onto output stack
						Node* previousOperator = operatorQ->getPrevious();
						operatorQ->setPrevious(outputQ);
						operatorQ->setNext(NULL);
						outputQ = outputQ->getNext();
						operatorQ = previousOperator;//moves top of operator stack onto output stack
					}else{
						break;
					}
					if(operatorQ == NULL){
						break;
					}
					//co++;
					//cout << co;
					cXPoint = operatorQ->getChar();
					cX = cXPoint[0];
					
				}
				cout << tCurrent->getChar();
				operatorQ->setNext(tCurrent);
				Node* newCurrent = tCurrent->getNext();
				tCurrent->setPrevious(operatorQ);
				tCurrent->setNext(NULL);
				tCurrent = newCurrent;
				operatorQ = operatorQ->getNext();
				
			}
		}else if(c == '('){//if left parentheses shove into operator queue

			operatorQ->setNext(tCurrent);
			Node* newCurrent = tCurrent->getNext();
			tCurrent->setPrevious(operatorQ);
			tCurrent->setNext(NULL);
			tCurrent = newCurrent;
			operatorQ = operatorQ->getNext();
			
		}else if(c == ')'){//
 
			tCurrent = tCurrent->getNext();
			char* opTemp = operatorQ->getChar();
			char opChar = opTemp[0];
			int co = 0;
			
			while(opChar != '('){//place operators on output until u find the left parentheses
				if(operatorQ->getPrevious() != NULL){
					Node* previousOp = operatorQ->getPrevious();
					outputQ->setNext(operatorQ);
					operatorQ->setPrevious(outputQ);
					operatorQ->setNext(NULL);
					outputQ = outputQ->getNext();
					operatorQ= previousOp;
				}else{
					break;
				}
				opTemp = operatorQ->getChar();
				opChar = opTemp[0];
				
				//co++;
				//cout << co;
				
			}
			Node* o = operatorQ->getPrevious();
			//operatorQ->safeDelete();//removes right parentheses
			operatorQ = o;
		}else if(c == ' ' ){

			outputQ->setNext(tCurrent);
			Node* newCurrent = tCurrent->getNext();
			tCurrent->setPrevious(outputQ);
			tCurrent->setNext(NULL);
			tCurrent = newCurrent;
			outputQ = outputQ->getNext();
			
		}
		//printHead(operatorQ);
		//printHead(operatorQ);
	}
	char* opTemp = operatorQ->getChar();
	char opChar = opTemp[0];

	
	while(isOperator(opChar)){
		Node* previousOp = operatorQ->getPrevious();
		outputQ->setNext(operatorQ);
		operatorQ->setPrevious(outputQ);
		operatorQ->setNext(NULL);
		outputQ = outputQ->getNext();
		operatorQ= previousOp;
		if(operatorQ == NULL){
			break;
		}
		
		opTemp = operatorQ->getChar();
		opChar = opTemp[0];
		
		
	}
	

	printHead(outputQ);
	return NULL;
}

void printHead(Node* current){
	int count = 0;
	while(current->getPrevious() != NULL){
		count++;
		current = current->getPrevious();
	}
	cout << count << " below current." << endl;
	Node* tCurrent = current;
	printNode(current, tCurrent);
}

bool checkPrecedence(char o1, char o2){//left associative, checks if first operator has higher precedence than second
//false on equavelence
	if(o1 == '^'){
		if(o2 == '^'){
			return false;
		}else if(o2 == '*'){
			return false;
		}else if(o2 == '/'){
			return false;
		}else if(o2 == '+'){
			return false;
		}else if(o2 == '-'){
			return false;
		}
	}else if(o1 == '*'){
		if(o2 == '^'){
			return true;
		}else if(o2 == '*'){
			return false;
		}else if(o2 == '/'){
			return false;
		}else if(o2 == '+'){
			return false;
		}else if(o2 == '-'){
			return false;
		}
	}else if(o1 == '/'){
		if(o2 == '^'){
			return true;
		}else if(o2 == '*'){
			return true;
		}else if(o2 == '/'){
			return false;
		}else if(o2 == '+'){
			return false;
		}else if(o2 == '-'){
			return false;
		}
	}else if(o1 == '+'){
		if(o2 == '^'){
			return true;
		}else if(o2 == '*'){
			return true;
		}else if(o2 == '/'){
			return true;
		}else if(o2 == '+'){
			return false;
		}else if(o2 == '-'){
			return false;
		}
	}else if(o1 == '-'){
		if(o2 == '^'){
			return true;
		}else if(o2 == '*'){
			return true;
		}else if(o2 == '/'){
			return true;
		}else if(o2 == '+'){
			return true;
		}else if(o2 == '-'){
			return false;
		}
	}
	
	return NULL;
}

bool isNumber(char c){
	if(c == '0'){
		return true;
	}else if(c == '1'){
		return true;
	}else if(c == '2'){
		return true;
	}else if(c == '3'){
		return true;
	}else if(c == '4'){
		return true;
	}else if(c == '5'){
		return true;
	}else if(c == '6'){
		return true;
	}else if(c == '7'){
		return true;
	}else if(c == '8'){
		return true;
	}else if(c == '9'){
		return true;
	}
	return false;
}

bool isOperator(char c){
	if(c == '-'){
		return true;
	}else if(c == '+'){
		return true;
	}else if(c == '/'){
		return true;
	}else if(c == '*'){
		return true;
	}else if(c == '^'){
		return true;
	}
	
	return false;
		
}

void bumpDown(Node* test){
	if(test->getNext() == NULL){

	}else{
		Node* next = test->getNext();
		char* nextChar = next->getChar();
		bool nextBool = next->getOperatorMoved();
		
		next->setChar(test->getChar());
		next->setOperatorMoved(test->getOperatorMoved());
		
		test->setChar(nextChar);
		test->setOperatorMoved(nextBool);

	}
	
}

void shiftHead(Node*& oldHead, Node* newHead){//works
	newHead->setNext(oldHead->getNext());
	newHead->setPrevious(NULL);
	delete oldHead->getChar();
	oldHead = newHead;
}