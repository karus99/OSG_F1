#pragma once

#include <iostream>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

using namespace std;
using namespace osg;
using namespace osgViewer;
using namespace osgDB;

class Game
{
private:
	static Game * instance;
	ref_ptr<Group> scene = NULL;
	ref_ptr<Node> player = NULL;
	ref_ptr<Viewer> viewer = NULL;

protected:
	ref_ptr<Node> createPlayer();
	Game(ref_ptr<Viewer> viewer);

public:
	static Game * getInstance(ref_ptr<Viewer> viewer);
	ref_ptr<Group> createScene();
	ref_ptr<Group> getScene();
	ref_ptr<Node> getPlayer();
};