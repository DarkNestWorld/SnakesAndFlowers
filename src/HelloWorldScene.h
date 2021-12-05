#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;


class HelloWorld : public Scene
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	//Проверка свободны ли окресности точки для высадки цветов, появления и роста змей
	bool HelloWorld::FreeSpace(std::vector<Vector<Sprite*>> SnakesSprites, Vector <Sprite*> SeedSprites, int x, int y);
	//Посадка цветка
	void HelloWorld::FlowerSpawn(Vector <Sprite*>& SeedSprites, int x, int y);
	//Появление змеи
	void HelloWorld::SnakeSpawn(std::vector<Vector<Sprite*>>& SnakesSprites, Vector <Sprite*> SeedSprites);
	//Рост змеи
	void HelloWorld::SnakeGrow(std::vector<Vector<Sprite*>>& SnakesSprites, Vector <Sprite*> SeedSprites, int SnakeNumber);
	//Проверка свободны ли окресности точки от змей (но не цветов) - для перемещения змей
	bool HelloWorld::NotSoFreeSpace(std::vector<Vector<Sprite*>> SnakesSprites, Vector <Sprite*> SeedSprites, int x, int y);
	//Перемещение змей
	void HelloWorld::SnakeMove(std::vector<Vector<Sprite*>>& SnakesSprites, Vector <Sprite*>& SeedSprites, int SnakeNumber, float MoveTime);
	//Удвоение скорости змей при поедании цветка. Так же проверка на проигрыш
	void HelloWorld::DoubleSpeed();
	//Возврат к обычной скорости
	void HelloWorld::NormalSpeed(int Time);
	//Проверка прищёлся ли щелчёк левой кнопкой на змею
	int HelloWorld::SnakeClick(std::vector<Vector<Sprite*>> SnakesSprites, int x, int y);
	//Таймер для перемещения змей
	void TimerOne(int Time);
	//Таймер для роста змей и получения денег от цветков
	void TimerThree(int Time);
	//Таймер появления змей
	void TimerSnakeSpawn(int Time);
	//Таймер ускорения появления змей
	void TimerTen(int Time);
	//Вектор всех цветов
	Vector <Sprite*> SeedSprites;
	//Вектор змей. Каждая змея - вектор содержащий свои сегменты
	std::vector<Vector<Sprite*> > SnakesSprites;
	//Вывод текущих деньг
	Label* CoinsLabel = Label::createWithSystemFont("Coins: 150", "Arial", 24);
	//Приветствие
	Label* HelloLabel = Label::createWithSystemFont("To start the game - plant a flower \nin any place of screen by right-clicking \nTo figth snakes - left-clicking it", "Arial", 32);
};

#endif // __HELLOWORLD_SCENE_H__
