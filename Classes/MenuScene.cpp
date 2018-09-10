/*
Copyright (c) 2017..
Autor: Alberto Quesada
Fecha: 5 febrero 2017
*/

#pragma once

#include "MenuScene.hpp"
#include "HelpScene.hpp"
#include "GameScene.h"

USING_NS_CC;

/** La clase MenuScene.cpp implementa las caracteristicas que va a tener el menu de pausa del juego.
*/
namespace game {

	Scene* MenuScene::createScene()
	{
		// 'scene' is an autorelease object
		auto scene = Scene::create();

		// 'layer' is an autorelease object
		auto layer = MenuScene::create();

		// add layer as a child to scene
		scene->addChild(layer);

		// return the scene
		return scene;
	}

	// on "init" you need to initialize your instance
	bool MenuScene::init()
	{
		//////////////////////////////
		// 1. super init first
		if (!Layer::init())
		{
			return false;
		}

		// Se crea el sprite del fondo:

		background = Sprite::create("background2.jpg");
		background->setAnchorPoint(Vec2::ZERO);
		background->setPosition(0, 0);
		this->addChild(background);

		// Se toma el tamaño visible del display para colocar los elementos gráficos
		// usando posiciones relativas (en lugar de absolutas):

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		// Creamos el boton restart:

		buttonRestart = Sprite::create();
		buttonRestart->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
		this->addChild(buttonRestart, 0);

		// Creamos el boton resume:

		buttonResume = Sprite::create();
		buttonResume->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
		this->addChild(buttonResume, 0);

		// Creamos el boton help:

		buttonHelp = Sprite::create();
		buttonHelp->setPosition(Point((visibleSize.width / 3) + origin.x, (visibleSize.height / 3) + origin.y));
		this->addChild(buttonHelp, 0);

		// Le asignamos los sprites y la funcion que tiene cada boton y los colocamos en pantalla: 

		auto menu_item_1 = MenuItemImage::create("buttonRestart.png", "buttonRestart2.png", CC_CALLBACK_1(MenuScene::RestartButton, this));
		auto menu_item_2 = MenuItemImage::create("buttonResume.png", "buttonResume2.png", CC_CALLBACK_1(MenuScene::ResumeButton, this));
		auto menu_item_3 = MenuItemImage::create("buttonHelpMenu.png", "buttonHelpMenu2.png", CC_CALLBACK_1(MenuScene::HelpButton, this));		

		menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 4.f));
		menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 2.5f));
		menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 1.f));
		
		// Creamos el menu:

		auto *menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, NULL);
		menu->setPosition(Point(0, 0));
		this->addChild(menu);

		return true;
	}
	
	/// En este metodo le da el comportamiento al boton Restart.
	void MenuScene::RestartButton(cocos2d::Ref *pSender)
	{
		CCLOG("Restart");
		
		auto scene = GameScene::createScene();

		Director::getInstance()->replaceScene(scene);		
	}

	/// En este metodo le da el comportamiento al boton Resume.
	void MenuScene::ResumeButton(cocos2d::Ref *pSender)
	{
		CCLOG("Resume");		

		Director::getInstance()->popScene();
	}	

	/// En este metodo le da el comportamiento al boton Help.
	void MenuScene::HelpButton(cocos2d::Ref *pSender)
	{
		CCLOG("Help");

		auto scene = HelpScene::createScene();

		Director::getInstance()->pushScene(scene);
	}

	/// a selector callback
	void MenuScene::menuCloseCallback(Ref* pSender)
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