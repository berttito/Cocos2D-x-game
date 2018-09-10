/*
Copyright (c) 2017..
Autor: Alberto Quesada
Fecha: 5 febrero 2017
*/

#pragma once

#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

/** La clase MainMenuScene.hpp define las caracteristicas que va a tener el menu principal del juego.
*/
namespace game {

	using cocos2d::Sprite;

	class MainMenuScene : public cocos2d::Layer
	{
	private:

		Sprite * startBackground;		///Sprite del fondo
		Sprite * buttonPlay;			///Sprite del boton Play
		Sprite * buttonHelp;			///Sprite del boton Help

	public:
		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static cocos2d::Scene* createScene();

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();

		// a selector callback
		void menuCloseCallback(cocos2d::Ref* pSender);

		// implement the "static create()" method manually
		CREATE_FUNC(MainMenuScene);

		// Metodos que gestionan el comportamiento de cada uno de los botones
		void PlayButton(Ref *pSender);
		void HelpButton(Ref *pSender);

	};
}
#endif // __HELLOWORLD_SCENE_H__
#pragma once
