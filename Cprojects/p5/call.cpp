#include "dlist.h"
#include "dlist.cpp"
#include <string>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;
enum Status{
	Regular,Silver,Gold,Platinum
};
const string statusName[]={"regular","silver","gold","platinum"};
class queueEmpty 
{
};
struct event
{	string origstr;
	int timestamp;//call in time
	string name;
	Status status;
	int waiting;//time customer will wait
	int waited;//time waited
	int duration;
};
class queue{
	
	Dlist<event> Myqueue;
	int elenum;
public:
	int size();
	void push(event *o);
	void pushfront(event *o);
	void pop();
	event &top();
	bool isEmpty();
	void tick_plusOne_hang(int tick);
	void tick_plusOne_call(int tick);
	queue();//constructor
	queue(const queue &s);//copy constructor
	queue &operator=(const queue &s);//assignment operator
	~queue();//desructor
};
queue::queue():Myqueue(){elenum=0;}
queue &queue::operator=(const queue &s){
	Myqueue=s.Myqueue;
	elenum=s.elenum;
	return *this;//this is a pointer
	
}
queue::~queue(){
	Myqueue.~Dlist();
}
bool queue::isEmpty(){
	return Myqueue.isEmpty();
}

int queue::size(){
	return elenum;
}
void queue::push(event *o){
	//event *a=new event(o);//A dynamically created object.
	Myqueue.insertBack(o);
	elenum++;
}
void queue::pushfront(event *o){
	//event *a=new event(o);//A dynamically created object.
	Myqueue.insertFront(o);
	elenum++;
}
void queue::pop(){
	try 
		{
			event *a=Myqueue.removeFront();
			delete a;
			elenum--;
		}
	catch (queueEmpty ept)
		{
			queueEmpty u;
			throw u;
		}
}

