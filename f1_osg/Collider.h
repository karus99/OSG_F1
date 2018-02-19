#pragma once

#include <iostream>
#include <osg\Geode>
#include <osg\ShapeDrawable>
#include <osg\PositionAttitudeTransform>
#include <osgParticle/ExplosionEffect>
#include <osgParticle/ExplosionDebrisEffect>
#include <osgParticle/SmokeEffect>
#include <osgParticle/SmokeTrailEffect>
#include <osgParticle/FireEffect>

#define COLLIDER_CAR		0
#define COLLIDER_BARRIER	1

using namespace std;
using namespace osg;
using namespace osgParticle;

class Collider
{
private:
	PositionAttitudeTransform * transform = NULL;
	ShapeDrawable * collider = NULL;
	Geode * colliderNode = NULL;
	double zAngle = 0.0;
	int colliderType;
	double health = 200.0f;

public:
	bool state = true;
	Collider(Box * collider, PositionAttitudeTransform * transform, double zAngle, int colliderType);
	ShapeDrawable * getCollider();
	PositionAttitudeTransform * getTransform();
	void move(double distance, double angle);
	void setTransform(Vec3d pos, double zAngle);
	double getFacingAngle();
	int getColliderType();
	void registerHit(double force);
};