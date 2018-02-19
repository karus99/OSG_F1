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

	double distance = 600.0;
	double height = 200.0;

	switch (game->getCameraMode())
	{
	case CAMERA_2:
	{
		distance = 600.0;
		height = 300.0;
		break;
	}
	case CAMERA_3:
	{
		distance = 500.0;
		height = 100.0;
		break;
	}
	case CAMERA_4:
	{
		distance = 50.0;
		height = 50.0;

		double zRad = DegreesToRadians(player->getFacingAngle());

		double x = pos.x() - (150.0 * sin(-zRad));
		double y = pos.y() - (150.0 * cos(-zRad));

		pos = Vec3d(x, y, pos.z());
		break;
	}
	}

	double x = pos.x() + (distance * sin(-zRad));
	double y = pos.y() + (distance * cos(-zRad));

	Vec3d eye(x, y, height);
	Vec3d center(pos.x(), pos.y(), (height == 50.0) ? (50.0) : (100.0));
	Vec3d up(pos.x(), pos.y(), 9999999.0);

	this->viewer->getCamera()->setViewMatrixAsLookAt(eye, center, up);
}