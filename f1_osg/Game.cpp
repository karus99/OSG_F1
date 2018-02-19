#include "Game.h"
#include "Camera.h"

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

	// track
	ref_ptr<Geode> track = new Geode();
	track->addDrawable(new ShapeDrawable(new Box(Vec3d(0.0, 0.0, 3.0), 10000.0, 10000.0, 1.0)));

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
	track_t->setUseHardwareMipMapGeneration(true);
	track_t->setMaxAnisotropy(16.0f);

	stateSet->setAttribute(material);
	stateSet->setTextureAttributeAndModes(0, track_t, StateAttribute::ON);

	this->scene->addChild(track);

	// sky_1
	ref_ptr<Geode> sky = new Geode();
	Sphere * sky_b = new Sphere(Vec3d(0.0, 0.0, 0.0), 7071.0);
	sky->addDrawable(new ShapeDrawable(sky_b));

	stateSet = sky->getOrCreateStateSet();
	stateSet->ref();

	material = new Material();
	Image * sky_i = readImageFile("Data/Skybox/skybox.png");

	if (!sky_i)
	{
		cout << "Couldn't load skybox textures." << endl;
		return NULL;
	}

	Texture2D * sky_t = new Texture2D;
	sky_t->setImage(sky_i);
	sky_t->setUseHardwareMipMapGeneration(true);
	sky_t->setMaxAnisotropy(16.0f);

	stateSet->setAttribute(material);
	stateSet->setTextureAttributeAndModes(0, sky_t, StateAttribute::ON);

	this->scene->addChild(sky);

	//barriers
	/*Collider * barrier = this->createBarrier(Vec3d(0.0f, 0.0f, 0.0f), 0.0);
	this->barriers.push_back(barrier);*/

	// barriers
	Collider * barrier = this->createBarrier(Vec3d(-2695.0f, 1080.0f, 0.0f), -91);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2695.0f, 910.0f, 0.0f), -90);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2695.0f, 710.0f, 0.0f), -90);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2695.0f, 525.0f, 0.0f), -90);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2695.0f, 340.0f, 0.0f), -91);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2705.0f, 110.0f, 0.0f), -91);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2715.0f, -110.0f, 0.0f), -91);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2735.0f, -385.0f, 0.0f), -94);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2760.0f, -635.0f, 0.0f), -101);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2830.0f, -850.0f, 0.0f), -116);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2680.0f, 1285.0f, 0.0f), -91);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2675.0f, 1510.0f, 0.0f), -91);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2675.0f, 1715.0f, 0.0f), -84);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2730.0f, 1905.0f, 0.0f), -64);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2805.0f, 2065.0f, 0.0f), -64);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-2930.0f, 2155.0f, 0.0f), -42);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3065.0f, 2245.0f, 0.0f), -25);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-4205.0f, 2460.0f, 0.0f), -25);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-4065.0f, 2385.0f, 0.0f), -25);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3915.0f, 2295.0f, 0.0f), -25);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3760.0f, 2200.0f, 0.0f), -29);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3615.0f, 2095.0f, 0.0f), -41);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3525.0f, 1965.0f, 0.0f), -71);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3510.0f, 1770.0f, 0.0f), -111);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3565.0f, -875.0f, 0.0f), -33);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3510.0f, -1045.0f, 0.0f), -102);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3570.0f, -1225.0f, 0.0f), -117);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3675.0f, -1365.0f, 0.0f), -133);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3800.0f, -1520.0f, 0.0f), -133);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3920.0f, -1660.0f, 0.0f), -133);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4540.0f, 2840.0f, 0.0f), -45);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4665.0f, 2695.0f, 0.0f), -54);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4780.0f, 2515.0f, 0.0f), -60);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4850.0f, 2345.0f, 0.0f), -80);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4880.0f, 2130.0f, 0.0f), -80);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4910.0f, 1895.0f, 0.0f), -89);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4925.0f, 1680.0f, 0.0f), -89);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4925.0f, 1450.0f, 0.0f), -91);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4925.0f, 1205.0f, 0.0f), -91);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4895.0f, 975.0f, 0.0f), -101);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4855.0f, 755.0f, 0.0f), -101);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4810.0f, 480.0f, 0.0f), -101);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4750.0f, 220.0f, 0.0f), -108);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(4660.0f, 45.0f, 0.0f), -123);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(3130.0f, -715.0f, 0.0f), -176);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(2935.0f, -730.0f, 0.0f), -176);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(2740.0f, -745.0f, 0.0f), -176);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(2560.0f, -745.0f, 0.0f), -176);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(2380.0f, -745.0f, 0.0f), -176);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(2200.0f, -745.0f, 0.0f), -176);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(2010.0f, -740.0f, 0.0f), -193);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(1835.0f, -700.0f, 0.0f), -200);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(1685.0f, -600.0f, 0.0f), -219);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(1535.0f, -495.0f, 0.0f), -219);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(1380.0f, -375.0f, 0.0f), -219);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(1250.0f, -250.0f, 0.0f), -224);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(1120.0f, -105.0f, 0.0f), -234);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(990.0f, 25.0f, 0.0f), -223);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(820.0f, 100.0f, 0.0f), -196);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(585.0f, 50.0f, 0.0f), -158);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3040.0f, -4700.0f, 0.0f), -190);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3225.0f, -4670.0f, 0.0f), -190);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3390.0f, -4600.0f, 0.0f), -213);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3555.0f, -4500.0f, 0.0f), -213);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3710.0f, -4385.0f, 0.0f), -226);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3845.0f, -4250.0f, 0.0f), -226);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-3980.0f, -4080.0f, 0.0f), -244);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-4110.0f, -3900.0f, 0.0f), -244);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-4215.0f, -3705.0f, 0.0f), -248);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-4290.0f, -3540.0f, 0.0f), -248);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(20.0f, 795.0f, 0.0f), -148);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-150.0f, 700.0f, 0.0f), -148);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-315.0f, 595.0f, 0.0f), -136);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-450.0f, 465.0f, 0.0f), -136);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-590.0f, 330.0f, 0.0f), -136);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-755.0f, 160.0f, 0.0f), -130);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-860.0f, -5.0f, 0.0f), -112);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-930.0f, -235.0f, 0.0f), -104);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-975.0f, -460.0f, 0.0f), -94);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-985.0f, -675.0f, 0.0f), -92);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-985.0f, -920.0f, 0.0f), -89);
	this->barriers.push_back(barrier);
	barrier = this->createBarrier(Vec3d(-940.0f, -1160.0f, 0.0f), -59);
	this->barriers.push_back(barrier);

	// cars
	Car * car = this->createCar(Vec3d(-4135.0f, 1260.0f, 20.0f), 0);
	this->scene->addChild(car->getTransform());
	this->barriers.push_back(car->getColliderNode());
	car = this->createCar(Vec3d(-3945.0f, 1260.0f, 20.0f), 0);
	this->scene->addChild(car->getTransform());
	this->barriers.push_back(car->getColliderNode());
	car = this->createCar(Vec3d(-3760.0f, 1260.0f, 20.0f), 0);
	this->scene->addChild(car->getTransform());
	this->barriers.push_back(car->getColliderNode());
	car = this->createCar(Vec3d(-3575.0f, 1260.0f, 20.0f), 0);
	this->scene->addChild(car->getTransform());
	this->barriers.push_back(car->getColliderNode());
	car = this->createCar(Vec3d(-3575.0f, -665.0f, 20.0f), 180);
	this->scene->addChild(car->getTransform());
	this->barriers.push_back(car->getColliderNode());
	car = this->createCar(Vec3d(-3745.0f, -665.0f, 20.0f), 180);
	this->scene->addChild(car->getTransform());
	this->barriers.push_back(car->getColliderNode());
	car = this->createCar(Vec3d(-3910.0f, -660.0f, 20.0f), 180);
	this->scene->addChild(car->getTransform());
	this->barriers.push_back(car->getColliderNode());
	car = this->createCar(Vec3d(-4080.0f, -660.0f, 20.0f), 180);
	this->scene->addChild(car->getTransform());
	this->barriers.push_back(car->getColliderNode());

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

	Vec3d pos = Vec3d(-4225.0f, 260.0f, 20.0f);
	double angle = 85;

	ref_ptr<PositionAttitudeTransform> playerCarT = new PositionAttitudeTransform();
	playerCarT->setPosition(pos);
	playerCarT->setPivotPoint(Vec3d(-31.0, 100.0, 20.0));
	playerCarT->addChild(playerCar);

	double zRad = DegreesToRadians(angle);

	double x = pos.x() - (68.0 * sin(-zRad));
	double y = pos.y() - (68.0 * cos(-zRad));

	Box * box = new Box(Vec3d(x, y, 30.0), 70, 175, 60);
	box->setRotation(Functions::getQuatFromEuler(0.0, 0.0, angle, true));

	ref_ptr<PlayerCollisionUpdateCallback> updateCallback = new PlayerCollisionUpdateCallback();
	playerCarT->addUpdateCallback(updateCallback);

	Player * player = new Player(playerCar, playerCarT, box);
	player->setFacingAngle(angle);
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

