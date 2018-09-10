/*
Copyright (c) 2017..
Autor: Alberto Quesada
Fecha: 5 febrero 2017
*/

#pragma once

#include "GameScene.h"
#include "IntroScene.hpp"
#include "MainMenuScene.hpp"

USING_NS_CC;

/** La clase IntroScene.cpp implementa las caracteristicas que va a tener la pantalla de inicio del juego.
*/
namespace game {

	Scene* IntroScene::createScene()
	{
		// 'scene' is an autorelease object
		auto scene = Scene::create();

		// 'layer' is an autorelease object
		auto layer = IntroScene::create();

		// add layer as a child to scene
		scene->addChild(layer);

		// return the scene
		return scene;
	}

	// on "init" you need to initialize your instance
	bool IntroScene::init()
	{
		//////////////////////////////
		// 1. super init first
		if (!Layer::init())
		{
			return false;
		}

		// Se toma el tamaño visible del display para colocar los elementos gráficos
		// usando posiciones relativas (en lugar de absolutas):

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		// Se crea el sprite del logo:

		introSprite = Sprite::create("logo.png");		
		introSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		this->addChild(introSprite);
		
		// Creamos el boton restart:

		buttonContinue = Sprite::create();
		buttonContinue->setPosition(Point((visibleSize.width / 3) + origin.x, (visibleSize.height / 3) + origin.y));
		this->addChild(buttonContinue, 0);

		// Le asignamos los sprites y la funcion que tiene cada boton y los colocamos en pantalla: 

		auto menu_item_1 = MenuItemImage::create("buttonContinue.png", "buttonContinue2.png", CC_CALLBACK_1(IntroScene::ContinueButton, this));		

		menu_item_1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 5.f));
		
		// Creamos el menu:

		auto *menu = Menu::create(menu_item_1, NULL);
		menu->setPosition(Point(0, 0));
		this->addChild(menu);

		return true;
	}

	/// En este metodo le da el comportamiento al boton Continue.
	void IntroScene::ContinueButton(cocos2d::Ref *pSender)
	{
		CCLOG("ContinueButton");

		auto scene = MainMenuScene::createScene();

		Director::getInstance()->pushScene(scene);
	}

	/// a selector callback
	void IntroScene::menuCloseCallback(Ref* pSender)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
		return;
#endif

		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}
}