/*
	Copyright(c) 2017
	Autor: Alberto Quesada
	Fecha: 5 enero 2017
*/

#pragma once

#ifndef GAME_GAMESCENE_HEADER
#define GAME_GAMESCENE_HEADER


#include "Character.hpp"
#include "cocos2d.h"

/** La clase GameScene.h define las caracteristicas que va a tener la ventana de juego.
*/
namespace game
{
	using cocos2d::Vec2;
	using cocos2d::Layer;
	using cocos2d::Touch;
	using cocos2d::Sprite;
	using cocos2d::Label;	

	class GameScene : public cocos2d::Scene
	{
	private:

		/// Esta enumeraci�n define los posibles estados de la escena
		enum
		{
			WAITING,
			PLAYING,
			GAME_OVER
		}
		state;

		/// Esta es una estructura que se usa como base de otras que necesitan un puntero a Sprite
		/// y un operador de conversi�n autom�tico a puntero a Sprite (operator Sprite *)
		struct SpriteWrapper
		{
			Sprite * sprite;
			operator Sprite * () { return sprite; }
		};

		/// Esta estructura representa una entidad del juego (es b�sicamente un Sprite con informaci�n complementaria)
		struct Entity : SpriteWrapper
		{
			Vec2 speed;
		};

		/// Este typedef facilita que se pueda reemplazar std::vector por cualquier otro contenedor apropiado
		typedef std::vector< Entity > EntityList;

		Layer * layer;
		Character   * playerChar;
		EntityList monsters;
		EntityList plants;
		Sprite * background;
		Sprite   * gameOver;
		Sprite * button;
		Label * scoreLabel;
		
		bool    monsterPassedPlayer;

		int     score;
		int numColisiones;
		static const int maxSimultaneousMonsters = 4;
		static const int monsterAdvanceSpeed = - 250;
		static const int maxSimultaneousPlants = 1;
		static const int plantAdvanceSpeed = - 350;
		bool    touching;
		float   touchY;
		

	public:

		// Esta macro crea la implementaci�n de un m�todo create() predefinido que sirve para
		// crear instancias de esta clase:

		CREATE_FUNC(GameScene);

		/// Este m�todo se encarga de crear la escena de juego
		static cocos2d::Scene* createScene();

		/// Este m�todo se llamar� autom�ticamente para inicializar la escena.
		bool init() override;

		/// Este m�todo se llamar� autom�ticamente cada fotograma.
		void update(float delta) override;

		/// Este es el bot�n de pausa
		void PauseButton(Ref *pSender);

	private:

		/// En este m�todo se crean los sprites y se a�aden a la escena
		void initSprites();

		void initTouch();

		/// Reinicia por completo el estado de la escena (para comenzar el juego).
		void resetGame();

		/// Establece el estado 'game over' cuando un asteroide choca con la nave.
		void setGameOverState();

		void setScore(int parameter);

		/// Este m�todo se usa para reposicionar los sprites que al salirse de la pantalla deben reaparecer
		void correctSpriteLocation(Sprite * sprite);
		
		/// Se actualiza la posici�n de todos los monstruos visibles y, si se salen por un lado de la escena,
		/// se los hace aparecer por el otro extremo:
		void updateMonstersPlants(float delta);		

		/// Se ha implementado esta funci�n para detectar la colosi�n entre las �reas envolventes circulares
		/// de dos sprites porque estas se adaptan mejor a la forma de los asteroides y de los disparos que
		/// las �reas envolventes rectangulares.
		bool checkCircularCollision(const Sprite * monster, const Sprite * sprite);

		/// Esta funci�n se usa para comprobar la colisi�n entre asteroides y la nave.
		/// Si hay una colisi�n se pone el estado del juego en 'game over'.
		void checkMonstersPlantsCharacterCollisions(const EntityList & monsterList, const EntityList & plantList);
		
		/// Funciones para procesar los eventos de inicio, movimiento y fin de toque en la pantalla:
		bool touchBegan(cocos2d::Touch * touch, cocos2d::Event *);
		void touchMoved(cocos2d::Touch * touch, cocos2d::Event *);
		void touchEnded(cocos2d::Touch * touch, cocos2d::Event *);

	};

}

#endif