Collider * Game::createBarrier(Vec3d pos, double zAngle)
{
	Node * barrier = readNodeFile("Data/Track/barrier.3ds");

	if (!barrier)
	{
		cout << "Couldn't load model ( Data/Track/barrier.3ds )." << endl;
		return NULL;
	}

	StateSet * stateSet = barrier->getOrCreateStateSet();
	stateSet->ref();

	Material * material = new Material();
	Image * barrier_i = readImageFile("Data/Track/concrete.jpg");

	if (!barrier_i)
	{
		cout << "Couldn't load barrier textures." << endl;
		return NULL;
	}

	Texture2D * barrier_t = new Texture2D;
	barrier_t->setImage(barrier_i);
	barrier_t->setUseHardwareMipMapGeneration(true);
	barrier_t->setMaxAnisotropy(16.0f);
	stateSet->setAttribute(material);
	stateSet->setTextureAttributeAndModes(0, barrier_t, StateAttribute::ON);

	PositionAttitudeTransform * barrierT = new PositionAttitudeTransform();
	barrierT->setPosition(pos);
	barrierT->setPivotPoint(Vec3d(0.0, 0.0, 0.0));
	barrierT->setAttitude(Functions::getQuatFromEuler(0.0, 0.0, zAngle, true));
	barrierT->setScale(Vec3d(50.0, 50.0, 50.0));
	barrierT->addChild(barrier);

	Box * box = new Box(pos, 140.0, 20.0, 80.0);
	box->setRotation(Functions::getQuatFromEuler(0.0, 0.0, zAngle, true));

	this->scene->addChild(barrierT);

	Collider * collider = new Collider(box, barrierT, zAngle, COLLIDER_BARRIER);

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

Car * Game::createCar(Vec3d pos, double angle)
{
	ref_ptr<Node> car = readNodeFile("Data/Car/car.3ds");

	if (!car)
	{
		cout << "Couldn't load model ( Data/Car/car.3ds )." << endl;
		return NULL;
	}

	ref_ptr<PositionAttitudeTransform> carT = new PositionAttitudeTransform();
	carT->setPosition(pos);
	carT->setPivotPoint(Vec3d(-31.0, 100.0, 20.0));
	carT->setAttitude(Functions::getQuatFromEuler(0.0, 0.0, angle, true));
	carT->addChild(car);

	double zRad = DegreesToRadians(angle);

	double x = pos.x() - (68.0 * sin(-zRad));
	double y = pos.y() - (68.0 * cos(-zRad));

	Box * box = new Box(Vec3d(x, y, 30.0), 70, 175, 60);
	box->setRotation(Functions::getQuatFromEuler(0.0, 0.0, angle, true));

	Car * carO = new Car(car, carT, box);
	carO->setFacingAngle(angle);
	cars.push_back(carO);

	Collider * collider = new Collider(box, carT, angle, COLLIDER_CAR);
	carO->addColliderNode(collider);

	return carO;
}

int Game::getCameraMode()
{
	return this->cameraMode;
}

void Game::setNextCameraMode()
{
	cameraMode++;

	if (cameraMode > CAMERA_4)
	{
		cameraMode = CAMERA_1;
	}
}