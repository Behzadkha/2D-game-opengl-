#ifndef PARTICLE_H
#define PARTICLE_H
#include <vector>
using namespace std;
//class
class particle{
public:
	particle();
	float PX,PY;
	int size;
	int c1,c2,c3;
	//vector<vector<float>> direction;
	int range;
	float speed;
	int life;
	
};
#endif
