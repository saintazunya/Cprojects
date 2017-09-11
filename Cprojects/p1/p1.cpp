#include <iostream>
#include "function.h"
#include <string>
#include <cstdlib>
using namespace std;
//using namespace std;

int main ()
{
	int a;
	string b;
	while (a!=1&&a!=2&&a!=3&&a!=4){
		cout << "Please enter the test choice: ";
		cin >> a;
		//cout << a<<endl;
	}
	int c=-5;
	while (c<0||c>10000000){
		cout << "Please enter the number for test: ";
		cin >> b;
		c=atoi(b.c_str());
	}
	if(a==1){
		cout<<fibonacci(c)<<endl;
	}
	else if(a==2){
		cout<<consquares(c)<<endl;
		}
	else if(a==3){
		cout<<repeatednumber(b)<<endl;
		}
	else if(a==4){
		cout<<Divisor(c)<<endl;
		}
}