#pragma once

#include <osg\Node>

#define CAR_MAX_SPEED 20.0f
#define CAR_SPEED_DROP 0.01f

using namespace std;
using namespace osg;

class Car
{
private:
	float speed = 0.0f;
	ref_ptr<Node> carNode = NULL;

public:
	Car(ref_ptr<Node> carNode);
	void addSpeed(float amount);
	float getSpeed();
	void update();
};