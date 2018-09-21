#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

void calculate(double t);

int main(){
	double j = 10.0; //final time
	for(double i = 0.0; i < j; i+=0.01){ 
		cout << i << " "; //whitespace as delimeter
		calculate(i);
	}
	return 0;
}

void calculate(double t){
	double  m = 1.0; //mass of point mass, assuming spring is light
	double A = 1.0; //amplitude being the intial displacement 
	double v = 1.0; // initial velocity
	double k = 1.0; //spring constant
	double x; //displacement from eqm
	double omega = k/m;
	x = A*cos(omega*t)+(v/omega)*sin(omega*t);
	cout << x <<endl;
}
