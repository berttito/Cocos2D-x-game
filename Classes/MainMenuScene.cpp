/*
Copyright (c) 2017..
Autor: Alberto Quesada
Fecha: 5 febrero 2017
*/

#pragma once

#include "MainMenuScene.hpp"
#include "HelpScene.hpp"
#include "GameScene.h"

USING_NS_CC;

namespace game {

	Scene* MainMenuScene::createScene()
	{
		// 'scene' is an autorelease object
		auto scene = Scene::create();

		// 'layer' is an autorelease object
		auto layer = MainMenuScene::create();

		// add layer as a child to scene
		scene->addChild(layer);

		// return the scene
		return scene;
	}

	// on "init" you need to initialize your instance
	bool MainMenuScene::init()
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

		// Se crea el sprite del fondo:

		startBackground = Sprite::create("startBackground.png");
		//startBackground->setAnchorPoint(Vec2::ZERO);
		//startBackground->setPosition(0,0);
		startBackground->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		this->addChild(startBackground);
		// Creamos el boton Play:

		buttonPlay = Sprite::create();
		buttonPlay->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
		this->addChild(buttonPlay, 0);

		// Creamos el boton Help:

		buttonHelp = Sprite::create();
		buttonHelp->setPosition(Point((visibleSize.width / 3) + origin.x, (visibleSize.height / 3) + origin.y));
		this->addChild(buttonHelp, 0);

		// Le asignamos los sprites y la funcion que tiene cada boton y los colocamos en pantalla: 

		auto menu_item_1 = MenuItemImage::create("buttonPlay.png", "buttonPlay2.png", CC_CALLBACK_1(MainMenuScene::PlayButton, this));
		auto menu_item_2 = MenuItemImage::create("buttonHelp.png", "buttonHelp2.png", CC_CALLBACK_1(MainMenuScene::HelpButton, this));

		menu_item_1->setPosition(Point(visibleSize.width / 3, (visibleSize.height / 2) * 1));
		menu_item_2->setPosition(Point(visibleSize.width / 3, (visibleSize.height / 3) * 1));

		// Creamos el menu:

		auto *menu = Menu::create(menu_item_1, menu_item_2, NULL);
		menu->setPosition(Point(0, 0));
		this->addChild(menu);

		return true;
	}

	/// En este metodo le da el comportamiento al boton Play.
	void MainMenuScene::PlayButton(cocos2d::Ref *pSender)
	{
		CCLOG("PlayButton");

		auto scene = GameScene::createScene();

		Director::getInstance()->pushScene(scene);
	}

	/// En este metodo le da el comportamiento al boton Help.
	void MainMenuScene::HelpButton(cocos2d::Ref *pSender)
	{
		CCLOG("HelpButton");

		auto scene = HelpScene::createScene();

		Director::getInstance()->pushScene(scene);
	}

	/// a selector callback
	void MainMenuScene::menuCloseCallback(Ref* pSender)
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