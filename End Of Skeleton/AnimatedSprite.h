#pragma once
#include <unordered_map>

class AnimatedSprite : public sf::Sprite
{
 public:
	/// <summary>
	/// Converts a spritesheet into a sprite that can then be animated
	/// </summary>
	/// <param name="textureFile">Path</param>
	/// <param name="collumns">Nb of collumns in the spritesheet</param>
	/// <param name="lines">Nb of lines in the spritesheet</param>
	/// <param name="speed">Frames per second</param>
	//AnimatedSprite(const std::string &texturePath, int collumns, int lines);
	AnimatedSprite(const sf::Texture &texture, int collumns, int lines);
	AnimatedSprite(int collumns, int lines);

	//void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Update(); // To be used right before draw() // override draw() instead
	void CreateAnim(const std::string &name, int line, const std::vector<int> &sequence, bool loop=true, float speed=4);
	void CreateStill(const std::string &name, int collumn, int line);
	void SwitchAnim(const std::string &name, bool smoothTransition=false);
	void FreezeAnim(int frame);
	void FreezeAnim();

	bool paused;

 protected:
	 class Animation
	 {
		 public:
		 float speed;
		 bool loop;
		 std::vector<sf::IntRect*> frames;
		 Animation(float speed, bool loop)
			 : speed {speed}, loop {loop}, frames {std::vector<sf::IntRect*>()}
		 {}
		 Animation()
			 : speed {0}, loop {false}, frames {std::vector<sf::IntRect*>()}
		 {} // map calls default constructor
	 };
	std::unordered_map<std::string, Animation> animations;
	std::string currentAnimKey;
	//sf::Texture texture;
	std::vector<std::vector<sf::IntRect>> grid;
	std::vector<sf::IntRect*>::iterator frame;
	sf::Clock animationClock;
};

