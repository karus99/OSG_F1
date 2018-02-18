#pragma once

#include <osgGA/GUIEventHandler>

#include "Car.h"

using namespace osgGA;

class Player : public Car
{
public:
	Player(ref_ptr<Node> carNode, ref_ptr<PositionAttitudeTransform> carTransform, Box * carCollider);
};

class PlayerCollisionUpdateCallback : public NodeCallback
{
public:
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
};