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

	ref_ptr<MatrixTransform> playerCarT = new MatrixTransform();
	Matrix mat;
	mat.setTrans(Vec3d(0.0, 0.0, 0.0));
	playerCarT->setMatrix(mat);

	BoundingBox playerCarBB;
	playerCarBB.init();
	playerCarBB.expandBy(playerCar->getBound());

	ref_ptr<Geode> playerCarBox = new Geode();
	float x = playerCarBB.xMin() - playerCarBB.xMax();
	float y = playerCarBB.yMin() - playerCarBB.yMax();
	float z = playerCarBB.zMin() - playerCarBB.zMax();

	cout << x << " " << y << " " << z << endl;

	playerCarBox->addDrawable(new ShapeDrawable(new Box(playerCarBB.center(), x, y, z)));

	playerCarT->addChild(playerCar);

	Player * player = new Player(playerCar, playerCarT);
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