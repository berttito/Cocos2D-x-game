#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

Private inheritance here hides part of interface from Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

private:

	// Design Resolution es la resolución "virtual" que tendrán todas las escenas en cualquier dispositivo:

	int designResolutionWidth = 1280;             ///< Ancho virtual de todas las escenas
	int designResolutionHeight = 720;             ///< Alto  virtual de todas las escenas

															   // Assets Resolution es la resolución para la que se prepararon los assets.
															   // En proyectos más elaborados normalmente conviene tener varios juegos de assets preparados para
															   // diversas resoluciones reales para se tengan que escalar menos:

	int assetsResolutionWidth = 1280;
	int assetsResolutionHeight = 720;

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  Called when the application moves to the background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  Called when the application reenters the foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_



