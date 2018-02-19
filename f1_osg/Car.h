#pragma once

#include <iostream>
#include <osg\Node>
#include <osg\Geode>
#include <osg\PositionAttitudeTransform>

#include "Collider.h"

#define CAR_MAX_SPEED			40.0f
#define CAR_MAX_SPEED_BACK	   -5.0f
#define CAR_SPEED_DROP			0.2f

#define CAR_MAX_ANG_SPEED		2.0f
#define CAR_ANG_SPEED_DROP		0.1f
#define CAR_SPEED_TURN_FACTOR	0.5f

#define CAR_COLLISION_FRONT		1
#define CAR_COLLISION_NONE		0
#define CAR_COLLISION_BACK		2
	
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
	ShapeDrawable * carCollider = NULL;
	vector<Collider *> colliders = vector<Collider *>();
	Collider * colliderNode = NULL;

public:
	Car(ref_ptr<Node> carNode, ref_ptr<PositionAttitudeTransform> carTransform, Box * carCollider);

	void addColliderNode(Collider * collider);
	Collider * getColliderNode();

	void addSpeed(float amount);
	float getSpeed();
	void addAngularSpeed(float amount);
	float getAngularSpeed();

	void update();
	void updateColliders();

	void setFacingAngle(double angle);
	double getFacingAngle();

	ref_ptr<PositionAttitudeTransform> getTransform();
	ShapeDrawable * getCollider();
	ref_ptr<Node> getNode();

	void addCollider(Collider * collider);
	bool findInColliders(Collider * collider);
	vector<Collider *> getCollisions();
};