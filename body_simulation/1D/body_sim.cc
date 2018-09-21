#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
#define G 9.81
#define time 50.0
#define u_0 30.0
#define step 0.01

class body{
	/* Access specifier */
	public:
	
	/*Variables to load*/
	double mass, ypos,w,e,u,t_f ;
	double * v;
	double * t_i;
	double * t_correction;

	/*function*/

	void project(double u , double t_f){
		if(u == u_0){ // only if it's the first projection
			double a = 0.0; // dummy variable to hold bounce time	
			double b = 0.0; // dummy variable for time correction
			t_i = &a;
			t_correction = &b;
		}
		else{
			double b = step;
			t_correction = &b;
		}
		for(double i = 0.0 ; i < t_f - *t_i; i+= step){
			ypos = u*i - (0.5)*G*i*i;
			w = u - G*i;
			v = &w;
			if(ypos <= 0 && *v!=u && abs(*v) > 0.1){
				double a = i + *t_i;
				t_i = &a;
				u = - w*e;
				project(u, t_f);
				break;
			}
			cout << ypos << " " << i + *t_i << endl;
		}
	}
};

int main(){
	body ball;
	ball.mass = 1.0; //kg
	ball.e = 0.8;
	ball.project(u_0,time);
	return 0;
}
