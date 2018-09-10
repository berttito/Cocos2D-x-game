/*
Copyright (c) 2017..
Autor: Alberto Quesada
Fecha: 5 febrero 2017
*/

#pragma once

#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"

/** La clase HelpScene.hpp define las caracteristicas que va a tener el menu de ayuda del juego.
*/
namespace game {

	using cocos2d::Sprite;
	using cocos2d::Label;

	class HelpScene : public cocos2d::Layer
	{
	private:

		Sprite * background;		///Sprite del fondo
		Sprite * buttonGoBack;		///Sprite del boton Go Back

		Label * infoLabel;

	public:
		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static cocos2d::Scene* createScene();

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();

		// a selector callback
		void menuCloseCallback(cocos2d::Ref* pSender);

		// implement the "static create()" method manually
		CREATE_FUNC(HelpScene);

		// Metodos que gestionan el comportamiento del boton GoBack
		void GoBackButton(Ref *pSender);
		
	};
}
#endif
