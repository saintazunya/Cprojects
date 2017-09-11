#include "player.h"
#include<cassert>
#include<iostream>
using namespace std;
class SimplePlayer:public Player{
    public:
		virtual int bet(unsigned int bankroll, unsigned int minbet);
	    bool draw(Card dealer, const Hand &playerhand);
		virtual void expose(Card c);
		virtual void shuffled();
};
/*-------------------imp--------------------------------*/
int SimplePlayer::bet(unsigned int bankroll, unsigned int minbet){
	if (bankroll<minbet)
		{assert(0);}
	else
		{return minbet;}
}

bool SimplePlayer::draw(Card dealer, const Hand &playerhand){
	bool playersoft=playerhand.handValue().soft;
	int optimvalue=playerhand.handValue().count;
	if (!playersoft)//if not soft
		{
			if(optimvalue<12)
				{return true;}
			else if(optimvalue==12)
				{
					if(dealer.spot==FOUR||dealer.spot==FIVE||dealer.spot==SIX)
						{return false;}
					else
						{return true;}
				}
			else if(optimvalue>12&&optimvalue<17)
				{
					if(dealer.spot==TWO||dealer.spot==THREE||dealer.spot==FOUR||dealer.spot==FIVE||dealer.spot==SIX)
						{return false;}
					else
						{return true;}
					
				}
			else
				{return false;}
		}
	else if(playersoft)// if soft
		{
			if(optimvalue<18)
				{return true;}
			else if(optimvalue==18)
				{
					if (dealer.spot==TWO||dealer.spot==SEVEN||dealer.spot==EIGHT)
						{return false;}
					else
						{return true;}
				}
			else
				{return false;}
		}
	else
		{assert(0);}
}

void SimplePlayer::expose(Card c){}//doing nothing
void SimplePlayer::shuffled(){}//doing nothing
static SimplePlayer simple;
Player *get_Simple(){
	return &simple;
}
/*------------------------------------count player----------------------------*/

class countplayer:public SimplePlayer{
	//derived class from simple player.
	int count;
public:
	countplayer();//"initialBank" is a user input.
	int bet(unsigned int bankroll, unsigned int minbet);
	void expose(Card c);
	void shuffled();
};

countplayer::countplayer():count(0){//constructor
	//init count to be 0;
}
int countplayer::bet(unsigned int bankroll, unsigned int minbet){
	//cout<<"this is the counting layer"<<endl;
	if(bankroll>=2*minbet && count>=2)
		return 2*minbet;
	else if(bankroll>=minbet)
		return minbet;
	else
	{
		assert(0);
		throw bankroll;
	}
}

void countplayer::expose(Card c){
	//cout<<"this is counting player exposed"<<endl;
	if (c.spot>=0&&c.spot<=4)
	{
		count++;
	}
	else if(c.spot==TEN||c.spot==JACK||c.spot==QUEEN||c.spot==KING||c.spot==ACE)
	{
		count--;
	}
	else
		{}
	//cout<<"this is current count value "<<count<<endl;
}
void countplayer::shuffled(){
	//restore count to be 0;
	count=0;
}
static countplayer Count;
Player *get_Counting(){
	return &Count;
}

