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
	BoundingBox collider = BoundingBox();
	Geode * colliderNode = NULL;

public:
	Collider(BoundingBox collider, PositionAttitudeTransform * transform);
	BoundingBox getCollider();
	PositionAttitudeTransform * getTransform();
};