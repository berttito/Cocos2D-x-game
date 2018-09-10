/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Copyright (c) ...                                                          *
*  Started on:                                                                *
*  Author:                                                                    *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MONSTER_HEADER
#define MONSTER_HEADER


#include "BoxSprite.hpp"

namespace game
{
	class Monster : public BoxSprite
	{
	private:

		//static const int speed = 100;

	public:

		static Monster * create()
		{
			return BoxSprite::create < Monster >("fruit.png");
		}

	public:

		Monster()
		{
		}

	public:

		void addMonster(float dt);
	};
}
#endif