//using the naive euler method, conservation of energy doesn't hold to second order
//need to use improved integrator to conserve E to second order
//maybe use verlet integrator


#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

#define h 0.0001 // stepsize
double t= 0.0;


class satellite{
	// we are assuming point mass as the distances are large
	public:
	/* declare attributes */
	double mass, x, y, u_x, u_y;

};

satellite probe;
satellite sun;
satellite earth;
double ge_x,ge_y,geu_x,geu_y; //global dummy variables
double gs_x, gs_y;
double gp_x, gp_y,gpu_x,gpu_y;

void euler_2(double M, double m, double probe_m, double s_x, double s_y, double su_x, double su_y); // second order ode solver

int main(){
	sun.mass = 333000;
	sun.x = 0; sun.y = 0;
	sun.u_x = 0; sun.u_y =0;
	gs_x = sun.x; gs_y = sun.y;

	probe.mass = 0.1;
	probe.x = 50; probe.y = 700;
	probe.u_x = 5; probe.u_y = 0.4;
	gp_x = probe.x; gp_y = probe.y; gpu_x = probe.u_x; gpu_y = probe.u_y;

	earth.mass = 1;
	earth.x = 1000; earth.y = 0;
	earth.u_x = 0; earth.u_y = 5.2;
	ge_x = earth.x; ge_y = earth.y; geu_x = earth.u_x; geu_y = earth.u_y;

	for(int i = 0; i < 10000000; i++){
		euler_2(sun.mass,earth.mass, probe.mass, sun.x,sun.y,sun.u_x,sun.u_y);
	}
	return 0;
}

void euler_2(double M, double m, double probe_m, double s_x, double s_y, double su_x, double su_y) {
	cout << ge_x << " " << ge_y << " " << gp_x << " " << gp_y<<endl;
	double x_previous = ge_x;
	double y_previous = ge_y;
	double probex_previous = gp_x;
	double probey_previous = gp_y;
	double f = -(M)/(pow((pow((x_previous - s_x),2) + pow((y_previous - s_y),2)),1.5)); // first term
	double f_2 = -(probe_m)/(pow((pow((x_previous - probex_previous),2) + pow((y_previous - probey_previous),2)),1.5));
	double f_3 = -(M)/(pow((pow((probex_previous - s_x),2) + pow((probey_previous - s_y),2)),1.5));
	double f_4 = -(m)/(pow((pow((probex_previous - x_previous),2) + pow((probey_previous - y_previous),2)),1.5));
	ge_x = ge_x + h*geu_x;
	ge_y = ge_y + h*geu_y;
	gp_x = gp_x + h*gpu_x;
	gp_y = gp_y + h*gpu_y;
	geu_x = geu_x +h*f*(x_previous-gs_x) + h*f_2*(x_previous - probex_previous);
	geu_y = geu_y +h*f*(y_previous-gs_y) + h*f_2*(y_previous - probey_previous);
	gpu_x = gpu_x + h*f_3*(probex_previous-gs_x) +h*f_4*(probex_previous-x_previous);
	gpu_y = gpu_y + h*f_3* (probey_previous-gs_y) + h*f_4*(probey_previous-y_previous);
	t = t + h;
}
