#pragma once



class CollisionManager

{
public:
	static CollisionManager * getInstance();
	bool Check = false;
	void update();
	

private:
	CollisionManager() {}

	static CollisionManager * _instance;

};