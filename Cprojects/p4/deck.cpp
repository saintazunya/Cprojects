#include<iostream>
#include "deck.h"
using namespace std;
Deck::Deck(){//constructor

	int i_suit,j_spot;//i for suit, j for spot
	for(i_suit=0;i_suit<4;i_suit++)
	{
		for(j_spot=0;j_spot<13;j_spot++)
		{
			deck[i_suit*13+j_spot].spot=Spot(j_spot);
			deck[i_suit*13+j_spot].suit=Suit(i_suit);
		}
	}
	next=0;
}
void Deck::reset(){
	Deck();
	
}
void Deck::shuffle(int n){
	next=0;//restore the deck
	//requires n in range
	if(n==0){return;}
	if(n<0||n>DeckSize)
		cout<<"Error"<<endl;
	Card *left=new Card[n];
	Card *right=new Card[DeckSize-n];
	// init right and left
	int itr;
	for (itr=0;itr<n;itr++)
		{
			left[itr]=deck[itr];
			//cout<<"left "<< itr <<" "<<SpotNames[left[itr].spot]<<" of "<<SuitNames[left[itr].suit]<<endl;
		}
	for (itr=n;itr<DeckSize;itr++)
		{
			right[itr-n]=deck[itr];
			//cout<<"right "<< itr -n <<" "<<SpotNames[right[itr-n].spot]<<" of "<<SuitNames[right[itr-n].suit]<<endl;
		}
	//init itr to be 0 again.
	itr=0;
	int itr_deck;
	int min_=min(n,DeckSize-n);
	
	for (itr=0;itr<min_;itr++)
		{
			deck[2*itr]=right[itr];
			deck[2*itr+1]=left[itr];
			//cout<<itr<<" in loop, deck.cpp before min"<<endl;
		}
	itr--;
	//cout<<itr<<" in deck.cpp before min"<<endl;
	if(n>DeckSize-n)
		{			
			for (itr_deck=itr*2+2;itr_deck<DeckSize;itr_deck++)
				{	itr++;
					//cout<<"in deck.cpp itr= "<<itr<<"itr_deck=   "<<itr_deck<<endl;
					deck[itr_deck]=left[itr];
				}
		}
	else 
		{
			for (itr_deck=itr*2+2;itr_deck<DeckSize;itr_deck++)
				{	itr++;
					deck[itr_deck]=right[itr];
				}	
		}
	delete[] left;
	delete[] right;
}

Card Deck::deal(){
	if (next==DeckSize)
		{
			DeckEmpty empty;
			throw empty;
		}
	else
		{
			return deck[next++];
		}
}

int Deck::cardsLeft(){
	
	return DeckSize - next;
}
