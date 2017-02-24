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

int main(){
	Node* stack = new Node("dank");
	char* input = new char[100]; //"5 + ((1 + 2) * 4) - 3";//correct -> 5 1 2 + 4 * + 3 −
	cin.getline(input, 100);
	char* inputSpaceless = removeSpaces(input);
	char* postfix;
	
	stringToStack(stack, input);
	
	Node* current = stack;
	
	
	printNode(stack, current);
	
	convertToPostfix(stack);
	current = stack;
	
	printNode(stack, current);
	//cout << "5 1 2 + 4 * + 3 -";
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
		
		if(isNumber(c)){
			outputQ->setNext(tCurrent);
			tCurrent->setPrevious(outputQ);
			tCurrent->getNext(NULL);
			outputQ = outputQ->getNext();
		}else if(isOperator(c)){
			if(operatorQ->getChar() == ' '){
				operatorQ->setNext(tCurrent);
				tCurrent->setPrevious(operatorQ);
				tCurrent->getNext(NULL);
				operatorQ = operatorQ->getNext();
			}else {
				
			}
		}
		tCurrent = tCurrent->getNext();
	}
	
	
	//keep bumping until you cant bump anymore, only bump operator if it's moved, stop bumping when it passes a certain amount of numbers
	while(tCurrent != NULL){//figures out many numbers an operator should move down
		char* cPoint = (tCurrent)->getChar();
		char c = cPoint[0];
		int bumpTimes = 0;
		if(isOperator(c) && !(tCurrent->getOperatorMoved()) ){//runs only if num is operator and if 
			int remainingNums = 1;
			Node* ultraTCurrent = tCurrent;
			Node* originalOperator = tCurrent;
			bool tInNum = false;
			
			while(remainingNums >= 0 && ultraTCurrent != NULL){//while operator still needs to be pushed down stack
				char* cPoint2 = ultraTCurrent->getChar();
				char c2 = cPoint2[0];//less typing
				
				if(tInNum){//if next num is digit
				
					if(isNumber(c2)){
						
						//do nothing since we are still inNumber
						
					}else{
						
						remainingNums--;
						
					}
				}else{
					if(isNumber(c2)){
						tInNum = true;
					}else if(c2 == '(' || c2 == ')'){
						remainingNums+= 2;
					}
					
					
					
				}
				bumpTimes++;
				
				ultraTCurrent = ultraTCurrent->getNext();
				
				if(remainingNums == 0){
					originalOperator->setOperatorMoved(true);
				}
				
			}
		}else if(c == '(' || c == ')'){
			Node* roflTemp = NULL;
			if(tCurrent->getPrevious() != NULL){
				roflTemp = tCurrent->getPrevious();
			}else if(tCurrent->getNext() != NULL){
				roflTemp = tCurrent->getNext();
			}else{
				cout << "Error: Invalid Size" << endl;
				return NULL;
			}
				
			
			tCurrent->safeDelete();
			tCurrent = roflTemp;
		}
		Node* n = head;
		printNode(head, n);
		
		Node* operatorLoc = tCurrent;
		for(int x = 0; x < bumpTimes; x++){
			
			bumpDown(operatorLoc);
			n = head;
			//printNode(head, n);
			if(operatorLoc->getNext() != NULL){
				operatorLoc = operatorLoc->getNext();
			}
		}
		
		tCurrent = tCurrent->getNext();
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



char* removeSpaces(char* in){//works
	int count = 0;
	while(in[count] != '\0'){	
		count++;
	}
	
	char* out = new char[count+1];
	count = 0;
	int count2 = 0;

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