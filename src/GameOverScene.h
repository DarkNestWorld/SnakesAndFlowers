#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class GameOver : public Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameOver);
};

#endif // __GAME_OVER_SCENE_H__
