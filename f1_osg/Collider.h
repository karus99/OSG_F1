#pragma once

#include <iostream>
#include <osg\Geode>
#include <osg\ShapeDrawable>
#include <osg\PositionAttitudeTransform>

using namespace std;
using namespace osg;

class Collider
{
private:
	PositionAttitudeTransform * transform = NULL;
	ShapeDrawable * collider = NULL;
	Geode * colliderNode = NULL;
	double zAngle = 0.0;

public:
	Collider(Box * collider, PositionAttitudeTransform * transform, double zAngle);
	ShapeDrawable * getCollider();
	PositionAttitudeTransform * getTransform();
	void move(double distance, double angle);
	void setTransform(Vec3d pos, double zAngle);
	double getFacingAngle();
};