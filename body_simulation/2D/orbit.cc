#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

#define h 0.001 // stepsize
double t= 0.0;


class satellite{
	// we are assuming point mass as the distances are large
	public:
	/* declare attributes */
	double mass, x, y, u_x, u_y;

};

satellite sun;
satellite earth;
double ge_x,ge_y,geu_x,geu_y; //global dummy variables

void euler_2(double M, double s_x, double s_y, double su_x, double su_y); // second order ode solver

int main(){
	sun.mass = 333000;
	sun.x = 0; sun.y = 0;
	sun.u_x = 0; sun.u_y =0;

	earth.mass = 1;
	earth.x = 1000; earth.y = 0;
	earth.u_x = 0; earth.u_y = 0;
	ge_x = earth.x; ge_y = earth.y; geu_x = earth.u_x; geu_y = earth.u_y;

	for(int i = 0; i < 1000000; i++){
		euler_2(sun.mass,sun.x,sun.y,sun.u_x,sun.u_y);
	}
	return 0;
}

void euler_2(double M, double s_x, double s_y, double su_x, double su_y) {
	cout << ge_x << " " << ge_y <<endl;
	double x_previous = ge_x;
	double y_previous = ge_y;
	double f = -(M)/pow((pow((x_previous - s_x),2) + pow((y_previous - s_y),2)),1.5); // this equals r double dot
	ge_x = ge_x + h*geu_x;
	ge_y = ge_y + h*geu_y;
	geu_x = geu_x +h*f*x_previous;
	geu_y = geu_y +h*f*y_previous;
	t = t + h;
}
