/*
Copyright (c) 2017..
Autor: Alberto Quesada
Fecha: 5 febrero 2017
*/

#pragma once

#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "cocos2d.h"

/** La clase IntroScene.hpp define las caracteristicas que va a tener la pantalla de inicio del juego.
*/
namespace game {

	using cocos2d::Sprite;

	class IntroScene : public cocos2d::Layer
	{
	private:
		
		Sprite * introSprite;		///Sprite del logo
		Sprite * buttonContinue;	///Sprite del boton continue

	public:
		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static cocos2d::Scene* createScene();

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();

		// a selector callback
		void menuCloseCallback(cocos2d::Ref* pSender);

		// implement the "static create()" method manually
		CREATE_FUNC(IntroScene);

		// Metodo que gestiona el comportamiento del boton de continue
		void ContinueButton(Ref *pSender);
	};
}
#endif // __INTRO_SCENE_H__
