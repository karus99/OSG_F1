#include "Game.h"

Game * Game::instance = NULL;

Game::Game(ref_ptr<Viewer> viewer)
{
	this->viewer = viewer;
}

Game * Game::getInstance(ref_ptr<Viewer> viewer)
{
	if (Game::instance == NULL)
		Game::instance = new Game(viewer);

	return Game::instance;
}

ref_ptr<Group> Game::createScene()
{
	this->scene = new Group();
	this->player = this->createPlayer();
	
	this->scene->addChild(this->player->getTransform());

	ref_ptr<Geode> track = new Geode();
	track->addDrawable(new ShapeDrawable(new Box(Vec3d(0.0, 0.0, 3.0), 5000.0, 5000.0, 1.0)));

	StateSet * stateSet = track->getOrCreateStateSet();
	stateSet->ref();

	Material * material = new Material();
	Image * track_i = readImageFile("Data/Track/track.tga");

	if (!track_i)
	{
		cout << "Couldn't load track textures." << endl;
		return NULL;
	}

	Texture2D * track_t = new Texture2D;
	track_t->setImage(track_i);

	stateSet->setAttribute(material);
	stateSet->setTextureAttributeAndModes(0, track_t, StateAttribute::ON);

	this->scene->addChild(track);

	//barriers
	Collider * barrier = this->createBarrier(Vec3d(0.0f, 0.0f, 0.0f), Functions::getQuatFromEuler(0.0, 0.0, 0.0, true));
	this->barriers.push_back(barrier);

	Optimizer optimzer;
	optimzer.optimize(this->scene);

	return this->scene;
}

Player * Game::createPlayer()
{
	ref_ptr<Node> playerCar = readNodeFile("Data/Car/car.3ds");

	if (!playerCar)
	{
		cout << "Couldn't load model ( Data/Car/car.3ds )." << endl;
		return NULL;
	}

	ref_ptr<PositionAttitudeTransform> playerCarT = new PositionAttitudeTransform();
	playerCarT->setPosition(Vec3d(0.0, 0.0, 20.0));
	playerCarT->setPivotPoint(Vec3d(-31.0, 100.0, 20.0));
	playerCarT->addChild(playerCar);

	/*Geode * sphere = new Geode();
	sphere->addDrawable(new ShapeDrawable(new Sphere(Vec3d(-31.0, 30.0, 20.0), 60.0)));
	playerCarT->addChild(sphere);*/

	ref_ptr<PlayerCollisionUpdateCallback> updateCallback = new PlayerCollisionUpdateCallback();
	playerCarT->addUpdateCallback(updateCallback);

	Player * player = new Player(playerCar, playerCarT, NULL);
	player->setFacingAngle(0.0);
	cars.push_back(player);

	return player;
}

Player * Game::getPlayer()
{
	return this->player;
}

vector<Car *> Game::getCars()
{
	return this->cars;
}

vector<Collider *> Game::getBarriers()
{
	return this->barriers;
}

Collider * Game::createBarrier(Vec3d pos, Quat rot)
{
	Node * barrier = readNodeFile("Data/Track/barrier.3ds");

	if (!barrier)
	{
		cout << "Couldn't load model ( Data/Track/barrier.3ds )." << endl;
		return NULL;
	}

	PositionAttitudeTransform * barrierT = new PositionAttitudeTransform();
	barrierT->setPosition(pos);
	barrierT->setPivotPoint(Vec3d(0.0, 0.0, 0.0));
	barrierT->setAttitude(rot);
	barrierT->setScale(Vec3d(50.0, 50.0, 50.0));
	barrierT->setInitialBound(BoundingSphere(pos, 60.0));
	barrierT->setComputeBoundingSphereCallback(new DummyComputeBoundingSphereCallback());
	cout << barrierT->getBound().radius() << endl;
	cout << barrierT->getBound().center().x() << " " << barrierT->getBound().center().y() << endl;
	barrierT->addChild(barrier);

	/*Geode * sphere = new Geode();
	sphere->addDrawable(new ShapeDrawable(new Sphere(Vec3d(0.0, 0.0, 0.0), 10.0)));
	barrierT->addChild(sphere);*/

	Geode * box = new Geode();
	Box * box_s = new Box(Vec3d(0.0, 0.0, 0.0), 20.0, 40.0, 10.0);
	ShapeDrawable * shape = new ShapeDrawable(box_s);
	box->addDrawable(shape);
	barrierT->addChild(box);

	this->scene->addChild(barrierT);

	Collider * collider = new Collider(BoundingBox(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5), barrierT);

	return collider;
}