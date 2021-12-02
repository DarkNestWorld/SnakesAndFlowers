#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include <iostream>
#include <string>     

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
    return HelloWorld::create();

}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

const int CageSize = 40;	//Размер "клетки" для одного цветка или сегмента змеи

int CageHeigth;
int CageWidth;				//Размер экрана в клетках

const int StartMoney = 150; 
const int SeedPrice = 50;	//Денежные константы

int Coins = StartMoney;

float SnakeSpawnInterval = 5.0;
float SnakeSpeed = 1.0;

bool GameNotStartedFlag = true;

bool HelloWorld::init()
{



    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CageHeigth = visibleSize.height / CageSize;	//Высота экрана в клетках
	CageWidth = visibleSize.width / CageSize;	//Ширина




	auto listener = EventListenerMouse::create();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	CoinsLabel->setPosition(70,30);
	this->addChild(CoinsLabel, 1);

	HelloLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(HelloLabel, 1);

	listener->onMouseDown = [&](Event* event)		//Нажатие мыши
	{


		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);


		int k = static_cast<int>(mouseEvent->getMouseButton());
		if ((k == 1) && (Coins >= SeedPrice))							//Правая кнопка мыши - посадка цветка
		{	
			if(FreeSpace(SnakesSprites, SeedSprites, mouseEvent->getCursorX(), mouseEvent->getCursorY()))
			{ 
				FlowerSpawn(SeedSprites, mouseEvent->getCursorX(), mouseEvent->getCursorY());
				Coins -= SeedPrice;
				CoinsLabel->setString("Coins: " + std::to_string(Coins));
				if (GameNotStartedFlag)									//Начало игры, запуск таймеров, убирание приветствия
				{
					GameNotStartedFlag = false;	
					SnakeSpawn(SnakesSprites, SeedSprites);
					scheduleOnce(SEL_SCHEDULE(&HelloWorld::TimerSnakeSpawn), SnakeSpawnInterval);
					schedule(SEL_SCHEDULE(&HelloWorld::TimerTen), 10);
					schedule(SEL_SCHEDULE(&HelloWorld::TimerThree), 3);
					scheduleOnce(SEL_SCHEDULE(&HelloWorld::TimerOne), SnakeSpeed);
					removeChild(HelloLabel);
				}
			}
		}
		if (k == 0)
		{
			int SnakeC = SnakeClick(SnakesSprites, mouseEvent->getCursorX(), mouseEvent->getCursorY());
			if (SnakeC != -1)
			{
				removeChild(SnakesSprites.at(SnakeC).back());
				SnakesSprites.at(SnakeC).popBack();
				if (SnakesSprites.at(SnakeC).empty())
					SnakesSprites.erase(std::next(SnakesSprites.begin(), SnakeC));
			}
		}



	};


	

    return true;
}

bool HelloWorld::FreeSpace(std::vector<Vector<Sprite*>> SnakesSprites, Vector <Sprite*> SeedSprites, int x, int y)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if(((x < 0) || (x > visibleSize.width)) || ((y < 0) || (y > visibleSize.height)))
		return(false);
	int xS;
	int yS;
	int i;
	int j;
	for (i = 0; i < SeedSprites.size(); i++)		//Должно не дать создать цветок или змею поверх другого цветка
	{
		xS = SeedSprites.at(i)->getPositionX();
		yS = SeedSprites.at(i)->getPositionY();		//Промежуточные переменные можно получить под if, но тогда код сложночитабелен 
		if ((abs(x - xS) < CageSize - 10) && (abs(y - yS) < CageSize -10))
			return(false);
	}
	for (i = 0; i < SnakesSprites.size(); i++)		//Должно не дать создать цветок или змею поверх другоой змеи
	{
		for (j = 0; j < SnakesSprites.at(i).size(); j++){
			xS = SnakesSprites.at(i).at(j)->getPositionX();
			yS = SnakesSprites.at(i).at(j)->getPositionY();
			if ((abs(x - xS) < CageSize/2) && (abs(y - yS) < CageSize/2))
				return(false);
		}
	}
	return(true);
}

void HelloWorld::FlowerSpawn(Vector <Sprite*>& SeedSprites, int x, int y)
{
	auto SeedSprite = Sprite::create("678141.png");			//Создание цветка 
	if (SeedSprite == nullptr) { problemLoading("'678141.png'"); }
	int x1 = x / CageSize;									//Смещение сажаемого ростка в центр "клетки". В два этапа для округления
	int x2 = x1 * CageSize + CageSize / 2;
	int y1 = y / CageSize;
	int y2 = y1 * CageSize + CageSize / 2;
	SeedSprite->setPosition(Vec2(x2, y2));
	addChild(SeedSprite);
	SeedSprites.pushBack(SeedSprite);
}

