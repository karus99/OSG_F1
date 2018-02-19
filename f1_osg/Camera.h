#pragma once

#include <osg\NodeCallback>
#include <osgViewer\Viewer>
#include "Game.h"

using namespace osg;
using namespace osgViewer;

#define CAMERA_1 0
#define CAMERA_2 1
#define CAMERA_3 2
#define CAMERA_4 3

class CameraUpdateCallback : public NodeCallback
{
private:
	ref_ptr<Viewer> viewer;

public:
	CameraUpdateCallback(ref_ptr<Viewer> viewer);
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
};