#pragma once

#include <osgGA/GUIEventHandler>

#include "Car.h"

using namespace osgGA;

class Player : public Car
{
public:
	Player(ref_ptr<Node> carNode, ref_ptr<MatrixTransform> carTransform);
};