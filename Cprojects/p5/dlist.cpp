#ifndef DLIST_CPP
#define DLIST_CPP
#include "dlist.h"
#include <cstdlib>
#include <cassert>
#include <iostream>
template <class T>
Dlist<T>::Dlist():first(0),last(0){}
template <class T>
bool Dlist<T>::isEmpty() const{
	//check if both is empyt
	return(!first&&!last);
}
template <class T>
void Dlist<T>::insertFront(T *op){
	node *np=new node;
	if(isEmpty())
		{
			np->op=op;
			np->prev=NULL;
			np->next=NULL;
			first=np;
			last=np;
		}
	else
		{
			np->next=first;
			first->prev=np;
			np->prev=NULL;
			np->op=op;
			first=np;
		}
}
template <class T>
void Dlist<T>::insertBack(T *op){
	//int tempp=1;//comment it before hand in	
	//cout<<tempp<<endl;
	node *np=new node;
	if(isEmpty())
		{	np->op=op;
			np->prev=NULL;
			np->next=NULL;
			first=np;
			last=np;
		}
	else
		{
			np->prev=last;
			last->next=np;
			np->next=NULL;
			np->op=op;
			last=np;
		}
}
template <class T>
T* Dlist<T>::removeBack(){
	
	node* victim=first;//temp node
	if(isEmpty())
		{
			emptyList ept;
			throw ept;
		}
	T* result=victim->op;
	if(first==last)
		{	//cout<<first<<endl;
			//cout<<last<<endl;
			first=NULL;
			last=NULL;
		}
	else
		{
			first=victim->next;
			first->prev=NULL;
		}
	delete victim;//
	return result;
}
template <class T>
T* Dlist<T>::removeFront(){
	node *victim=first;
	if(isEmpty())
		{
			emptyList ept;
			throw ept;
		}
	T* result=victim->op;
	if(!first)
		{
			first=NULL;
			last=NULL;
		}
	else
		{
			first=victim->next;
			first->prev=NULL;
		}
	delete victim;// needs debuging 
	return result;

}

template <class T>
void Dlist<T>::removeAll(){
	while(!isEmpty())
	{
		T* op=removeBack();
		delete op;
	}
}
template <class T>
Dlist<T>::~Dlist(){//destructor
	removeAll();
}
template <class T>
void Dlist<T>::copyAll(const Dlist &l){//copy constructor
	node *temp=l.first;
	while(temp)
	{
		T* tmp=new T(*temp->op);
		insertBack(tmp);
		temp=temp->next;
	}
	delete temp;
	
}
template <class T>
Dlist<T>& Dlist<T>::operator=(const Dlist &l){//assign operator
	
	if(this!=&l) 
	{
		removeAll();
		copyAll(l);
	}
	return *this;
}
#endif
