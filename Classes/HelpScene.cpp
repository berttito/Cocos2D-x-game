/*
Copyright (c) 2017..
Autor: Alberto Quesada
Fecha: 5 febrero 2017
*/

#pragma once

#include "HelpScene.hpp"
#include "GameScene.h"

USING_NS_CC;


/** La clase HelpScene.cpp implementa las caracteristicas que va a tener el menu de pausa del juego.
*/
namespace game {

	Scene* HelpScene::createScene()
	{
		// 'scene' is an autorelease object
		auto scene = Scene::create();

		// 'layer' is an autorelease object
		auto layer = HelpScene::create();

		// add layer as a child to scene
		scene->addChild(layer);

		// return the scene
		return scene;
	}

	// on "init" you need to initialize your instance
	bool HelpScene::init()
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

		// Creamos el boton goBack:

		buttonGoBack = Sprite::create();
		buttonGoBack->setPosition(Point((visibleSize.width / 3) + origin.x, (visibleSize.height / 3) + origin.y));
		this->addChild(buttonGoBack, 0);

		// Le asignamos los sprites y la funcion que tiene cada boton y los colocamos en pantalla: 

		auto menu_item_1 = MenuItemImage::create("buttonGoBack.png", "buttonGoBack2.png", CC_CALLBACK_1(HelpScene::GoBackButton, this));		

		menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4.5f) * 1));		

		// Creamos el menu:

		auto *menu = Menu::create(menu_item_1, NULL);
		menu->setPosition(Point(0, 0));
		this->addChild(menu);
		return true;

		__String * info = __String::createWithFormat("¡Trata de evitar que los monstruos invadan tu casa comiendotelos! Mueve a tu planta de arriba a abajo para conseguirlo");
		infoLabel = Label::createWithTTF(info->getCString(), "fonts/Marker Felt.ttf", visibleSize.height);
		infoLabel->setColor(Color3B::WHITE);
		infoLabel->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2) * 1));
		this->addChild(infoLabel, 1);
	}	

	/// En este metodo le da el comportamiento al boton goBack.
	void HelpScene::GoBackButton(cocos2d::Ref *pSender)
	{
		CCLOG("GoBack");

		Director::getInstance()->popScene();
	}

	/// a selector callback
	void HelpScene::menuCloseCallback(Ref* pSender)
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