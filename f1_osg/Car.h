#pragma once

#include <iostream>
#include <osg\Node>
#include <osg\Geode>
#include <osg\PositionAttitudeTransform>

#define CAR_MAX_SPEED		40.0f
#define CAR_MAX_SPEED_BACK -5.0f
#define CAR_SPEED_DROP		0.2f

#define CAR_MAX_ANG_SPEED	2.0f
#define CAR_ANG_SPEED_DROP	0.1f

#define CAR_COLLISION_FRONT	1
#define CAR_COLLISION_NONE	0
#define CAR_COLLISION_BACK	2

using namespace std;
using namespace osg;

class Car
{
protected:
	double zAngle = 0.0f;
	float speed = 0.0f;
	float angularSpeed = 0.0f;
	ref_ptr<Node> carNode = NULL;
	ref_ptr<PositionAttitudeTransform> carTransform = NULL;
	ref_ptr<Geode> carCollider = NULL;
	vector<PositionAttitudeTransform *> colliders = vector<PositionAttitudeTransform *>();

public:
	Car(ref_ptr<Node> carNode, ref_ptr<PositionAttitudeTransform> carTransform, ref_ptr<Geode> carCollider);
	void addSpeed(float amount);
	float getSpeed();
	void addAngularSpeed(float amount);
	float getAngularSpeed();
	void update();
	void updateColliders();
	void setFacingAngle(double angle);
	double getFacingAngle();
	ref_ptr<PositionAttitudeTransform> getTransform();
	ref_ptr<Geode> getCollider();
	ref_ptr<Node> getNode();
	void addCollider(PositionAttitudeTransform * collider);
	bool findInColliders(PositionAttitudeTransform * collider);
};