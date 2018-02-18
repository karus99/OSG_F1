#include "Collider.h"
#include "Functions.h"

Collider::Collider(BoundingBox collider, PositionAttitudeTransform * transform)
{
	this->collider = collider;
	this->transform = transform;

	this->colliderNode = new Geode();
	ShapeDrawable * shape = new ShapeDrawable(new Box());
	shape->setInitialBound(collider);
	shape->setComputeBoundingBoxCallback(new DummyComputeBoundingBoxCallback());

	cout << shape->getBoundingBox().center().x() << " " << shape->getBoundingBox().center().y() << endl;
	cout << shape->getBoundingBox().xMin() << " " << shape->getBoundingBox().xMax() << " " << shape->getBoundingBox().yMin() << " " << shape->getBoundingBox().yMax() << endl;

	this->transform->addChild(this->colliderNode);
}

BoundingBox Collider::getCollider()
{
	return this->collider;
}

PositionAttitudeTransform * Collider::getTransform()
{
	return this->transform;
}