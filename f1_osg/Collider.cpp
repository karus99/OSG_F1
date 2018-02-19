#include "Collider.h"
#include "Functions.h"

Collider::Collider(Box * collider, PositionAttitudeTransform * transform, double zAngle, int colliderType)
{
	ShapeDrawable * shape = new ShapeDrawable(collider);
	this->collider = shape;
	this->transform = transform;
	this->zAngle = zAngle;
	this->colliderType = colliderType;
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

	Box * box = new Box();
	switch (colliderType)
	{
	case COLLIDER_BARRIER:
	{
		box = new Box(pos, 140.0, 20.0, 80.0);
	}
	case COLLIDER_CAR:
	{
		double zRad = DegreesToRadians(zAngle);

		double x = pos.x() - (68.0 * sin(-zRad));
		double y = pos.y() - (68.0 * cos(-zRad));

		box = new Box(Vec3d(x, y, 30.0), 70, 175, 60);
	}
	}

	box->setRotation(Functions::getQuatFromEuler(0.0, 0.0, this->zAngle, true));
	ShapeDrawable * shape = new ShapeDrawable(box);
	this->collider = shape;
}

void Collider::setTransform(Vec3d pos, double zAngle)
{
	this->transform->setPosition(pos);
	this->transform->setAttitude(Functions::getQuatFromEuler(0.0, 0.0, zAngle, true));

	this->zAngle = zAngle;

	Box * box = new Box();
	switch (colliderType)
	{
	case COLLIDER_BARRIER:
	{
		box = new Box(pos, 140.0, 20.0, 80.0);
	}
	case COLLIDER_CAR:
	{
		double zRad = DegreesToRadians(zAngle);

		double x = pos.x() - (68.0 * sin(-zRad));
		double y = pos.y() - (68.0 * cos(-zRad));

		box = new Box(Vec3d(x, y, 30.0), 70, 175, 60);
	}
	}

	box->setRotation(Functions::getQuatFromEuler(0.0, 0.0, zAngle, true));
	ShapeDrawable * shape = new ShapeDrawable(box);
	this->collider = shape;
}

double Collider::getFacingAngle()
{
	return this->zAngle;
}