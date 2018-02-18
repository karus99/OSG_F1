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

void Collider::move(double distance, double angle)
{
	Vec3d pos = this->transform->getPosition();

	double x = pos.x() - (distance * sin(-angle));
	double y = pos.y() - (distance * cos(-angle));

	this->transform->setPosition(Vec3d(x, y, pos.z()));

	Box * box = new Box(Vec3d(x, y, pos.z()), 140.0, 20.0, 80.0);
	ShapeDrawable * shape = new ShapeDrawable(box);
	this->collider = shape;
}