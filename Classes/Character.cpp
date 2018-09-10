/*
Copyright(c) 2017
Autor: Alberto Quesada
Fecha: 5 enero 2017
*/

#pragma once

#include <memory>
#include "Character.hpp"

using namespace cocos2d;


/** La clase Character.cpp implementa el movimiento que va a tener el personaje en el juego.
*/
namespace game
{
	void Character::moveTowards(float targetY, float timeDelta)
	{
		float currentY = getPositionY();

		float currentX = getPositionX();

		if (int(targetY) != int(currentY))
		{
			float newY = currentY + (currentY < targetY ? +speed : -speed) * timeDelta;

			// Se ajusta la nueva posición para que el personaje no se salga de la pantalla:

			Size  sceneSize = Director::getInstance()->getVisibleSize();

			if (newY - halfHeight < 0.f)
			{
				newY = halfHeight;
			}
			else
				if (newY + halfHeight > sceneSize.height)
				{
					newY = sceneSize.height - halfHeight;
				}

			this->setPositionY(newY);
			
		}
	}
	
}
