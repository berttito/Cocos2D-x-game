/*
Copyright(c) 2017
Autor: Alberto Quesada
Fecha: 5 enero 2017
*/

#pragma once

#include <ctime>
#include <cstdlib>
#include "GameScene.h"
#include "MenuScene.hpp"
#define SCORE_FONT_SIZE 0.1

/** La clase GameScene.cpp implementa las caracteristicas que va a tener la ventana de juego.
*/
using namespace cocos2d;

namespace game
{
	Scene* GameScene::createScene()
	{
		// 'scene' is an autorelease object
		auto scene = Scene::create();

		// 'layer' is an autorelease object
		auto layer = GameScene::create();

		// add layer as a child to scene
		scene->addChild(layer);

		// return the scene
		return scene;
	}

	bool GameScene::init()
	{
		// Se intenta inicializar la clase base y, si falla, se retorna con error:

		if (!Scene::init())
		{
			return false;
		}

		// Se crea una capa y se añade a la escena:

		layer = Layer::create();

		this->addChild(layer);

		// Se inicializan diversos aspectos de la escena:

		initSprites();
		initTouch();

		resetGame();

		// Inicializamos los elementos de la escena con su estado por defecto:		
		// Se activa la invocación automática del método update():

		scheduleUpdate();

		return true;
	}

	void GameScene::initSprites()
	{
		auto origin = Director::getInstance()->getVisibleOrigin();
		auto winSize = Director::getInstance()->getVisibleSize();

		//Creamos el escenario:

		background = Sprite::create("background.jpg");
		background->setAnchorPoint(Vec2::ZERO);
		background->setPosition(0, 0);
		layer->addChild(background);

		// Se crean los monsters grandes:

		monsters.resize(maxSimultaneousMonsters);

		for (auto & monster : monsters)
		{
			monster.sprite = Sprite::create("monster.png");

			layer->addChild(monster, 1);			
		}

		// Se crean los monsters grandes:

		plants.resize(maxSimultaneousPlants);

		for (auto & plant : plants)
		{
			plant.sprite = Sprite::create("fruit.png");

			layer->addChild(plant, 2);
		}

		// Se crea el sprite del usuario:

		playerChar = Character::create();
		playerChar->setPosition(Vec2(winSize.width * 0.1, winSize.height * 0.5));
		layer->addChild(playerChar, 1);

		// Se crea el sprite con el mensaje de game over:

		gameOver = Sprite::create("game-over.png");

		gameOver->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

		layer->addChild(gameOver, 2);

		//Boton pausa:

		button = Sprite::create();
		button->setPosition(Point((winSize.width / 15) + origin.x, (winSize.height / 1.07f) + origin.y));
		this->addChild(button, 0);

		auto menu_item_1 = MenuItemImage::create("button.png", "button2.png", CC_CALLBACK_1(GameScene::PauseButton, this));

		menu_item_1->setPosition(Point(winSize.width / 15, (winSize.height / 1.07f) * 1));

		auto *menu = Menu::create(menu_item_1, NULL);
		menu->setPosition(Point(0, 0));
		this->addChild(menu);

		__String * tempScore = __String::createWithFormat("Score: %i", score);
		scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", winSize.height * SCORE_FONT_SIZE);
		scoreLabel->setColor(Color3B::WHITE);
		scoreLabel->setPosition(Point(winSize.width / 5, (winSize.height / 1.07f) * 1));
		this->addChild(scoreLabel, 1);

	}

	void GameScene::PauseButton(cocos2d::Ref *pSender)
	{
		CCLOG("Pause Button");

		state = WAITING;

		auto scene = MenuScene::createScene();

		Director::getInstance()->pushScene(scene);
	}

	void GameScene::initTouch()
	{
		// Se registran los eventos de la pantalla táctil:

		auto touchListener = EventListenerTouchOneByOne::create();

		touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::touchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::touchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::touchEnded, this);

		layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, layer);
	}

	void GameScene::setGameOverState()
	{
		gameOver->setVisible(true);

		state = GAME_OVER;
	}

	void GameScene::setScore(int parameter)
	{
		auto winSize = Director::getInstance()->getVisibleSize();

		if (scoreLabel != nullptr)
		{
			this->removeChild(scoreLabel, 1);
		}

		score += parameter;

		__String * tempScore = __String::createWithFormat("Score: %i", score);
		scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", winSize.height * SCORE_FONT_SIZE);
		scoreLabel->setColor(Color3B::WHITE);
		scoreLabel->setPosition(Point(winSize.width / 5, (winSize.height / 1.07f) * 1));
		this->addChild(scoreLabel, 1);
	}

	void GameScene::correctSpriteLocation(cocos2d::Sprite * sprite)
	{
		// Se toman las dimensiones del sprite:
		// (Nota: aquí hay algo que no acaba de cuadrar cuando la nave está rotada en ciertos ángulos)

		float leftX = sprite->getBoundingBox().getMinX();
		float rightX = sprite->getBoundingBox().getMaxX();
		float topY = sprite->getBoundingBox().getMaxY();
		float bottomY = sprite->getBoundingBox().getMinY();
		Size  sceneSize = Director::getInstance()->getVisibleSize();
		Size  spriteSize = sprite->getContentSize();

		// Se comprueba si el sprite se sale de la escena por algún lado y, de ser así, se recoloca
		// en el lado opuesto. Sólo se modifica la coordenada X o Y dejando la otra intacta:

		if (rightX < 0.f)                   // La nave se sale completamente por el lado izquierdo de la escena
		{
			sprite->setPosition(Vec2((rand() % (int)(sceneSize.width) + sceneSize.width), (rand() % (int)(sceneSize.height - 80) + 40)));

		}
	}

	void GameScene::update(float delta)
	{
		if (state == PLAYING)
		{
			if (touching)
			{
				playerChar->moveTowards(touchY, delta);
			}

			updateMonstersPlants(delta);
			checkMonstersPlantsCharacterCollisions(monsters, plants);
		}

	}

	void GameScene::updateMonstersPlants(float delta)
	{
		// Se actualiza la posición de todos los monstruos visibles y, si se salen por un lado de la escena,
		// se los hace aparecer por el otro extremo:

		for (auto & monster : monsters)
		{
			if (monster.sprite->isVisible())
			{
				monster.sprite->setPosition(monster.sprite->getPosition() + monster.speed * delta);

				correctSpriteLocation(monster.sprite);
			}
		}

		for (auto & plant : plants)
		{
			if (plant.sprite->isVisible())
			{
				plant.sprite->setPosition(plant.sprite->getPosition() + plant.speed * delta);

				correctSpriteLocation(plant.sprite);
			}
		}
	}

	bool GameScene::checkCircularCollision(const Sprite * a, const Sprite * b)
	{
		// Sólo se comprueba la colisión si ambos sprites están visibles:

		if (a->isVisible() && b->isVisible())
		{
			// Se calcula el radio de cada sprite tomando el mínimo de la mitad del ancho y del alto.
			// Luego se calcula la distancia que separa sus centros:

			Size   aSize = a->getContentSize();
			Size   bSize = b->getContentSize();
			float  aRadius = MIN(aSize.width, aSize.height) / 2.f;
			float  bRadius = MIN(bSize.width, bSize.height) / 2.f;
			float  separation = (a->getPosition() - b->getPosition()).length();

			// Dos círculos se solapan si la distancia que separa sus centros es menor que la suma de sus radios:

			return separation < aRadius + bRadius;
		}

		return false;
	}


	void GameScene::checkMonstersPlantsCharacterCollisions(const EntityList & monsterList, const EntityList & plantList)
	{

		for (auto & monster : monsterList)
		{
			auto winSize = Director::getInstance()->getVisibleSize();

			if (checkCircularCollision(monster.sprite, playerChar) == true)
			{
				// Se establece el estado 'game over':

				monster.sprite->setVisible(false);
				numColisiones++;

				if (numColisiones % 4 == 0) {

					monsters.resize(maxSimultaneousMonsters);

					for (auto & monster : monsters)
					{
						monster.sprite = Sprite::create("monster.png");

						monster.sprite->setPosition(Vec2((rand() % (int)(winSize.width) + winSize.width), (rand() % (int)(winSize.height - 80) + 40)));

						layer->addChild(monster, 2);
					}
				}

				/*if (score % 10 == 0)
				{
				maxSimultaneousPlants++;

				plants.resize(maxSimultaneousPlants);

				for (auto & plant : plants)
				{
				plant.sprite = Sprite::create("fruit.png");

				layer->addChild(plant, 2);
				}
				}*/

				setScore(1);

				// No hay nada más que comprobar:

				break;
			}
		}

		for (auto & plant : plantList)
		{
			if (checkCircularCollision(plant.sprite, playerChar) == true)
			{
				// Se establece el estado 'game over':

				setGameOverState();

				// No hay nada más que comprobar:

				break;
			}
		}
	}

	void GameScene::resetGame()
	{
		// Se toma el tamaño visible del display para colocar los elementos gráficos
		// usando posiciones relativas (en lugar de absolutas):

		Size winSize = Director::getInstance()->getVisibleSize();

		// Se coloca al personaje en la escena:

		playerChar->setPosition(Vec2(winSize.width * 0.1, winSize.height * 0.5));

		// Se colocan los monstruos en posiciones aleatorias asegurándose que de no empiecen
		// solapándose con la planta:

		for (auto & monster : monsters)
		{
			// El proceso de ubicar cada monstruo aleatoriamente se repite hasta que se encuentre
			// una posición válida:

			while (true)
			{
				// Se establece una posición aleatoria que quede dentro de la escena:

				monster.sprite->setPosition(Vec2((rand() % (int)(winSize.width) + winSize.width), rand() % (int)winSize.height));

				// Se comprueba que si hay solapamiento con la planta:

				if (monster.sprite->getBoundingBox().intersectsRect(playerChar->getBoundingBox()) == false)
				{
					// Si la posición es válida se establece una velocidad para que el monstruo
					// empiece acercandose de la planta y se sale del bucle while:

					Vec2 direction = Vec2(1, 0);

					monster.speed = direction.getNormalized() * monsterAdvanceSpeed;

					break;
				}

				monster.sprite->setVisible(true);
			}

			for (auto & plant : plants)
			{
				// El proceso de ubicar cada monstruo aleatoriamente se repite hasta que se encuentre
				// una posición válida:

				while (true)
				{
					// Se establece una posición aleatoria que quede dentro de la escena:

					plant.sprite->setPosition(Vec2((rand() % (int)(winSize.width) + winSize.width), rand() % (int)winSize.height));

					// Se comprueba que si hay solapamiento con la planta:

					if (plant.sprite->getBoundingBox().intersectsRect(playerChar->getBoundingBox()) == false)
					{
						// Si la posición es válida se establece una velocidad para que el monstruo
						// empiece acercandose de la planta y se sale del bucle while:

						Vec2 direction = Vec2(1, 0);

						plant.speed = direction.getNormalized() * plantAdvanceSpeed;

						break;
					}

					monster.sprite->setVisible(true);
				}

				gameOver->setVisible(false);

				// Se resetean las variables que controlan la interacción con el usuario:
				state = PLAYING;
			}
		}
	}

	bool GameScene::touchBegan(cocos2d::Touch * touch, cocos2d::Event *)
	{
		switch (state)
		{
		case WAITING:
		{
			state = PLAYING;
			break;
		}

		case PLAYING:
		{
			touching = true;
			touchY = touch->getLocation().y;
			break;
		}
		}

		return true;
	}

	void GameScene::touchMoved(cocos2d::Touch * touch, cocos2d::Event *)
	{
		touchY = touch->getLocation().y;
	}

	void GameScene::touchEnded(cocos2d::Touch * touch, cocos2d::Event *)
	{
		touching = false;
	}

}