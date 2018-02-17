
#include "Game.h"
#include "Player.h"

Player::Player(ref_ptr<Node> carNode, ref_ptr<PositionAttitudeTransform> carTransform, ref_ptr<Geode> carCollider) : Car(carNode, carTransform, carCollider)
{

}

void PlayerCollisionUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	Game * game = Game::getInstance(NULL);
	Player * player = game->getPlayer();

	BoundingSphere bBox = player->getTransform()->getBound();

	vector<PositionAttitudeTransform *> barriers = game->getBarriers();

	bool found = false;

	for (int i = 0; i < barriers.size(); i++)
	{
		if (bBox.intersects(barriers[i]->getBound()))
		{
			if (!player->findInColliders(barriers[i]))
			{
				player->addCollider(barriers[i]);
			}
		}
	}
}