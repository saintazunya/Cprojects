#include"hand.h"
#include<iostream>
#include<cassert>
using namespace std;
Hand::Hand(){// constructor
	curValue.count=0;
	curValue.soft=false;//default soft value to be false.
}
void Hand::addCard(Card c){
	//different from value of c. 
	if (c.spot < 9)//prue number
		{curValue.count+=(c.spot+2);}
	else if (c.spot>=9&&c.spot<12)//c.spot=JACK ~ KING.
		{curValue.count+=10;}
	else if (curValue.count<11&&c.spot==12)//c.spot is ACE, count as 11
		{
			curValue.soft=true;
			curValue.count+=11;
		}
	else if (curValue.count>=11&&c.spot==12)//c.spot is ACE, count as 1
		{curValue.count+=1;}
	else 
		{	
			cout<<"c.spot value is "<<c.spot<<endl;
			cout<<"Error in addCard"<<endl;
			assert(0);
		}
/*----------------------------------------------------*/
	if (curValue.soft&&curValue.count>21)//if already an ace on hand
		{
			curValue.count-=10;
			curValue.soft=false;
		}	
}

HandValue Hand::handValue() const
{
	return curValue;
}
void Hand::discardAll()
{
	curValue.count=0;
	curValue.soft=false;
}
