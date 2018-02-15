#pragma once

#include <osg\Quat>

using namespace osg;

namespace Functions
{
	Quat getQuatFromEuler(double bank, double heading, double attitude, bool degrees = false);
	Quat getQuatFromEuler(Vec3d rotation, bool degrees = false);
	Vec3d getEulerFromQuat(Quat q, bool degrees = false);
};