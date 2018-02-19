#include <iostream>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgGA/GUIEventHandler>

#include <wtypes.h>

#include "Game.h"
#include "Camera.h"

using namespace osg;
using namespace osgDB;
using namespace osgViewer;
using namespace osgGA;
using namespace std;

void getDesktopResolution(int& horizontal, int& vertical);

Collider * editorBarrier = NULL;

class KeyHandler : public GUIEventHandler
{
private:
	Viewer * viewer;
	bool cameraMode = true;
	vector<int> keysPressed = vector<int>();

public:
	KeyHandler(Viewer * viewer)
	{
		this->viewer = viewer;
	}

	virtual bool handle(const GUIEventAdapter& ea, GUIActionAdapter&)
	{
		switch (ea.getEventType())
		{
		case(GUIEventAdapter::KEYDOWN):
		{
			switch (ea.getKey())
			{
			case 65470: // F1
			{
				if (cameraMode)
				{
					viewer->setCameraManipulator(new TrackballManipulator());
				}
				else
				{
					viewer->setCameraManipulator(NULL);
					Vec3d eye(0.0, 600.0, 200.0);
					Vec3d center(0.0, 0.0, 100.0);
					Vec3d up(0.0, 0.0, 150.0);

					viewer->getCamera()->setViewMatrixAsLookAt(eye, center, up);
				}
				cameraMode = !cameraMode;
				break;
			}
			case 99:
			{
				Vec3d pos = editorBarrier->getTransform()->getPosition();
				double zAngle = editorBarrier->getFacingAngle();

				Game * game = Game::getInstance(viewer);
				editorBarrier = game->createBarrier(Vec3d(pos.x(), pos.y(), pos.z()), zAngle);

				cout << "Collider * barrier = this->createBarrier(Vec3d(" << pos.x() << ".0f, " << pos.y() << ".0f, " << pos.z() << ".0f), " << zAngle << ");" << endl;
				break;
			}
			}

			bool found = false;
			for (int i = 0; i < keysPressed.size(); i++)
			{
				if (ea.getKey() == keysPressed[i])
				{
					found = true;
				}
			}

			if(!found)
				keysPressed.push_back(ea.getKey());
			break;
		}
		case(GUIEventAdapter::KEYUP):
		{
			for (int i = 0; i < keysPressed.size(); i++)
			{
				if (ea.getKey() == keysPressed[i])
					keysPressed.erase(keysPressed.begin() + i);
			}
			break;
		}
		}

		for (int i = 0; i < keysPressed.size(); i++)
		{
			switch (keysPressed[i])
			{
			case 119:
			case 65362:
			{
				Game * game = Game::getInstance(viewer);
				Player * player = game->getPlayer();

				player->addSpeed(0.5f);
				break;
			}
			case 115:
			case 65364:
			{
				Game * game = Game::getInstance(viewer);
				Player * player = game->getPlayer();

				player->addSpeed(-0.5f);
				break;
			}
			case 97:
			case 65361:
			{
				Game * game = Game::getInstance(viewer);
				Player * player = game->getPlayer();

				player->addAngularSpeed(0.25f);
				break;
			}
			case 100:
			case 65363:
			{
				Game * game = Game::getInstance(viewer);
				Player * player = game->getPlayer();

				player->addAngularSpeed(-0.25f);
				break;
			}
			case 105:
			{
				Vec3d pos = editorBarrier->getTransform()->getPosition();
				double zAngle = editorBarrier->getFacingAngle();
				editorBarrier->setTransform(Vec3d(pos.x(), pos.y() - 5.0, pos.z()), zAngle);
				break;
			}
			case 107:
			{
				Vec3d pos = editorBarrier->getTransform()->getPosition();
				double zAngle = editorBarrier->getFacingAngle();
				editorBarrier->setTransform(Vec3d(pos.x(), pos.y() + 5.0, pos.z()), zAngle);
				break;
			}
			case 106:
			{
				Vec3d pos = editorBarrier->getTransform()->getPosition();
				double zAngle = editorBarrier->getFacingAngle();
				editorBarrier->setTransform(Vec3d(pos.x() + 5.0, pos.y(), pos.z()), zAngle);
				break;
			}
			case 108:
			{
				Vec3d pos = editorBarrier->getTransform()->getPosition();
				double zAngle = editorBarrier->getFacingAngle();
				editorBarrier->setTransform(Vec3d(pos.x() - 5.0, pos.y(), pos.z()), zAngle);
				break;
			}
			case 112:
			{
				Vec3d pos = editorBarrier->getTransform()->getPosition();
				double zAngle = editorBarrier->getFacingAngle();
				editorBarrier->setTransform(Vec3d(pos.x(), pos.y(), pos.z()), zAngle - 1.0);
				break;
			}
			case 111:
			{
				Vec3d pos = editorBarrier->getTransform()->getPosition();
				double zAngle = editorBarrier->getFacingAngle();
				editorBarrier->setTransform(Vec3d(pos.x(), pos.y(), pos.z()), zAngle + 1.0);
				break;
			}
			}
		}

		if (keysPressed.empty())
			return false;
		else
			return true;
	}
};

int main(int argc, char * argv[])
{
	Viewer * viewer = new Viewer();

	Game * game = Game::getInstance(viewer);
	ref_ptr<Group> scene = game->createScene();

	int s_width, s_height;
	getDesktopResolution(s_width, s_height);

	viewer->setUpViewInWindow(100, 100, s_width - 200, s_height - 200);
	viewer->setSceneData(scene);

	ref_ptr<WindowSizeHandler> windowHandler = new WindowSizeHandler();
	ref_ptr<KeyHandler> keyHandler = new KeyHandler(viewer);
	viewer->addEventHandler(new StatsHandler);
	viewer->addEventHandler(windowHandler);
	viewer->addEventHandler(keyHandler);
	viewer->setLightingMode(osg::View::LightingMode::HEADLIGHT);
	viewer->realize();

	editorBarrier = game->createBarrier(Vec3d(), 0.0);

	Vec3d eye(0.0, 600.0, 200.0);
	Vec3d center(0.0, 0.0, 100.0);
	Vec3d up(0.0, 0.0, 150.0);

	viewer->getCamera()->setViewMatrixAsLookAt(eye, center, up);
	viewer->getCamera()->setClearColor(Vec4(1, 1, 1, 1.0));

	ref_ptr<CameraUpdateCallback> cameraUpdateCallback = new CameraUpdateCallback(viewer);
	viewer->getCamera()->addUpdateCallback(cameraUpdateCallback);

	Player * player = game->getPlayer();
	vector<Car *> cars = game->getCars();

	while (!viewer->done())
	{
		for (int i = 0; i < cars.size(); i++)
		{
			cars[i]->update();
		}

		viewer->frame();
	}
}

void getDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;

	const HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &desktop);

	horizontal = desktop.right;
	vertical = desktop.bottom;
}