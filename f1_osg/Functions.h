#pragma once

#include <osg\Node>
#include <osg\Drawable>

using namespace osg;

namespace Functions
{
	Quat getQuatFromEuler(double bank, double heading, double attitude, bool degrees = false);
	Quat getQuatFromEuler(Vec3d rotation, bool degrees = false);
	Vec3d getEulerFromQuat(Quat q, bool degrees = false);
};

class DummyComputeBoundingSphereCallback : public Node::ComputeBoundingSphereCallback
{
public:
	virtual BoundingSphere computeBound(Node * node);
};

class DummyComputeBoundingBoxCallback : public Drawable::ComputeBoundingBoxCallback
{
public:
	virtual BoundingBox computeBound(const osg::Drawable &) const;
};