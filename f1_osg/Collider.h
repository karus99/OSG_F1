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

public:
	Collider(Box * collider, PositionAttitudeTransform * transform);
	ShapeDrawable * getCollider();
	PositionAttitudeTransform * getTransform();
};