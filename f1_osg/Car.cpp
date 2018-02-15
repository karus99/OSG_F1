#include "Car.h"
#include "Functions.h"

Car::Car(ref_ptr<Node> carNode, ref_ptr<MatrixTransform> carTransform)
{
	this->carNode = carNode;
	this->carTransform = carTransform;
}

void Car::addSpeed(float amount)
{
	this->speed += amount;

	if (this->speed > CAR_MAX_SPEED)
	{
		this->speed = CAR_MAX_SPEED;
	}

	if (this->speed < CAR_MAX_SPEED_BACK)
	{
		this->speed = CAR_MAX_SPEED_BACK;
	}
}

float Car::getSpeed()
{
	return this->speed;
}

void Car::addAngularSpeed(float amount)
{
	this->angularSpeed += amount;

	if (this->angularSpeed > CAR_MAX_ANG_SPEED)
	{
		this->angularSpeed = CAR_MAX_ANG_SPEED;
	}

	if (this->angularSpeed < -CAR_MAX_ANG_SPEED)
	{
		this->angularSpeed = -CAR_MAX_ANG_SPEED;
	}
}

float Car::getAngularSpeed()
{
	return this->angularSpeed;
}

void Car::update()
{
	// speed update
	// to-do air mass factor
	if (this->speed > 0)
	{
		this->speed -= CAR_SPEED_DROP;
		if (this->speed < 0)
		{
			this->speed = 0.0f;
		}
	}
	else if (this->speed < 0)
	{
		this->speed += CAR_SPEED_DROP;
		if (this->speed > 0)
		{
			this->speed = 0.0f;
		}
	}

	// angular speed update
	if (this->angularSpeed > 0)
	{
		this->angularSpeed -= CAR_ANG_SPEED_DROP;
		if (this->angularSpeed < 0)
		{
			this->angularSpeed = 0.0f;
		}
	}
	else if (this->angularSpeed < 0)
	{
		this->angularSpeed += CAR_ANG_SPEED_DROP;
		if (this->angularSpeed > 0)
		{
			this->angularSpeed = 0.0f;
		}
	}

	Matrix mat = this->carTransform->getMatrix();

	Vec3d pos = mat.getTrans();

	if (this->speed != 0)
	{
		this->zAngle += this->angularSpeed;
	}
	double zRad = DegreesToRadians(this->zAngle);

	double x = pos.x() - (this->speed * sin(-zRad));
	double y = pos.y() - (this->speed * cos(-zRad));

	mat.setTrans(Vec3d(x, y, pos.z()));
	mat.setRotate(Functions::getQuatFromEuler(0.0, 0.0, this->zAngle, true));
	this->carTransform->setMatrix(mat);
}

ref_ptr<MatrixTransform> Car::getTransform()
{
	return this->carTransform;
}

void Car::setFacingAngle(double angle)
{
	Matrix mat = this->carTransform->getMatrix();

	this->zAngle = angle;

	mat.setRotate(Functions::getQuatFromEuler(Vec3d(0.0, 0.0, angle), true));
	this->carTransform->setMatrix(mat);
}

double Car::getFacingAngle()
{
	return this->zAngle;
}