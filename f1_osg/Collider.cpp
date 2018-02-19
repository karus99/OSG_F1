#include "Collider.h"
#include "Functions.h"
#include "Game.h"

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

int Collider::getColliderType()
{
	return this->colliderType;
}

void Collider::registerHit(double force)
{
	this->health -= force;

	if (this->health <= 0.0f)
	{
		Game * game = Game::getInstance(NULL);
		Player * player = game->getPlayer();

		vector<Collider *> barriers = game->getBarriers();
		vector<Collider *> collisions = player->getCollisions();
		Group * scene = game->getScene();

		for (int i = 0; i < barriers.size(); i++)
		{
			if (barriers[i]->getTransform() == this->transform)
			{
				barriers.erase(barriers.begin() + i);
			}
		}

		this->state = false;

		Vec3 wind(1.0f, 0.0f, 0.0f);
		Vec3 pos(this->transform->getPosition());

		double zRad = DegreesToRadians(this->zAngle);

		double x = pos.x() - (10.0 * sin(-zRad));
		double y = pos.y() - (10.0 * cos(-zRad));

		ExplosionEffect* explosion = new ExplosionEffect(Vec3d(x, y, 20.0), 40.0f);
		ExplosionDebrisEffect* explosionDebri = new ExplosionDebrisEffect(Vec3d(x, y, 20.0), 40.0f);
		SmokeEffect* smoke = new SmokeEffect(Vec3d(x, y, 20.0), 40.0f);
		FireEffect* fire = new FireEffect(Vec3d(x, y, 20.0), 40.0f);

		explosion->setWind(wind);
		explosionDebri->setWind(wind);
		smoke->setWind(wind);
		fire->setWind(wind);

		scene->addChild(explosion);
		scene->addChild(explosionDebri);
		scene->addChild(smoke);
		scene->addChild(fire);

		scene->removeChild(this->transform);
		return;
	}

	if (this->health <= 190.0f)
	{
		Vec3 wind(1.0f, 0.0f, 0.0f);
		Vec3 pos(this->transform->getPosition());

		double zRad = DegreesToRadians(this->zAngle);

		double x = pos.x() - (10.0 * sin(-zRad));
		double y = pos.y() - (10.0 * cos(-zRad));

		SmokeEffect* smoke = new SmokeEffect(Vec3d(x, y, 20.0), 40.0f);
		FireEffect* fire = new FireEffect(Vec3d(x, y, 20.0), 40.0f);

		smoke->setWind(wind);
		fire->setWind(wind);

		this->transform->addChild(smoke);
		this->transform->addChild(fire);
		return;
	}
}