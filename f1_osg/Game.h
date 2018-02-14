#pragma once

#include <iostream>
#include <vector>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Matrix>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

#include "Player.h"
#include "Functions.h"

using namespace std;
using namespace osg;
using namespace osgViewer;
using namespace osgDB;

class Game
{
private:
	static Game * instance;
	ref_ptr<Group> scene = NULL;
	Player * player = NULL;
	ref_ptr<Viewer> viewer = NULL;
	vector<Car *> cars;

protected:
	Player * createPlayer();
	Game(ref_ptr<Viewer> viewer);

public:
	static Game * getInstance(ref_ptr<Viewer> viewer);
	ref_ptr<Group> createScene();
	ref_ptr<Group> getScene();
	Player * getPlayer();
	vector<Car *> getCars();
};