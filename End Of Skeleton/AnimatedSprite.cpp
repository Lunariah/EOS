#include "stdafx.h"
#include "AnimatedSprite.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

AnimatedSprite::AnimatedSprite(const Texture &texture, int collumns, int lines)
	: Sprite(texture)
	, paused{ false }
{
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

AnimatedSprite::AnimatedSprite(int collumns, int lines)
	: Sprite()
	, paused{false}
	, animPlaying{nullptr}
{

}

//AnimatedSprite::AnimatedSprite(const string& texturePath, int collumns, int lines) 
//{
//
//	if (!texture.loadFromFile(texturePath))
//		throw "No file found at location ’" + texturePath + "’";     
//	//setTexture(texture);
//	
//	AnimatedSprite()
//	
//}

void AnimatedSprite::Update()
{
	if (paused) return;

	if (animationClock.getElapsedTime().asSeconds() >= 1.f / animPlaying->speed)
	{
		animationClock.restart();
		
		if (++frame == animPlaying->frames.end())
		{
			if (animPlaying->loop)
				frame = animPlaying->frames.begin();
			else {
				paused = true;
				return;
			}
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
	// Return if anim is currently playing
	if (animPlaying == &animations[name] && animPlaying->loop && !paused)
		return;

	paused = false;

	animPlaying = &animations[name];
	frame = animPlaying->frames.begin();

	if (!smoothTransition) // smoothTransition==true creates animation lag. Deprecating for now
	{
		animationClock.restart();
		setTextureRect(**frame);
	}
}

void AnimatedSprite::FreezeAnim(int frozenFrame)
{
	paused = true;

	if (frozenFrame < animPlaying->frames.size()) 
		setTextureRect(*animPlaying->frames[frozenFrame]);
}

void AnimatedSprite::FreezeAnim()
{
	paused = true;
}
