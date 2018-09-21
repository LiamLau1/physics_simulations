#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

#define h 0.0001 // stepsize
#define G 6.67*pow(10,-11)
#define R 778.3*pow(10,3) // semi major axis in m
double t= 0.0;


class satellite{
	// we are assuming point mass as the distances are large
	public:
	/* declare attributes */
	double mass, x, y, u_x, u_y;

};

satellite probe;
satellite sun;
satellite jupiter;
double ge_x,ge_y,geu_x,geu_y; //global dummy variables
double gs_x, gs_y;
double gp_x, gp_y,gpu_x,gpu_y;
double omega; // angular velocity of corotating system

void euler_2(double M, double m, double probe_m, double s_x, double s_y, double su_x, double su_y, double omega); // second order ode solver

int main(){
	double alpha = -M_PI/3; // angle in radians
	sun.mass = 1.989 * pow(10,30);
	probe.mass = 0.1;
	jupiter.mass = 1.899*pow(10,27);

	jupiter.x = (sun.mass * R)/(sun.mass + jupiter.mass); jupiter.y = 0;
	jupiter.u_x = 0; jupiter.u_y = 0;
	ge_x = jupiter.x; ge_y = jupiter.y; geu_x = jupiter.u_x; geu_y = jupiter.u_y;
	sun.x = -(jupiter.mass*R)/(sun.mass + jupiter.mass); sun.y = 0;
	sun.u_x = 0; sun.u_y =0;
	gs_x = sun.x; gs_y = sun.y;
	probe.x = (R*(sun.mass - jupiter.mass)*cos(alpha))/(sun.mass+jupiter.mass); probe.y = sin(alpha);
	probe.u_x = 0; probe.u_y = 0;
	gp_x = probe.x; gp_y = probe.y; gpu_x = probe.u_x; gpu_y = probe.u_y;

	omega = sqrt((G*(sun.mass + jupiter.mass))/(pow(R,3)));

	for(int i = 0; i < 100000; i++){
		euler_2(sun.mass,jupiter.mass, probe.mass, sun.x,sun.y,sun.u_x,sun.u_y, omega);
	}
	return 0;
}

void euler_2(double M, double m, double probe_m, double s_x, double s_y, double su_x, double su_y, double omega) {
	cout << gs_x << " " << gs_y << " " << ge_x << " " << ge_y << " " << gp_x << " " << gp_y<<endl;
	// do it in the corotating frame
	double x_previous = ge_x;
	double y_previous = ge_y;
	double probeux_previous = gpu_x;
	double probeuy_previous = gpu_y;
	double probex_previous = gp_x;
	double probey_previous = gp_y;
	//double f = -(M)/(pow((pow((x_previous - s_x),2) + pow((y_previous - s_y),2)),1.5)); // first term
	//double f_2 = -(probe_m)/(pow((pow((x_previous - probex_previous),2) + pow((y_previous - probey_previous),2)),1.5));
	double f_3 = -(G*M)/(pow((pow((probex_previous - s_x),2) + pow((probey_previous - s_y),2)),1.5));
	double f_4 = -(G*m)/(pow((pow((probex_previous - x_previous),2) + pow((probey_previous - y_previous),2)),1.5));
	//ge_x = ge_x + h*geu_x;
	//ge_y = ge_y + h*geu_y;
	gp_x = gp_x + h*gpu_x;
	gp_y = gp_y + h*gpu_y;
	//geu_x = geu_x +h*f*(x_previous-gs_x) + h*f_2*(x_previous - probex_previous);
	//geu_y = geu_y +h*f*(y_previous-gs_y) + h*f_2*(y_previous - probey_previous);
	gpu_x = gpu_x + h*f_3*(probex_previous-gs_x) +h*f_4*(probex_previous-x_previous)+ 2* h*omega*probeuy_previous + h*pow(omega,2)*probex_previous;
	gpu_y = gpu_y + h*f_3* (probey_previous-gs_y) + h*f_4*(probey_previous-y_previous) - 2 * h*omega * probeux_previous + h*pow(omega,2)*probey_previous;
	t = t + h;
}
