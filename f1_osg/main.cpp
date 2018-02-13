#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Material>
#include <osg/Texture2D>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <wtypes.h>

using namespace osg;
using namespace osgDB;
using namespace osgViewer;
using namespace std;

void getDesktopResolution(int& horizontal, int& vertical);

Node * createScene()
{
	Group * scene = new Group();

	Node * playerCar = readNodeFile("Data/Car/car.3ds");

	if (!playerCar)
	{
		cout << "Couldn't load model ( Data/Car/car.3ds )." << endl;
		return NULL;
	}

	StateSet * stateSet = playerCar->getOrCreateStateSet();
	stateSet->ref();

	Material *material = new Material();
	Image *body_i = readImageFile("Data/Car/body.jpg");
	Image *frontup_i = readImageFile("Data/Car/frontup.jpg");

	if (!body_i || !frontup_i)
	{
		cout << "Couldn't load textures." << endl;
		return NULL;
	}

	Texture2D *body_t = new Texture2D;
	body_t->setImage(body_i);

	Texture2D *frontup_t = new Texture2D;
	frontup_t->setImage(frontup_i);

	stateSet->setAttribute(material);
	stateSet->setTextureAttributeAndModes(1, body_t, StateAttribute::ON);
	stateSet->setTextureAttributeAndModes(0, frontup_t, StateAttribute::ON);

	scene->addChild(playerCar);

	return scene;
}

int main(int argc, char * argv[])
{
	Node * scene = createScene();
	Viewer viewer;
	int s_width, s_height;
	getDesktopResolution(s_width, s_height);

	viewer.setUpViewInWindow(100, 100, s_width - 200, s_height - 200);
	viewer.setSceneData(scene);
	return viewer.run();
}

void getDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;

	const HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &desktop);

	horizontal = desktop.right;
	vertical = desktop.bottom;
}