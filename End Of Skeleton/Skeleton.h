#pragma once
#include "AnimatedSprite.h"

class Skeleton : public AnimatedSprite
{
 public:
	Skeleton(const std::string &textureFile, const int collumns, const int lines);
	~Skeleton();

	//void Update();

	void MoveUp(const int squares);
	void MoveDown(const int squares);
	void MoveRight(const int squares);
	void MoveLeft(const int squares);

 private:
	
};

