#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

struct vec{

	double x;
	double y;
};

vec r_0;
vec v;
vec r;

int main(){
	r_0.x = 0.0;
	r_0.y = 0.0;
	v.x = 1.0;
	v.y = 1.0;
	int t = 0;
	for(int i = 0; i < 10; i++){
		r.x = r_0.x + v.x*t;
		r.y = r_0.y + v.y*t;
		cout << fixed <<setprecision(2) << r.x << " " << fixed <<setprecision(3) << r.y << endl;
		t ++;
	}
	return 0;


}
