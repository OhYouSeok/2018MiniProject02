#pragma once



#include <vector>

#include "Bullet.h"



class BulletManager

{

public:

	static BulletManager * getInstance();

	void PushBackBullet(Bullet * bullet);

	void DeleteBullet(Bullet * bullet);

	std::vector<Bullet*> getBullets() const;
	void draw();

	void update();

	void clean();



private:

	BulletManager() {}

	static BulletManager * _instance;	

	std::vector<Bullet*> _bullets;

};