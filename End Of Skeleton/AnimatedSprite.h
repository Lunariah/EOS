#pragma once
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
	AnimatedSprite(const std::string &texturePath, int collumns, const int lines);

	void Update(); // To be used right before draw()
	void CreateAnim(const std::string &name, int line, const std::vector<int> &sequence, bool loop=true, float speed=4);
	void SwitchAnim(const std::string &name, bool smoothTransition);

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
		 {}
	 };
	std::map<std::string, Animation> animations; // map calls default constructor
	Animation* animPlaying;
	sf::Texture texture;
	std::vector<std::vector<sf::IntRect>> grid;
	std::vector<sf::IntRect*>::iterator frame;
	sf::Clock animationClock;
};