void HelloWorld::SnakeSpawn(std::vector<Vector<Sprite*>>& SnakesSprites, Vector <Sprite*> SeedSprites)
{
	auto SnakeHead = Sprite::create("snake_head.png");						//Создание Змеи 
	if (SnakeHead == nullptr) { problemLoading("'snake_head.png'"); }
	int Sx;
	int Sy;
	do{
		Sx = CageSize * (rand() % (CageWidth - 1) + 1) + CageSize / 2;
		Sy = CageSize * (rand() % (CageHeigth - 1) + 1) + CageSize / 2;					//Случайная позиция 	
	} while (!HelloWorld::FreeSpace(SnakesSprites, SeedSprites, Sx, Sy));	//Проверка свободна ли позиция
	SnakeHead->setPosition(Sx, Sy);	
	addChild(SnakeHead);
	Vector <Sprite*> Snake;
	Snake.pushBack(SnakeHead);
	SnakesSprites.push_back(Snake);
	SnakeGrow(SnakesSprites, SeedSprites, SnakesSprites.size()-1);
}

void HelloWorld::SnakeGrow(std::vector<Vector<Sprite*>>& SnakesSprites, Vector <Sprite*> SeedSprites, int SnakeNumber)
{
	if ((SnakesSprites.at(SnakeNumber).size() < 5) || ((SnakesSprites.at(SnakeNumber).size() < 10) && (SeedSprites.size() >= 2)))	//Проверка длины змейки, если длиннее 5/10 - не растёт
	{
		int PreviousX = SnakesSprites.at(SnakeNumber).back()->getPositionX();
		int PreviousY = SnakesSprites.at(SnakeNumber).back()->getPositionY();
		int NextX = PreviousX;
		int NextY = PreviousY;
		int RandomStart = rand() % 4;
		int RandomNext;
		int i;
		for (i = 0; i < 4; i++)																					//Цикл ищет свободное место под хвост по часовой стрелке, начиная со случайного
		{
			RandomNext = (RandomStart + i) % 4;
			if ((RandomNext == 0) && (FreeSpace(SnakesSprites, SeedSprites, NextX - CageSize, NextY)))			//Слева
			{
				NextX -= CageSize;
				i = 4;
			}
			else
			if ((RandomNext == 1) && (FreeSpace(SnakesSprites, SeedSprites, NextX, NextY + CageSize)))			//Сверху
			{
				NextY += CageSize;
				i = 4;
			}
			else
			if ((RandomNext == 2) && (FreeSpace(SnakesSprites, SeedSprites, NextX + CageSize, NextY)))			//Справа
			{
				NextX += CageSize;
				i = 4;
			}
			else
			if ((RandomNext == 3) && (FreeSpace(SnakesSprites, SeedSprites, NextX, NextY - CageSize)))			//Снизу
			{
				NextY -= CageSize;
				i = 4;
			}																							
		}
		if (i == 5)					//Если i !=5 значит свободного места для хвоста нет
		{ 
			auto SnakeTaill = Sprite::create("snake_part.png");						//Создание змеиного хвоста 
			if (SnakeTaill == nullptr) { problemLoading("'snake_part.png'"); }

			SnakeTaill->setPosition(NextX, NextY);
			addChild(SnakeTaill);
			SnakesSprites.at(SnakeNumber).pushBack(SnakeTaill);
		}
		//else 
			//log("!!!SnakeHasNotPlaceToGrove!!!");
	}
}

bool HelloWorld::NotSoFreeSpace(std::vector<Vector<Sprite*>> SnakesSprites, Vector <Sprite*> SeedSprites, int x, int y)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (((x < 0) || (x > visibleSize.width)) || ((y < 0) || (y > visibleSize.height)))
		return(false);
	int xS;
	int yS;
	int i;
	int j;
	for (i = 0; i < SnakesSprites.size(); i++)		//Должно не дать змее ползти поверх другоой змеи
	{
		for (j = 0; j < SnakesSprites.at(i).size(); j++) {
			xS = SnakesSprites.at(i).at(j)->getPositionX();
			yS = SnakesSprites.at(i).at(j)->getPositionY();
			if ((abs(x - xS) < CageSize - 10) && (abs(y - yS) < CageSize - 10))
				return(false);
		}
	}
	return(true);
}