event& queue::top()
{
	try 
		{
			event *o=Myqueue.removeFront();//remove it and insert it back.
			Myqueue.insertFront(o);
			return *o;
		}
	catch (queueEmpty ept)
		{
			queueEmpty u;
			throw u;
		}
}
void queue::tick_plusOne_hang(int tick)
{	int i,ele_temp;
	ele_temp=elenum;
	//cout<<tick<<"elenum "<<elenum<<endl;
	if(elenum==0)
		{
			//cout<<"This que is already empty"<<endl;
		}
	else
		{
			for (i=0;i<ele_temp;i++)
			{	
				event *temp=new event;
				*temp=top();
				pop();
				//cout<<temp->origstr<<" "<<endl;
				if (temp->timestamp>tick)
					{
						push(temp);	
					}
				else
					{
						temp->waited++;
						//cout<<temp->name<<" time waited: "<<temp->waited << " time waiting: "<<temp->waiting<<endl;
						//cout<<temp->name<<" status: "<<statusName[temp->status]<<" this is time waited: "<<temp->waited<<endl;
						if (temp->waited>temp->waiting)
							{	
								cout<<temp->name<< " hangs up"<<endl;
								//cout<<"current elenum after hang up"<<elenum<<endl;
								delete temp;
							}
						else 
							{
								push(temp);
							}
					}
			}
			
				
		}
		//cout<<top().name<<endl;

}
void queue::tick_plusOne_call(int tick)
{	int i,ele_temp;
	ele_temp=elenum;
	//cout<<"elenum in tick_plusOne_call: "<<elenum<<endl;;
	if(elenum==0)
		{
			//cout<<"This que is already empty"<<endl;
		}
	else{		
				//cout<<top().name<<" ";
				//cout<<"tick: "<<tick<<" and timestamp: "<<top().timestamp<<endl;
				for (i=0;i<ele_temp;i++)
				{	
					event *temp=new event;
					*temp=top();
					pop();
				if (temp->timestamp>tick)
					{
						push(temp);	
					}
				//else if (temp->timestamp<tick){}
				else
					{
						//cout<<temp->name<<" time waited: "<<temp->waited << " time waiting: "<<temp->waiting<<endl;
						//cout<<temp->name<<" status: "<<statusName[temp->status]<<" this is time waited: "<<temp->waited<<endl;
						if (temp->timestamp==tick)
						{	cout<<"Call from "<<temp->name<< " a "<<statusName[temp->status]<< " member"<<endl;
							push(temp);
							//cout<<"current elenum (not) hang up "<<elenum<<endl;
						}
						else 
							{
								push(temp);
							}
					}
					//cout<<"this is :"<<top().name<< " a "<<statusName[top().status]<< " member"<<endl;
						
				}
			}
		//cout<<"This is Current que.size "<<size()<<endl;
}
/*void print_all(queue que){
	int i,tempp;
	tempp=que.size();
for (i=0;i<tempp;i++)	
		{
			cout<<" "<<que->top().name<<endl;
			que.pop();
		}
}*/
void read_in_one_event(queue &Pque,queue &Gque,queue &Sque,queue &Rque)
{			
			event evt;
			string temp;
			istringstream istream;
			queue *quetemp;
			//cout<<"This is eventNum "<<eventNum<<endl;
			//cout<<"This is eventNum "<<eventNum<<endl;
			getline(cin,temp);
			istream.str(temp);
			evt.origstr=temp;
			istream>>evt.timestamp>>evt.name>>temp;
			//cout<<evt.timestamp<<endl;
			if(temp=="regular")
				{
					evt.status=Regular;
					quetemp=&Rque;
				}
			else if (temp=="silver")
				{
					evt.status=Silver;
					quetemp=&Sque;
				}
			else if (temp=="gold")
				{
					evt.status=Gold;
					quetemp=&Gque;
				}
			else if (temp=="platinum")
				{
					evt.status=Platinum;
					quetemp=&Pque;
				}
			else 
				assert(0);
			istream>>evt.waiting>>evt.duration;
			evt.waited=0;
			//event *a=new event(o);
		//	cout<<evt.origstr<<endl;
			event *a=new event(evt);
			quetemp->push(a);
			//cout<<"current top: "<<quetemp->top().name<<" shold always be the same ";
			//quetemp->pop();
			//cout<<"This is Current que.size "<<quetemp->size()<<endl;
			istream.clear();
}
struct agent{
		bool busy;
		int workingtime;
		event currentevt;
};
void exe_one_tick(int tick,agent &agt, queue &Pque,queue &Gque,queue &Sque,queue &Rque)
{	
	Pque.tick_plusOne_hang(tick);
	Gque.tick_plusOne_hang(tick);
	Sque.tick_plusOne_hang(tick);
	Rque.tick_plusOne_hang(tick);

	
	event noevent;
	noevent.timestamp=-1;
	noevent.name="";
	noevent.duration=-1;
	noevent.origstr="This is an event denotes no events. ";
	noevent.waited=-1;
	noevent.status=Regular;
	noevent.waiting=-1;
	event current;
	/*string origstr;
	int timestamp;//call in time
	string name;
	Status status;
	int waiting;//time customer will wait
	int waited;//time waited
	int duration;*/
	//cout<<"this is elenments in Rqueue: " << Rque.size()<<endl;
	//cout<<agt.workingtime<<" "<<agt.currentevt.duration<<endl;
	if (agt.busy)
	{
		
		if(agt.workingtime>=agt.currentevt.duration)
			{	
				agt.busy=false;
				agt.workingtime=0;
			}
		else
			{
				agt.workingtime++;
			}
		
			
	}
	//cout<<"after update: "<<agt.workingtime<<" "<<agt.currentevt.duration<<endl;
	//cout<<Pque.size()<<Gque.size()<<Sque.size()<<Rque.size()<<endl;
	if(!Pque.size()&&!Gque.size()&&!Sque.size()&&!Rque.size())
	{	//cout<<"test"<<endl;
		if(agt.workingtime==agt.currentevt.duration)
			{	agt.busy=false;
				return;}
	}
	//cout<<"agent is now(1 is busy, 0 is free)"<<agt.busy<<endl;
	Pque.tick_plusOne_call(tick);
	Gque.tick_plusOne_call(tick);
	Sque.tick_plusOne_call(tick);
	Rque.tick_plusOne_call(tick);
	if (!agt.busy)
	{
		//cout<<"top element's time stamp"<<endl;
		if(Pque.size()>0)
			{	//cout<<Pque.top().origstr<<endl;
				//cout<<Pque.top().timestamp<<endl;
				if (Pque.top().timestamp<=tick)
					{
						current=Pque.top();
						cout<<"Answering call from "<<current.name<<endl;
						Pque.pop();
						agt.busy=true;
						agt.workingtime=1;
						agt.currentevt=current;
						return;
					}
				else 
				{}
			}
		if(Gque.size()>0)
				{	//cout<<Gque.top().origstr<<endl;
					//cout<<Gque.top().timestamp<<endl;
					if(Gque.top().timestamp<=tick)
						{	//cout<<"should run to here"<<endl;
							current=Gque.top();
							cout<<"Answering call from "<<current.name<<endl;
							Gque.pop();
							agt.busy=true;
							agt.workingtime=1;
							agt.currentevt=current;
							return;
						}
					else 
					{}
					
				}
		if(Sque.size()>0)
						{	//cout<<Sque.top().origstr<<endl;
							//cout<<Sque.top().timestamp<<endl;
							if(Sque.top().timestamp<=tick)
								{	
									current=Sque.top();
									cout<<"Answering call from "<<current.name<<endl;
									Sque.pop();
									agt.busy=true;
									agt.workingtime=1;
									agt.currentevt=current;
									return;
								}
							else 
							{}
								
						}
		if(Rque.size()>0)
				{	//cout<<"finding debuging line"<<endl;
					//cout<<Rque.top().name<<" "<< Rque.top().timestamp<<endl;
					//cout<<Rque.top().origstr<<endl;
					//cout<<Rque.top().timestamp<<endl;
					if(Rque.top().timestamp<=tick)
						{	
							current=Rque.top();
							cout<<"Answering call from "<<current.name<<endl;
							Rque.pop();
							agt.busy=true;
							agt.workingtime=1;
							agt.currentevt=current;
							return;
						}
					else 
					{}
					
				}	
		else 
		{	//cout<<"no calls now"<<endl;
			current=noevent;
			agt.currentevt=current;
			agt.workingtime=0;
			return;
		}
	}
	//cout<<agt.workingtime<<endl;
	
}
int main()
{	int eventNum,tick=0;

	event noevent;
	noevent.timestamp=-1;
	noevent.name="";
	noevent.duration=-10;
	noevent.origstr="This is an event denotes no events. ";
	noevent.waited=-1;
	noevent.status=Regular;
	noevent.waiting=-1;
	
	string temp;
	agent agt;
	agt.busy=false;
	agt.workingtime=0;
	agt.currentevt=noevent;
	getline(cin,temp);
	eventNum=atoi(temp.c_str());
	//cout<<"eventNUm: "<<eventNum<<endl;;
	queue Pque,Gque,Sque,Rque;
	for (;eventNum>0;eventNum--)
		{	//<timestamp> <name> <status> <waiting> <duration>
			read_in_one_event(Pque,Gque,Sque,Rque);
			//cout<<"just before break"<<endl;
			//break;
		}
		/*while(Rque.size())
		{cout<<Rque.top().origstr<<endl;
		Rque.pop();}*/	
		while(1)
		{	
			if(!Pque.size()&&!Gque.size()&&!Sque.size()&&!Rque.size()&&!agt.busy)
					{break;}
			cout<<"Starting tick #"<<tick<<endl;
			
			exe_one_tick(tick,agt,Pque,Gque,Sque,Rque);
			tick++;
			
			
		}
	//exit(0);
}
/*struct event
{
	int timestamp;//call in time
	string name;
	Status status;
	int waiting;//time customer will wait
	int waited;//time waited
	int duration;
};*/