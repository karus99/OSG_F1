
#include "Functions.h"

namespace Functions
{
	Quat getQuatFromEuler(double bank, double heading, double attitude, bool degrees)
	{
		if (degrees)
		{
			bank = DegreesToRadians(bank);
			heading = DegreesToRadians(heading);
			attitude = DegreesToRadians(attitude);
		}

		double c1 = cos(heading / 2); double s1 = sin(heading / 2); double c2 = cos(attitude / 2); double s2 = sin(attitude / 2); double c3 = cos(bank / 2);
		double s3 = sin(bank / 2);
		double c1c2 = c1*c2; double s1s2 = s1*s2;

		double w = c1c2*c3 - s1s2*s3;
		double x = c1c2*s3 + s1s2*c3;
		double y = s1*c2*c3 + c1*s2*s3;
		double z = c1*s2*c3 - s1*c2*s3;

		Quat q;

		q[0] = x; q[1] = y;
		q[2] = z; q[3] = w;

		return q;
	}

	Quat getQuatFromEuler(Vec3d rotation, bool degrees)
	{
		return getQuatFromEuler(rotation.x(), rotation.y(), rotation.z(), degrees);
	}

	Vec3d getEulerFromQuat(osg::Quat q, bool degrees)
	{
		double limit = 0.499999;

		double sqx = q.x()*q.x(); 
		double sqy = q.y()*q.y();
		double sqz = q.z()*q.z();

		double t = q.x()*q.y() + q.z()*q.w();

		double heading, attitude, bank;

		if (t>limit) // gimbal lock ?
		{
			heading = 2 * atan2(q.x(), q.w());
			attitude = osg::PI_2;
			bank = 0;
		}
		else if (t<-limit)
		{
			heading = -2 * atan2(q.x(), q.w());
			attitude = -osg::PI_2;
			bank = 0;
		}
		else
		{
			heading = atan2(2 * q.y()*q.w() - 2 * q.x()*q.z(), 1 - 2 * sqy - 2 * sqz);
			attitude = asin(2 * t);
			bank = atan2(2 * q.x()*q.w() - 2 * q.y()*q.z(), 1 - 2 * sqx - 2 * sqz);
		}

		if (degrees)
			return Vec3d(RadiansToDegrees(bank), RadiansToDegrees(heading), RadiansToDegrees(attitude));
		else
			return Vec3d(bank, heading, attitude);
	}
}
