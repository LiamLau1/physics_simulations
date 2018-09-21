// program to solve for SHM optional frequency space plot
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

#define h 0.0001 //stepsize
#define omega 10
#define coefficient 1 //0 for no forcing 1 for forcing
#define gamma 1
double x = 1.0; //initial position
double u = 10.0; //initial speed
double t = 0.0; //initial time
double force = 200.0; //forcing amplitude
double force_omega = 3.0;

void euler();

int main(){
		for(int i =0; i < 100000; i++){
			euler();
		}
	

	return 0;
}
void euler(){
	cout << fixed << setprecision(5) << t << " " <<fixed << setprecision(5) << x <<endl;
	double f = -omega*omega*x  - 2*gamma*u + coefficient*force*cos(force_omega*t); // differential equation rearranged
	x = x + h*u; //to get the new x
	u = u + h*f;// get new x prime
	t = t + h;
}
