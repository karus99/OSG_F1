#pragma once

#include <osg\NodeCallback>
#include <osgViewer\Viewer>
#include "Game.h"

using namespace osg;
using namespace osgViewer;

class CameraUpdateCallback : public NodeCallback
{
private:
	ref_ptr<Viewer> viewer;

public:
	CameraUpdateCallback(ref_ptr<Viewer> viewer);
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
};