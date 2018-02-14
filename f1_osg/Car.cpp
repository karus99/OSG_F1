#include "Car.h"

Car::Car(ref_ptr<Node> carNode)
{
	this->carNode = carNode;
}

void Car::addSpeed(float amount)
{
	this->speed += amount;

	if (this->speed > CAR_MAX_SPEED)
	{
		this->speed = CAR_MAX_SPEED;
	}
}

float Car::getSpeed()
{
	return this->speed;
}

void Car::update()
{
	if (this->speed > 0)
	{
		this->speed -= CAR_SPEED_DROP;
	}
	else
		this->speed = 0.0f;
}