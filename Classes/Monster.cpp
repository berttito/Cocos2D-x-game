/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by Ángel on november of 2016                                       *
*  This is free software released into the public domain.                     *
*  angel.rodriguez@esne.edu                                                   *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <memory>
#include "Monster.hpp"

using namespace cocos2d;

namespace game
{
	void Monster::addMonster(float dt)
	{
		auto monster = Sprite::create("fruit.png");

		// 1
		auto monsterContentSize = monster->getContentSize();
		auto selfContentSize = this->getContentSize();
		int minY = monsterContentSize.height / 2;
		int maxY = selfContentSize.height - monsterContentSize.height / 2;
		int rangeY = maxY - minY;
		int randomY = (rand() % rangeY) + minY;

		monster->setPosition(Vec2(selfContentSize.width + monsterContentSize.width / 2, randomY));
		this->addChild(monster, 1);

		// 2
		int minDuration = 2.0;
		int maxDuration = 4.0;
		int rangeDuration = maxDuration - minDuration;
		int randomDuration = (rand() % rangeDuration) + minDuration;

		// 3
		auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width / 2, randomY));
		auto actionRemove = RemoveSelf::create();
		monster->runAction(Sequence::create(actionMove, actionRemove, nullptr));
	}
}