void HelloWorld::SnakeMove(std::vector<Vector<Sprite*>>& SnakesSprites, Vector <Sprite*>& SeedSprites, int SnakeNumber, float MoveTime)
{
	int PreviousX = SnakesSprites.at(SnakeNumber).at(0)->getPositionX();
	int PreviousY = SnakesSprites.at(SnakeNumber).at(0)->getPositionY();
	int NextX = PreviousX;
	int NextY = PreviousY;
	int RandomStart = rand() % 4;
	int RandomNext;
	int i;
	for (i = 0; i < 4; i++)																					//Цикл ищет свободное место для головы по часовой стрелке, начиная со случайного
	{																										//Четыре напраления, поскольку змее можно убрать всё кроме головы
		RandomNext = (RandomStart + i) % 4;
		if ((RandomNext == 0) && (NotSoFreeSpace(SnakesSprites, SeedSprites, NextX - CageSize, NextY)))			//Слева
		{
			NextX -= CageSize;
			i = 4;
		}
		else
			if ((RandomNext == 1) && (NotSoFreeSpace(SnakesSprites, SeedSprites, NextX, NextY + CageSize)))			//Сверху
			{
				NextY += CageSize;
				i = 4;
			}
			else
				if ((RandomNext == 2) && (NotSoFreeSpace(SnakesSprites, SeedSprites, NextX + CageSize, NextY)))			//Справа
				{
					NextX += CageSize;
					i = 4;
				}
				else
					if ((RandomNext == 3) && (NotSoFreeSpace(SnakesSprites, SeedSprites, NextX, NextY - CageSize)))			//Снизу
					{
						NextY -= CageSize;
						i = 4;
					}
	}
	if (i == 5)					//Если i !=5 значит свободного места для хвоста нет cвободного места
	{
		
		for (int j = SnakesSprites.at(SnakeNumber).size()-1; j > 0; j--)
		{
			int x1 = SnakesSprites.at(SnakeNumber).at(j - 1)->getPositionX() / CageSize;
			int x = x1 * CageSize + CageSize / 2;
			int y1 = SnakesSprites.at(SnakeNumber).at(j - 1)->getPositionY() / CageSize;
			int y = y1 * CageSize + CageSize / 2;
			auto Move = MoveTo::create(MoveTime, Vec2(x, y));
			SnakesSprites.at(SnakeNumber).at(j)->runAction(Move);
		}
		
		int x1 = NextX / CageSize;
		int x = x1 * CageSize + CageSize / 2;
		int y1 = NextY / CageSize;
		int y = y1 * CageSize + CageSize / 2;
		auto Move = MoveTo::create(MoveTime, Vec2(x, y));
		SnakesSprites.at(SnakeNumber).at(0)->runAction(Move);

		for (int j = 0; j < SeedSprites.size(); j++)		//Проверка на контакт с цветком
		{
			int xS = SeedSprites.at(j)->getPositionX();
			int yS = SeedSprites.at(j)->getPositionY();
			if ((abs(NextX - xS) < CageSize/2) && (abs(NextY - yS) < CageSize/2))	//Змея ест цветок с меньшего растояния, чем избегает других змей
			{
				removeChild(SeedSprites.at(j));
				SeedSprites.erase(j);
				DoubleSpeed();
				j = SeedSprites.size(); //Потому что не может быть двух цветков на одном месте
			}
		}
	}
	//else
		//log("!!!SnakeHasNotPlaceToMove!!!");

}

int HelloWorld::SnakeClick(std::vector<Vector<Sprite*>> SnakesSprites, int x, int y)
{

	int xS;
	int yS;
	for (int i = 0; i < SnakesSprites.size(); i++)		//Проверка клика по змее
	{
		for (int j = 0; j < SnakesSprites.at(i).size(); j++) {
			xS = SnakesSprites.at(i).at(j)->getPositionX();
			yS = SnakesSprites.at(i).at(j)->getPositionY();
			if ((abs(x - xS) < CageSize) && (abs(y - yS) < CageSize))
				return(i);
		}
	}
	return(-1);
}

void HelloWorld::TimerOne(int Time)
{
	//log("OneSecundTimer");
	for (int i = 0; i < SnakesSprites.size(); i++)
		SnakeMove(SnakesSprites, SeedSprites, i, SnakeSpeed);
	scheduleOnce(SEL_SCHEDULE(&HelloWorld::TimerOne), SnakeSpeed);

}

void HelloWorld::TimerThree(int Time)
{
	//log("ThreeSecundTimer");
	Coins += 5 * SeedSprites.size();
	CoinsLabel->setString("Coins: " + std::to_string(Coins));
	for(int i = 0; i < SnakesSprites.size(); i++)
		SnakeGrow(SnakesSprites, SeedSprites, i);
}

void HelloWorld::TimerSnakeSpawn(int Time)
{
	//log("SnakeSpawnSecundTimer");
	SnakeSpawn(SnakesSprites, SeedSprites);
	scheduleOnce(SEL_SCHEDULE(&HelloWorld::TimerSnakeSpawn), SnakeSpawnInterval);
}

void HelloWorld::TimerTen(int Time)
{
	//log("TenSecundTimer");
	SnakeSpawnInterval = SnakeSpawnInterval * 1.05;//0.95	//Согласно условию каждые 10 секунд скорость появление новых змеек уменьшается на 5%.
}

void HelloWorld::DoubleSpeed()
{
	if (SnakeSpeed == 1.0)
	{
		SnakeSpeed = 0.5;
		scheduleOnce(SEL_SCHEDULE(&HelloWorld::NormalSpeed), 5);
	}

	if ((SeedSprites.size() == 0) && (Coins < SeedPrice))	//Проверка проиграна ли ирга (нет цветков и денег на новые)
	{
		auto GameOverScene = GameOver::createScene();
	
		Director::getInstance()->replaceScene(GameOverScene);
	}

}

void HelloWorld::NormalSpeed(int Time)
{
		SnakeSpeed = 1.0;
}