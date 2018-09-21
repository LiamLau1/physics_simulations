//using the naive euler method, conservation of energy doesn't hold to second order
//need to use improved integrator to conserve E to second order
//reduce energy drift
//maybe use verlet integrator as it is sympletic (Störmer-Verlet)

#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
using namespace std;

#define dT 0.0001 // stepsize
#define D 2 //dimensions
double t= 0.0;


class satellite{
	// we are assuming point mass as the distances are large
	public:
	vector<double> position;
	vector<double> velocity;
	vector<double> previous_position;
	double acceleration_function_1;
	double acceleration_function_2;
	double mass;
	void euler(double body1_m, double body2_m, vector<double> &c_position, vector<double> &c_velocity, vector<double> &o_position, vector<double> &body1_position, vector<double> &body2_position,  double accelerationf1, double acceleartionf2); // second order ode solver
	private:
};

void satellite::euler(double body1_m, double body2_m, vector<double> &c_position, vector<double> &c_velocity, vector<double> &o_position, vector<double> &body1_position, vector<double> &body2_position,  double accelerationf1, double acceleartionf2)
{
	//first iteration to update position of body, c_position and c_velocity of the body interested using a position and velocity verlet
	cout << c_position[0] << " " << c_position[1] << " ";
	for(int i =0; i < 2 ; i++){
		o_position[i] = c_position[i]; //initialises the old positions
	}
	accelerationf1 = -(body1_m)/(pow((pow((c_position[0] - body1_position[0]),2) + pow((c_position[1] - body1_position[1]),2)),1.5));
	acceleartionf2 = -(body2_m)/(pow((pow((c_position[0] - body2_position[0]),2) + pow((c_position[1] - body2_position[1]),2)),1.5));
	for(int i =0; i < 2; i++){
		c_position[i] += dT*c_velocity[i] + 0.5*((accelerationf1*(o_position[i] - body1_position[i]))+(acceleartionf2*(o_position[i] - body2_position[i])))*pow(dT,2); //updating position to r(t+dT)
	}
	/// *** update acceleration to a(t+dT) using x(t+dT) to find v(t+dT) *** ///
	double accelerationf1_new = -(body1_m)/(pow((pow((c_position[0] - body1_position[0]),2) + pow((c_position[1] - body1_position[1]),2)),1.5));
	double acceleartionf2_new = -(body2_m)/(pow((pow((c_position[0] - body2_position[0]),2) + pow((c_position[1] - body2_position[1]),2)),1.5));
	for(int i =0; i < 2; i++){
		c_velocity[i] += 0.5*dT*(((accelerationf1*(o_position[i] - body1_position[i]))+(acceleartionf2*(o_position[i] - body2_position[i]))) +((accelerationf1_new*(c_position[i] - body1_position[i]))+(acceleartionf2_new*(c_position[i] - body2_position[i])))); //updating velocity to v(t+dT)
	}
}

satellite probe;
satellite sun;
satellite earth;
double ge_x,ge_y,geu_x,geu_y; //global dummy variables
double gs_x, gs_y;
double gp_x, gp_y,gpu_x,gpu_y;



int main(){
	//create the vectors with dimension D
	sun.position.push_back(D);
	sun.velocity.push_back(D);
	sun.previous_position.push_back(D);
	//sun.acceleration_function.push_back(D);
	earth.position.push_back(D);
	earth.velocity.push_back(D);
	earth.previous_position.push_back(D);
	//earth.acceleration_function.push_back(D);
	probe.position.push_back(D);
	probe.velocity.push_back(D);
	probe.previous_position.push_back(D);
	//probe.acceleration_function.push_back(D);
	/// ***** Sun's Attributes ***** ///
	sun.mass = 333000;
	sun.position[0] = 0; //x
	sun.position[1] = 0; //y
	sun.velocity[0] = 0;
	sun.velocity[1]=0;

	/// ***** Probe's Attributes ***** ///

	probe.mass = 0.1;
	probe.position[0] = 50;
	probe.position[1] = 700;
	probe.velocity[0] = 5;
	probe.velocity[1] = 0.4;

	/// ***** Earth's Attributes ***** ///

	earth.mass = 1;
	earth.position[0] = 1000;
	earth.position[1] = 0;
	earth.velocity[0] = 0;
	earth.velocity[1] = 5.2;

	for(int i = 0; i < 10000000; i++){
		earth.euler(sun.mass, probe.mass, earth.position,earth.velocity, earth.previous_position, sun.position, probe.position, earth.acceleration_function_1, earth.acceleration_function_2);
		probe.euler(sun.mass, earth.mass, probe.position,probe.velocity, probe.previous_position, sun.position, earth.position, probe.acceleration_function_1, probe.acceleration_function_2);
		sun.euler(earth.mass, probe.mass, sun.position,sun.velocity, sun.previous_position, earth.position, probe.position, sun.acceleration_function_1, sun.acceleration_function_2);
		cout << endl ;
	}
	return 0;
}
