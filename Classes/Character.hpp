/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Copyright (c) ...                                                          *
*  Started on:                                                                *
*  Author:                                                                    *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CHARACTER_HEADER
#define CHARACTER_HEADER


#include "BoxSprite.hpp"

namespace game
{
	class Character : public BoxSprite
	{
	private:

		static const int speed = 100;

	public:

		static Character * create()
		{
			return BoxSprite::create < Character >("garfield.png");
		}

	public:

		Character()
		{
		}

	public:

		void moveTowards(float newX, float timeDelta);
	};
}
#endif
