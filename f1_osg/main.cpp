#include <iostream>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgGA/GUIEventHandler>

#include <wtypes.h>

#include "Game.h"

using namespace osg;
using namespace osgDB;
using namespace osgViewer;
using namespace osgGA;
using namespace std;

void getDesktopResolution(int& horizontal, int& vertical);

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
			// 65362, 119 - up
			// 65361, 97 - left
			// 65363, 100 - right
			// 65364, 115 - down

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

				player->addAngularSpeed(0.5f);
				break;
			}
			case 100:
			case 65363:
			{
				Game * game = Game::getInstance(viewer);
				Player * player = game->getPlayer();

				player->addAngularSpeed(-0.5f);
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
	viewer->realize();

	Vec3d eye(0.0, 600.0, 200.0);
	Vec3d center(0.0, 0.0, 100.0);
	Vec3d up(0.0, 0.0, 150.0);

	viewer->getCamera()->setViewMatrixAsLookAt(eye, center, up);

	Player * player = game->getPlayer();
	//player->addSpeed(20.0f);
	vector<Car *> cars = game->getCars();

	while (!viewer->done())
	{
		//cout << "pSpeed: " << player->getSpeed() << endl;

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