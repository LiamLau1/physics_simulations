//First order ODE Euler Method Numerical solver
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

void euler(double stepsize, double space ,  double x, double y);

int main(){
	for(int i = 0; i < space / stepsize; i++){
		euler(double stepsize, double space, double x, double y);}
	return 0;
}
void euler(double stepsize, double space, double x, double y){
	cout <<fixed<< setprecision(5) <<x<<" "<<fixed<< setprecision(5) << y <<endl;
	
