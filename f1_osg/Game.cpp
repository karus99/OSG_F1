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
	PositionAttitudeTransform * barrier = this->createBarrier(Vec3d(0.0f, 0.0f, 0.0f), Functions::getQuatFromEuler(0.0, 0.0, 0.0, true));
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

	playerCarT->dirtyBound();

	ref_ptr<Geode> playerCarBox = new Geode();

	ref_ptr<PlayerCollisionUpdateCallback> updateCallback = new PlayerCollisionUpdateCallback();
	playerCarT->addUpdateCallback(updateCallback);

	//ref_ptr<Group> decorator = new Group();

	//playerCarBox->addDrawable(new ShapeDrawable(new Box(Vec3d(-31.0, -80.0, 30.0), 90, 180, 60)));

	//decorator->addChild(playerCarBox);

	//ref_ptr<StateSet> stateset = new StateSet;
	//ref_ptr<PolygonOffset> polyoffset = new PolygonOffset;
	//polyoffset->setFactor(-1.0f);
	//polyoffset->setUnits(-1.0f);
	//ref_ptr<PolygonMode> polymode = new PolygonMode;
	//polymode->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
	//stateset->setAttributeAndModes(polyoffset, StateAttribute::OVERRIDE | StateAttribute::ON);
	//stateset->setAttributeAndModes(polymode, StateAttribute::OVERRIDE | StateAttribute::ON);
	//stateset->setTextureMode(0, GL_TEXTURE_2D, StateAttribute::OVERRIDE | StateAttribute::OFF);
	//decorator->setStateSet(stateset);

	//playerCarT->addChild(decorator);
	playerCarT->addChild(playerCar);

	Player * player = new Player(playerCar, playerCarT, playerCarBox);
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

vector<PositionAttitudeTransform *> Game::getBarriers()
{
	return this->barriers;
}

PositionAttitudeTransform * Game::createBarrier(Vec3d pos, Quat rot)
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
	barrierT->dirtyBound();

	//ref_ptr<Group> decorator = new Group();

	//Geode * barrierBox = new Geode();
	//barrierBox->addDrawable(new ShapeDrawable(new Box(Vec3d(0, 0, 0), 10, 10, 10)));

	//decorator->addChild(barrierBox);

	//ref_ptr<StateSet> stateset = new StateSet;
	//ref_ptr<PolygonOffset> polyoffset = new PolygonOffset;
	//polyoffset->setFactor(-1.0f);
	//polyoffset->setUnits(-1.0f);
	//ref_ptr<PolygonMode> polymode = new PolygonMode;
	//polymode->setMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE);
	//stateset->setAttributeAndModes(polyoffset, StateAttribute::OVERRIDE | StateAttribute::ON);
	//stateset->setAttributeAndModes(polymode, StateAttribute::OVERRIDE | StateAttribute::ON);
	//stateset->setTextureMode(0, GL_TEXTURE_2D, StateAttribute::OVERRIDE | StateAttribute::OFF);
	//decorator->setStateSet(stateset);

	//barrierT->addChild(decorator);
	barrierT->addChild(barrier);

	this->scene->addChild(barrierT);

	return barrierT;
}