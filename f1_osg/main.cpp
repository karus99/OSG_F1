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

public:
	KeyHandler(Viewer * viewer)
	{
		this->viewer = viewer;
	}

public:
	virtual bool handle(const GUIEventAdapter& ea, GUIActionAdapter&)
	{
		switch (ea.getEventType())
		{
		case(GUIEventAdapter::KEYDOWN):
		{
			cout << "Key pressed: " << ea.getKey() << endl;
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
			}
					
		}

		default:
			return false;
		}
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

	while (!viewer->done())
	{
		cout << "Frame" << endl;
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