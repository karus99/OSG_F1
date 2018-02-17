#include "Car.h"
#include "Functions.h"

Car::Car(ref_ptr<Node> carNode, ref_ptr<PositionAttitudeTransform> carTransform, ref_ptr<Geode> carCollider)
{
	this->carNode = carNode;
	this->carTransform = carTransform;
	this->carCollider = carCollider;
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
	int collisionMoveState = CAR_COLLISION_NONE;

	for (int i = 0; i < this->colliders.size(); i++)
	{
		Vec3d carPos = this->carTransform->getPosition();
		Vec3d colPos = this->colliders[i]->getPosition();

		double zRad = DegreesToRadians(this->zAngle);

		double x = carPos.x() - (50.0 * sin(-zRad));
		double y = carPos.y() - (50.0 * cos(-zRad));

		Vec3d frontPoint = Vec3d(x, y, carPos.z());

		x = carPos.x() + (50.0 * sin(-zRad));
		y = carPos.y() + (50.0 * cos(-zRad));

		Vec3d backPoint = Vec3d(x, y, carPos.z());

		double distanceFront = sqrt(pow(colPos.x() - frontPoint.x(), 2) + pow(colPos.y() - frontPoint.y(), 2) + pow(colPos.z() - frontPoint.z(), 2));
		double distanceBack = sqrt(pow(colPos.x() - backPoint.x(), 2) + pow(colPos.y() - backPoint.y(), 2) + pow(colPos.z() - backPoint.z(), 2));

		if (distanceFront < distanceBack)
		{
			collisionMoveState |= CAR_COLLISION_FRONT;

			if (this->speed > 0)
			{
				this->speed = 0;
			}
		}
		else
		{
			collisionMoveState |= CAR_COLLISION_BACK;

			if (this->speed < 0)
			{
				this->speed = 0;
			}
		}
	}

	// speed update
	// to-do air mass factor
	if (this->speed > 0)
	{
		this->speed -= CAR_SPEED_DROP;
		if (this->speed < 0)
		{
			this->speed = 0.0f;
			this->angularSpeed = 0.0f;
		}
	}
	else if (this->speed < 0)
	{
		this->speed += CAR_SPEED_DROP;
		if (this->speed > 0)
		{
			this->speed = 0.0f;
			this->angularSpeed = 0.0f;
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

	Vec3d pos = this->carTransform->getPosition();

	if (this->speed != 0)
	{
		this->zAngle += this->angularSpeed;
	}
	double zRad = DegreesToRadians(this->zAngle);

	double x = pos.x() - (this->speed * sin(-zRad));
	double y = pos.y() - (this->speed * cos(-zRad));

	this->carTransform->setPosition(Vec3d(x, y, pos.z()));
	this->carTransform->setAttitude(Functions::getQuatFromEuler(0.0, 0.0, this->zAngle, true));

	// update colliders
	this->updateColliders();
}

ref_ptr<PositionAttitudeTransform> Car::getTransform()
{
	return this->carTransform;
}

void Car::setFacingAngle(double angle)
{
	this->zAngle = angle;

	this->carTransform->setAttitude(Functions::getQuatFromEuler(0.0, 0.0, angle, true));
}

double Car::getFacingAngle()
{
	return this->zAngle;
}

ref_ptr<Geode> Car::getCollider()
{
	return this->carCollider;
}

ref_ptr<Node> Car::getNode()
{
	return this->carNode;
}

void Car::addCollider(PositionAttitudeTransform * collider)
{
	this->colliders.push_back(collider);
}

bool Car::findInColliders(PositionAttitudeTransform * collider)
{
	for (int i = 0; i < this->colliders.size(); i++)
	{
		if (this->colliders[i] == collider)
		{
			return true;
		}
	}
	return false;
}

void Car::updateColliders()
{
	cout << "Colides with: ";
	for (int i = 0; i < this->colliders.size(); i++)
	{
		if (!this->carTransform->getBound().intersects(this->colliders[i]->getBound()))
		{
			this->colliders.erase(this->colliders.begin() + i);
			continue;
		}
		cout << i << ", ";
	}
	cout << endl;
}