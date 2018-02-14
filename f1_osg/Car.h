#pragma once

#include <osg\Node>
#include <osg\MatrixTransform>

#define CAR_MAX_SPEED 20.0f
#define CAR_MAX_SPEED_BACK -5.0f
#define CAR_SPEED_DROP 0.1f

#define CAR_MAX_ANG_SPEED 2.0f
#define CAR_ANG_SPEED_DROP 0.08f

using namespace std;
using namespace osg;

class Car
{
protected:
	double zAngle = 0.0f;
	float speed = 0.0f;
	float angularSpeed = 0.0f;
	ref_ptr<Node> carNode = NULL;
	ref_ptr<MatrixTransform> carTransform = NULL;

public:
	Car(ref_ptr<Node> carNode, ref_ptr<MatrixTransform> carTransform);
	void addSpeed(float amount);
	float getSpeed();
	void addAngularSpeed(float amount);
	float getAngularSpeed();
	void update();
	void setFacingAngle(double angle);
	ref_ptr<MatrixTransform> getTransform();
};