#include "Collider.h"
#include "Functions.h"

Collider::Collider(Box * collider, PositionAttitudeTransform * transform)
{
	ShapeDrawable * shape = new ShapeDrawable(collider);
	this->collider = shape;
	this->transform = transform;
}

ShapeDrawable * Collider::getCollider()
{
	return this->collider;
}

PositionAttitudeTransform * Collider::getTransform()
{
	return this->transform;
}