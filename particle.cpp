#include "particle.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
//random float
float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float difference = b - a;
    float randN = random * difference;
    return a + randN;
}
//Constructor
particle::particle(){
		this->PX = RandomFloat(-10.0, 10);
		this->PY = RandomFloat(-10.0, 10);
		this->c1 = rand()% 3;
		this->c2 = rand()% 3;
		this->c3 = rand()% 3;
		//this->direction = {{0,0}};I did not use direction
		this->range = rand()% 3 + 2;
		this->size = rand() % 5 + 1;
		this->speed = 0.6;
		this->life = rand() % 600 + 100;
	}