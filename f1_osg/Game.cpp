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

	createLight();

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

	Box * box = new Box(Vec3d(0.0, -68.0, 30.0), 70, 175, 60);

	ref_ptr<PlayerCollisionUpdateCallback> updateCallback = new PlayerCollisionUpdateCallback();
	playerCarT->addUpdateCallback(updateCallback);

	Player * player = new Player(playerCar, playerCarT, box);
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
	barrierT->addChild(barrier);

	Box * box = new Box(pos, 140.0, 20.0, 80.0);
	box->setRotation(rot);

	this->scene->addChild(barrierT);

	Collider * collider = new Collider(box, barrierT);

	return collider;
}

ref_ptr<Group> Game::getScene()
{
	return this->scene;
}

void Game::createLight()
{
	StateSet* state = this->scene->getOrCreateStateSet();
	state->setMode(GL_LIGHTING, StateAttribute::ON);
	state->setMode(GL_LIGHT0, StateAttribute::ON); // for first light

	ref_ptr<Light> light0 = new Light;
	light0->setPosition(Vec4(0, 0, 100, 1.0));
	light0->setAmbient(Vec4(1.0, 1.0, 1.0, 1.0));
	light0->setDiffuse(Vec4(1.0, 1.0, 1.0, 1.0));
	light0->setSpecular(Vec4(1, 1, 1, 1));
	light0->setDirection(Vec3(0, 0, 0));
	light0->setLightNum(0);

	ref_ptr<LightSource> source0 = new LightSource;
	source0->setLight(light0.get());
	this->scene->addChild(source0);
}