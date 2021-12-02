#include "GameOverScene.h"
#include <iostream>
#include <string>  

USING_NS_CC;

Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return GameOver::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool GameOver::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto dirs = Director::getInstance();
	Size visibleSize = dirs->getVisibleSize();
	auto label1 = Label::createWithSystemFont("GAME OVER", "Arial", 108);
	label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(label1);
	return(true);
}