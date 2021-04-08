#pragma once
#include "AnimatedSprite.h"

class Skeleton : public AnimatedSprite
{
 public:
	Skeleton(const std::string &textureFile, const int collumns, const int lines);
	~Skeleton();

	void Update(float deltaTime);
	void Reset(sf::Vector2i position);
	void SetGridPosition(sf::Vector2i pos);
	//void SetGridPosition(int x, int y);

	void Wait();
	void MoveUp(const int squares);
	void MoveDown(const int squares);
	void MoveRight(const int squares);
	void MoveLeft(const int squares);

	sf::Vector2f Journey;
 private:
	const float MOVEMENT_SPEED;
	sf::Vector2i gridPos;
};

