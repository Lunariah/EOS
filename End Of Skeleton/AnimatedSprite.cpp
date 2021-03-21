#include "stdafx.h"
#include "AnimatedSprite.h"
#include <vector>

using namespace std;
using namespace sf;

AnimatedSprite::AnimatedSprite(string textureFile, const int collumns, const int lines, float speed)
	: Sprite()
	, speed {speed}
{
	if (!texture.loadFromFile(textureFile))
		throw "No file found at location ’" + textureFile + "’";     
	setTexture(texture);
	
	int spriteWidth = texture.getSize().x / collumns;
	int spriteHeight = texture.getSize().y / lines;

	grid = vector<vector<IntRect>>(collumns, vector<IntRect>(lines, IntRect()));
	for (int x = 0; x < collumns; x++)
	{
		for (int y = 0; y < lines; y++)
		{
			grid[x][y] = IntRect((x * spriteWidth), (y * spriteHeight), spriteWidth, spriteHeight);
		}
	}
}

void AnimatedSprite::Update()
{
	if (animationClock.getElapsedTime().asSeconds() >= 1.f / speed)
	{
		animationClock.restart();
		
		if (++frame == animPlaying.end())
		{
			frame = animPlaying.begin();
		}
		setTextureRect(**frame);
	}
}

void AnimatedSprite::CreateAnim(string name, int line, vector<int> sequence, bool loop)
{
	vector<IntRect*> newAnim;

	for (int pos : sequence)
	{
		newAnim.push_back(&grid[pos][line]);
	}

	//animations.insert(pair<string, vector<IntRect*>> (name, newAnim));
	//animations.emplace(name, newAnim);
	animations[name] = newAnim; // Replaces value if key already exists
}

void AnimatedSprite::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

void AnimatedSprite::SwitchAnim(string name, bool smoothTransition)
{
	animPlaying = animations[name];
	frame = animPlaying.begin();

	if (!smoothTransition)
	{
		animationClock.restart();
		setTextureRect(**frame);
	}
}
