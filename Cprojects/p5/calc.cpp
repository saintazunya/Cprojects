#include "dlist.h"
#include "dlist.cpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;

struct complex{
	int re;
	int im;
};
class calcEmpty
{
};

class calc
{
	//OVERVIEW:The interpretations of the method functions are copied from the slide.
	Dlist<complex> Thecalc;
	int elenum;
public:
	// Operational methods
	int size();
	bool isEmpty();
	void push(complex o);
	void pop();
	complex &top();
	calc();//constructor
	calc(const calc &s);//copy constructor
	calc &operator=(const calc &s);//assignment operator
	~calc();//desructor
};
calc::calc():Thecalc(){elenum=0;}//constructor
calc::calc(const calc &s):Thecalc(){//copy constructor
		Thecalc=s.Thecalc;
		elenum=s.elenum;
}

calc &calc::operator=(const calc &s){
	Thecalc=s.Thecalc;
	elenum=s.elenum;
	return *this;//this is a pointer
	
}
calc::~calc(){
	Thecalc.~Dlist();
}
bool calc::isEmpty(){
	return Thecalc.isEmpty();
}

int calc::size(){
	return elenum;
}
void calc::push(complex o){
	complex *a=new complex(o);//A dynamically created object.
	Thecalc.insertFront(a);
	elenum++;
}

void calc::pop(){
	try 
		{
			complex *a=Thecalc.removeFront();
			delete a;
			elenum--;
		}
	catch (emptyList ept)
		{
			calcEmpty u;
			throw u;
		}
}

complex& calc::top()
{
	try 
		{
			complex *o=Thecalc.removeFront();//remove it and insert it back.
			Thecalc.insertFront(o);
			return *o;
		}
	catch (emptyList ept)
		{
			calcEmpty u;
			throw u;
		}
}

void add(calc &RPN){
	if (RPN.size()<2)
		cout << "Not enough operands\n";
	else
		{
			complex fir,sec,res;
			fir=RPN.top();
			RPN.pop();
			sec=RPN.top();
			RPN.pop();
			res.re=fir.re+sec.re;
			res.im=fir.im+sec.im;
			RPN.push(res);	
			//cout<<RPN.top().re<<RPN.top().im<<endl;
		}
}
void mus(calc &RPN){
	if (RPN.size()<2)
		cout << "Not enough operands\n";
	else
		{
			complex fir,sec,res;
			fir=RPN.top();
			RPN.pop();
			sec=RPN.top();
			RPN.pop();
			res.re=-fir.re+sec.re;
			res.im=-fir.im+sec.im;
			RPN.push(res);	
			//cout<<RPN.top().re<<RPN.top().im<<endl;
		}
}
void mlt(calc &RPN){
	if (RPN.size()<2)
		cout << "Not enough operands\n";
	else
		{
			complex fir,sec,res;
			fir=RPN.top();
			RPN.pop();
			sec=RPN.top();
			RPN.pop();
			res.re=fir.re*sec.re-fir.im*sec.im;
			res.im=fir.re*sec.im+fir.im*sec.re;
			RPN.push(res);	
			//cout<<RPN.top().re<<RPN.top().im<<endl;
		}
}
void neg(calc &RPN){
	if (RPN.size()<1)
		cout << "Not enough operands\n";
	else
		{
			complex fir,res;
			fir=RPN.top();
			RPN.pop();
			res.re=-fir.re;
			res.im=-fir.im;
			RPN.push(res);	
			//cout<<RPN.top().re<<RPN.top().im<<endl;
		}
}
void dup(calc &RPN){
	if (RPN.size()<1)
		cout << "Not enough operands\n";
	else
		{
			complex fir;
			fir=RPN.top();
			RPN.pop();
			RPN.push(fir);	
			RPN.push(fir);
			//cout<<RPN.top().re<<RPN.top().im<<endl;
		}
}
void rev(calc &RPN){
	if (RPN.size()<2)
		cout << "Not enough operands\n";
	else
		{
			complex fir,sec;
			fir=RPN.top();
			RPN.pop();
			sec=RPN.top();
			RPN.pop();
			RPN.push(fir);
			RPN.push(sec);
			//cout<<RPN.top().re<<RPN.top().im<<endl;
		}
}
void clc(calc &RPN){
	while(RPN.size()>0)
		RPN.pop();
}
void prt(calc &RPN){
	calc temp;
	temp=RPN;
	while(temp.size()>0)
	{	
		cout<<temp.top().re;
		if (temp.top().im>=0)
			cout<<"+";
		cout<<temp.top().im<<"i"<<" ";
		temp.pop();
	}
	cout<<endl;
}
void ptp(calc &RPN){
	if (RPN.size()<1)
		cout << "Not enough operands\n";
	calc temp;
	temp=RPN;
	cout<<temp.top().re;
	if(temp.top().im>=0)
		cout<<"+";
	cout<<temp.top().im<<"i"<<endl;
}
int main()
{
	calc RPN;
	string in,op,ifi;
	istringstream temp;
	while (cin>>in)
	{		//cout<<in<<endl;
			complex a;
			temp.str(in);
			//cout<<in<<endl;
			if(temp>>a.re)
				{	
					//cout<<"fuck"<<endl;
					temp>>a.im>>ifi;
					if(ifi!="i")
						cout << "Bad input\n";
					else	
						RPN.push(a);
					temp.clear();
					
				}
			else 
				{	
					temp>>in;
					//cout<<in<<endl;
					if(in.length()>1)
						cout << "Bad input\n";
					else
						{
							switch(in.c_str()[0])
								{
									case '+':
										add(RPN);
										break;
									case '-':
										mus(RPN);
										break;
									case '*':
										mlt(RPN);
										break;
									case 'n':
										neg(RPN);
										break;
									case 'd':
										dup(RPN);
										break;
									case 'r':
										rev(RPN);
										break;
									case 'c':
										clc(RPN);
										break;
									case 'a':
										prt(RPN);
										break;
									case 'p':
										ptp(RPN);
										break;
									case 'q':
										exit(0);
										break;
									default:
										cout << "Bad input\n";
										break;
							}
						}
				
					temp.clear();	
				}
				//cout<< "not a number"<<endl;
			//cout<<a.re<<a.im<<endl;
	}
	
	
	
}
