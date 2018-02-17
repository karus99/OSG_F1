#include "Camera.h"

CameraUpdateCallback::CameraUpdateCallback(ref_ptr<Viewer> viewer)
{
	this->viewer = viewer;
}

void CameraUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	Game * game = Game::getInstance(NULL);
	Player * player = game->getPlayer();

	Vec3d pos = player->getTransform()->getPosition();
	double zRad = DegreesToRadians(player->getFacingAngle());

	double x = pos.x() + (600.0 * sin(-zRad));
	double y = pos.y() + (600.0 * cos(-zRad));

	Vec3d eye(x, y, 200.0);
	Vec3d center(pos.x(), pos.y(), 100.0);
	Vec3d up(pos.x(), pos.y(), 9999999.0);

	this->viewer->getCamera()->setViewMatrixAsLookAt(eye, center, up);
}