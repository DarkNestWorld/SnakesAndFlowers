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

	//�������� �������� �� ���������� ����� ��� ������� ������, ��������� � ����� ����
	bool HelloWorld::FreeSpace(std::vector<Vector<Sprite*>> SnakesSprites, Vector <Sprite*> SeedSprites, int x, int y);
	//������� ������
	void HelloWorld::FlowerSpawn(Vector <Sprite*>& SeedSprites, int x, int y);
	//��������� ����
	void HelloWorld::SnakeSpawn(std::vector<Vector<Sprite*>>& SnakesSprites, Vector <Sprite*> SeedSprites);
	//���� ����
	void HelloWorld::SnakeGrow(std::vector<Vector<Sprite*>>& SnakesSprites, Vector <Sprite*> SeedSprites, int SnakeNumber);
	//�������� �������� �� ���������� ����� �� ���� (�� �� ������) - ��� ����������� ����
	bool HelloWorld::NotSoFreeSpace(std::vector<Vector<Sprite*>> SnakesSprites, Vector <Sprite*> SeedSprites, int x, int y);
	//����������� ����
	void HelloWorld::SnakeMove(std::vector<Vector<Sprite*>>& SnakesSprites, Vector <Sprite*>& SeedSprites, int SnakeNumber, float MoveTime);
	//�������� �������� ���� ��� �������� ������. ��� �� �������� �� ��������
	void HelloWorld::DoubleSpeed();
	//������� � ������� ��������
	void HelloWorld::NormalSpeed(int Time);
	//�������� �������� �� ������ ����� ������� �� ����
	int HelloWorld::SnakeClick(std::vector<Vector<Sprite*>> SnakesSprites, int x, int y);
	//������ ��� ����������� ����
	void TimerOne(int Time);
	//������ ��� ����� ���� � ��������� ����� �� �������
	void TimerThree(int Time);
	//������ ��������� ����
	void TimerSnakeSpawn(int Time);
	//������ ��������� ��������� ����
	void TimerTen(int Time);
	//������ ���� ������
	Vector <Sprite*> SeedSprites;
	//������ ����. ������ ���� - ������ ���������� ���� ��������
	std::vector<Vector<Sprite*> > SnakesSprites;
	//����� ������� �����
	Label* CoinsLabel = Label::createWithSystemFont("Coins: 150", "Arial", 24);
	//�����������
	Label* HelloLabel = Label::createWithSystemFont("To start the game - plant a flower \nin any place of screen by right-clicking \nTo figth snakes - left-clicking it", "Arial", 32);
};

#endif // __HELLOWORLD_SCENE_H__
