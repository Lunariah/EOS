#pragma once
#include "AnimatedSprite.h"

class Skeleton
{
 public:
	Skeleton(const std::string &textureFile, const int collumns, const int lines);
	//Skeleton(const sf::Texture &texture, const int collumns, const int lines);
	Skeleton(const int collumns, const int lines);
	~Skeleton();


	AnimatedSprite Update(float deltaTime);
	void Reset(sf::Vector2i position);
	void WarpTo(sf::Vector2i pos);
	//void SetGridPosition(int x, int y);

	void Wait();
	void MoveUp(const int squares=1); // Using arguments is deprecated
	void MoveDown(const int squares=1);
	void MoveRight(const int squares=1);
	void MoveLeft(const int squares=1);

	sf::Vector2f Journey;
	sf::Vector2i gridPos;

 private:
	sf::Texture texture;
	AnimatedSprite sprite;
};

