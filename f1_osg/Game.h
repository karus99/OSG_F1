#pragma once

#include <iostream>
#include <vector>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Material>
#include <osg/Matrix>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osg/PolygonOffset>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osgViewer/Viewer>

#include "Player.h"
#include "Functions.h"

using namespace osg;
using namespace osgDB;
using namespace osgUtil;
using namespace osgViewer;
using namespace std;

class Game
{
private:
	static Game * instance;
	ref_ptr<Group> scene = NULL;
	Player * player = NULL;
	ref_ptr<Viewer> viewer = NULL;
	vector<Car *> cars = vector<Car *>();
	vector<Collider *> barriers = vector<Collider *>();
	int cameraMode = -1;

	void createLight();

protected:
	Player * createPlayer();
	Game(ref_ptr<Viewer> viewer);

public:
	static Game * getInstance(ref_ptr<Viewer> viewer);
	ref_ptr<Group> createScene();
	ref_ptr<Group> getScene();
	Player * getPlayer();
	Car * createCar(Vec3d pos, double angle);
	vector<Car *> getCars();
	vector<Collider *> getBarriers();
	Collider * createBarrier(Vec3d pos, double zAngle);
	int getCameraMode();
	void setNextCameraMode();
};