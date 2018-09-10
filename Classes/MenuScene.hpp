/*
	Copyright (c) 2017..
	Autor: Alberto Quesada
	Fecha: 5 febrero 2017
*/

#pragma once

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

/** La clase MenuScene.h define las caracteristicas que va a tener el menu de pausa del juego.
*/
namespace game {

	using cocos2d::Sprite;	

	class MenuScene : public cocos2d::Layer
	{
	private:

		Sprite * background;		///Sprite del fondo
		Sprite * buttonRestart;		///Sprite del boton Restart
		Sprite * buttonResume;		///Sprite del boton Resume
		Sprite * buttonHelp;		///Sprite del boton Help

	public:
		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static cocos2d::Scene* createScene();

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();

		// a selector callback
		void menuCloseCallback(cocos2d::Ref* pSender);

		// implement the "static create()" method manually
		CREATE_FUNC(MenuScene);

		// Metodos que gestionan el comportamiento de cada uno de los botones
		void RestartButton(Ref *pSender);
		void ResumeButton(Ref *pSender);
		void HelpButton(Ref *pSender);
		
	};
}
#endif // __HELLOWORLD_SCENE_H__
