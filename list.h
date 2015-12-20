// fig 15.3

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <assert.h>

#include "listnd.h"

using namespace std;


template <class NODETYPE>
class List {
	public:
		List();
		~List();
		void insertAtFront(const NODETYPE &);
		void insertAtBack(const NODETYPE &);
		bool removeFromFront(NODETYPE &);
		bool removeFromBack(NODETYPE &);
		bool isEmpty() const;
		void print() const;
		NODETYPE getFirst() const;
		NODETYPE getLast() const;
		
		NODETYPE getMax() const;
		NODETYPE getMin() const;
		// these arent working
		bool deleteNode(int &); // deleted the nth element of the list, starting from 1
		bool insertNode(const NODETYPE &, int &); // insert a node at some index value, starts at 1
		
	private:
		ListNode <NODETYPE> *firstPtr;
		ListNode <NODETYPE> *lastPtr;
		ListNode <NODETYPE> *getNewNode(const NODETYPE &);
		
};


template <class NODETYPE>
List <NODETYPE>::List() : firstPtr(0), lastPtr(0) {}

template <class NODETYPE>
List <NODETYPE>::~List(){

	if (!isEmpty()){
		//cout << "Destroying nodes" << endl;
		ListNode <NODETYPE> *currentPtr = firstPtr;
		ListNode <NODETYPE> *tempPtr;
		
		while (currentPtr != 0){
			tempPtr = currentPtr;
			//cout << tempPtr->data << endl; // turned this off for ttc
			currentPtr = currentPtr->nextPtr;
			delete tempPtr;
		}
	}
	
	//cout << "All node are destroyed " << endl;
}


template <class NODETYPE>
void List<NODETYPE>::insertAtFront(const NODETYPE &value){
	
	ListNode <NODETYPE> *newPtr = getNewNode(value);
	
	if (isEmpty()){
		lastPtr = newPtr;
		firstPtr = lastPtr;
	}else{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
}

template <class NODETYPE>
void List <NODETYPE>::insertAtBack(const NODETYPE &value){
	ListNode <NODETYPE> *newPtr = getNewNode(value);
	
	if (isEmpty()){
		firstPtr = lastPtr = newPtr;
	}else{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}
}


template <class NODETYPE>
bool List <NODETYPE>::removeFromFront(NODETYPE &value){

	if (isEmpty()){
		return false;
	}else{
		ListNode <NODETYPE> *tempPtr = firstPtr;
		
		if( firstPtr == lastPtr){
			firstPtr = lastPtr = 0;
		}else{
			firstPtr = firstPtr->nextPtr;
		}
		
		value = tempPtr->data;
		delete tempPtr;
		return true;
	}
}

template <class NODETYPE>
bool List<NODETYPE>::removeFromBack(NODETYPE &value){
	if (isEmpty()){
		return false;
	}else{
		ListNode <NODETYPE> *tempPtr = lastPtr;
		
		if (firstPtr == lastPtr){
			firstPtr = lastPtr = 0;
		}else{
			ListNode <NODETYPE> *currentPtr = firstPtr;
			
			while (currentPtr->nextPtr != lastPtr){
				currentPtr = currentPtr->nextPtr;
			}
			
			lastPtr = currentPtr;
			currentPtr->nextPtr = 0;
		}
		
		value = tempPtr->data;
		delete tempPtr;
		return true;
	}
}


template <class NODETYPE>
bool List <NODETYPE>::isEmpty() const{
	return firstPtr == 0;
}

template <class NODETYPE> 
ListNode <NODETYPE> *List <NODETYPE>::getNewNode(const NODETYPE &value){
	
	ListNode <NODETYPE> *ptr = new ListNode <NODETYPE> (value);
	assert(ptr!=0);
	return ptr;
}

template <class NODETYPE>
void List <NODETYPE>::print() const{
	
	if (isEmpty()){
		cout << "The list is empty " << endl;
		return;
	}
	
	ListNode <NODETYPE> *currentPtr = firstPtr;
	cout << "The list is " << endl;
	while (currentPtr != NULL){
		cout << currentPtr->data << " ";
		currentPtr = currentPtr->nextPtr;
	}
	
	cout << "\n\n";
	
}

template <class NODETYPE>
NODETYPE List<NODETYPE>::getFirst() const{
	
	return firstPtr->getData();
}



template<class NODETYPE>
NODETYPE List<NODETYPE>::getLast() const{
	
	return lastPtr->getData();
}

template<class NODETYPE>
NODETYPE List<NODETYPE>::getMax() const{
	//cout << "getmax is called " << endl;
	
	//cout << firstPtr << endl;
	
	ListNode<NODETYPE> *current = firstPtr;
	//cout << "current " << current << endl;
	
	NODETYPE max = firstPtr->data;
	//cout << "max " << max << endl;
	
	current = current->nextPtr;
	
	while (current != NULL){
		if (current->data > max){
			max = current->data;
		}
		current = current->nextPtr;
	}
	
	//cout << "max " << max << endl;
	
	return max;
}

template<class NODETYPE>
NODETYPE List<NODETYPE>::getMin() const{
	
	//cout << "getMin() is called " << endl;
	
	ListNode<NODETYPE> *current = firstPtr;
	NODETYPE min = firstPtr->data;
	current = current->nextPtr;
		
	while (current != NULL){
		if (current->data < min){
			min = current->data;
		}
		current = current->nextPtr;
	}
	
	return min;
	
}

template<class NODETYPE>
bool List<NODETYPE>::deleteNode(int &index){ // indexing unlike arrays, starts at 1
	
	if (index == 1){
		NODETYPE null;
		return removeFromFront(null);
	}
	
	ListNode<NODETYPE> *current = firstPtr;
		
	for (int i = 1; i < index - 1; i++){
		if (current == NULL){
			cout << "The list does not have that many elements" << endl;
			return false;
		}
		
		current = current->nextPtr;
	}
	
	// current points to the node prior to the one to be deleted
	// check that current->next is not null;
	
	if (current->nextPtr == NULL){ // if this is the last node
		cout << "List does not have that many elements " << endl;
		return false;
	}else if (current->nextPtr->nextPtr == NULL){ 	// check if the element to be deleted is the last on
		NODETYPE null;
		return removeFromBack(null);
	}else{
		ListNode<NODETYPE> *temp = current->nextPtr;
		
		current->nextPtr = current->nextptr->nextPtr;
		delete temp;
		return true;
	}
	
}

template<class NODETYPE>
bool List<NODETYPE>::insertNode(const NODETYPE &value, int &index){
	
	if (index == 1){
		return insertAtFront(value);
	}
	
	ListNode<NODETYPE> *current = firstPtr;
		
	for (int i = 1; i < index - 1; i++){
		if (current == NULL){
			cout << "The list does not have that many elements." << endl;
			return false;
		}
		
		current = current->nextPtr;
	}
	
	if (current->nextPtr == NULL){ // if current points to the last node
		
		return insertAtBack(value);
	}else{
		ListNode<NODETYPE> *temp = current->nextPtr;
		ListNode<NODETYPE> *newNode = getNewNode(value);
		
		current->nextPtr = newNode;
		newNode->nextPtr = temp->next->next;
		
		delete temp;
		return true;
	}	
}

#endif


	
	
	
	
	
