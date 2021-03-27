#include "stdafx.h"
#include "AnimatedSprite.h"
#include <vector>

using namespace std;
using namespace sf;

AnimatedSprite::AnimatedSprite(const string& texturePath, const int collumns, const int lines) 
	: Sprite()
{
	if (!texture.loadFromFile(texturePath))
		throw "No file found at location ’" + texturePath + "’";     
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
	if (animationClock.getElapsedTime().asSeconds() >= 1.f / animPlaying->speed)
	{
		animationClock.restart();
		
		if (++frame == animPlaying->frames.end())
		{
			frame = animPlaying->frames.begin();
		}
		setTextureRect(**frame);
	}
}

void AnimatedSprite::CreateAnim(const string& name, int line, const vector<int>& sequence, bool loop, float speed)
{
	Animation newAnim(speed, loop);

	for (int pos : sequence)
	{
		newAnim.frames.push_back(&grid[pos][line]);
	}

	//animations.insert(pair<string, vector<IntRect*>> (name, newAnim));
	//animations.emplace(name, newAnim);
	animations[name] = newAnim; // Replaces value if key already exists
}

void AnimatedSprite::SwitchAnim(const string& name, bool smoothTransition)
{
	animPlaying = &animations[name];
	frame = animPlaying->frames.begin();

	if (!smoothTransition)
	{
		animationClock.restart();
		setTextureRect(**frame);
	}
}
