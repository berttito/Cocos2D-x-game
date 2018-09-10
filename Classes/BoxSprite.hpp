/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by Ángel on november of 2016                                       *
*  This is free software released into the public domain.                     *
*  angel.rodriguez@esne.edu                                                   *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef GAME_BOXSPRITE_HEADER
#define GAME_BOXSPRITE_HEADER

#include <cocos2d.h>

namespace game
{

	class BoxSprite : public cocos2d::Sprite
	{
	protected:

		template< class DERIVED_CLASS >
		static DERIVED_CLASS * create(const char * textureName);

	protected:

		float halfWidth;
		float halfHeight;

	protected:

		BoxSprite()
		{
			this->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
		}

		virtual ~BoxSprite()
		{
		}

	public:

		float leftX() const { return getPositionX() - halfWidth; }
		float rightX() const { return getPositionX() + halfWidth; }
		float topY() const { return getPositionY() + halfHeight; }
		float bottomY() const { return getPositionY() - halfHeight; }

	public:

		void  setLeftX(float newX) { setPositionX(newX + halfWidth); }
		void  setRightX(float newX) { setPositionX(newX - halfWidth); }
		void  setTopY(float newY) { setPositionY(newY - halfHeight); }
		void  setBottomY(float newY) { setPositionY(newY + halfHeight); }

	};

	template< class DERIVED_CLASS >
	DERIVED_CLASS * BoxSprite::create(const char * textureName)
	{
		std::unique_ptr< DERIVED_CLASS > sprite(new (std::nothrow) DERIVED_CLASS);

		if (sprite)
		{
			if (sprite->initWithFile(textureName))
			{
				sprite->halfWidth = sprite->getBoundingBox().size.width / 2.f;
				sprite->halfHeight = sprite->getBoundingBox().size.height / 2.f;

				sprite->autorelease();

				return sprite.release();
			}
		}

		return nullptr;
	}

}

#endif

