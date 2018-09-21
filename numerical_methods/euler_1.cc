#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

#define h 0.01 //stepsize
double x = 0.0; //initial conditions
double y = 1.0; //initial conditions

void euler();

int main(){
	for(int i =0; i < 1000; i++){
		euler();
	}
	return 0;
}
void euler(){
	cout << fixed << setprecision(5) << x << " " <<fixed << setprecision(5) << y <<endl;
	double y_prime = y ; // rearrange to get tangent gradient
	y = y + h*y_prime; //to get the new y
	x = x + h;
}
