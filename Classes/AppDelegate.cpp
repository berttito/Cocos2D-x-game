#include "AppDelegate.h"
#include "IntroScene.hpp"

USING_NS_CC;

#include <vector>
#include <string>

using namespace std;
using namespace cocos2d;

// Esta macro permite determinar si se está compilando para un entorno de escritorio:
#define IS_DESKTOP_COMPUTER (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || \
                            (CC_TARGET_PLATFORM == CC_PLATFORM_MAC  ) || \
                            (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	// Se crea la ventana en la que se mostrarán todas las escenas:
	// En ordenadores de escritorio la ventana tiene un tamaño concreto y en dispositivos móviles
	// ocupa toda (o casi toda) la pantalla.

	auto director = Director::getInstance();
	auto glView = director->getOpenGLView();

	if (!glView)
	{
#if IS_DESKTOP_COMPUTER //AQUI LO PONGO PARA RESOLUCION DE ESCRITORIO
		glView = GLViewImpl::createWithRect("MiJuego", Rect(0, 0, designResolutionWidth, designResolutionHeight));
#else 
		glView = GLViewImpl::create("MiJuego");
#endif

		director->setOpenGLView(glView);
}
	
		// Se establece la subcarpeta en la que se buscarán los recursos.
		// Establecer la subcarpeta apropiada según la resolución del dispositivo se deja pendiente como ejercicio.
		// Revisar esta documentación: http://www.cocos2d-x.org/wiki/Multi_resolution_support

	CCSize frameSize = glView->getFrameSize();//ESTO SIRVE PARA SACAR EL TAMAÑO DE LA PANTALLA DEL MOVIL DONDE ESTE

	vector< string > searchPathList;//CON ESTO LE DIGO LAS CARPETAS DONDE TIENE QUE BUSCAR LOS SPRITES EN FUNCION DEL TAMAÑO DE LA PANTALLA DEL MOVIL

	//AQUI HAGO IFS PARA DIFERENTES RESOLUCIONES Y LE DIGO EN QUE CARPETA TIENE QUE BUSCAR (ESTAS CARPETAS VAN DENTRO DE RESOURCES)
	if (frameSize.height <= 480)
	{
		searchPathList.push_back("480p");
	}

	else if (frameSize.height >= 1080)
	{
		searchPathList.push_back("1080p");
	}

	else
	{
		searchPathList.push_back("720p");
	}


	FileUtils::getInstance()->setSearchPaths(searchPathList);

	// Se establece la resolución de diseño de las escenas:

	glView->setDesignResolutionSize(designResolutionWidth, designResolutionHeight, ResolutionPolicy::NO_BORDER);

	// Se establece cuánto hay que escalar los assets para acaptarse a la resolución de diseño:

	director->setContentScaleFactor(float(assetsResolutionWidth) / designResolutionWidth);

	// Descomentar si se quieren mostrar estadísticas de rendimiento en pantalla:

	// director->setDisplayStats (true);

	// Se inicia la escena principal:

	director->runWithScene(game::IntroScene::createScene());

	return true;


	/*
	// turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    auto fileUtils = FileUtils::getInstance();
    auto screenSize = glView->getFrameSize();
    std::vector<std::string> resDirOrders;
	

	// check which assets the devices requires
	
	if (1080 <= screenSize.width || 1080 <= screenSize.height)
	{
		resDirOrders.push_back("720p");		

		glView->setDesignResolutionSize(1080, 720, ResolutionPolicy::NO_BORDER);
	}
	else if (960 <= screenSize.width || 960 <= screenSize.height)
	{
		resDirOrders.push_back("960p");		

		glView->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
	}
	else
	{
		resDirOrders.push_back("480p");

		glView->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);
	}

	fileUtils->setSearchPaths(resDirOrders);

	// create a scene. it's an autorelease object
	auto scene = game::IntroScene::createScene();

	// run
	director->runWithScene(scene);

	return true;
	*/
	
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
