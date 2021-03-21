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
	AnimatedSprite(std::string textureFile, int collumns, const int lines, float speed);

	void Update(); // To be used right before draw(). See if I can override draw() instead
	void CreateAnim(std::string name, int line, std::vector<int> sequence, bool loop=true);
	void SetSpeed(float newSpeed);
	void SwitchAnim(std::string name, bool smoothTransition);

 private:
	sf::Texture texture;
	std::vector<std::vector<sf::IntRect>> grid;
	std::map<std::string, std::vector<sf::IntRect*>> animations;
	std::vector<sf::IntRect*> animPlaying;
	std::vector<sf::IntRect*>::iterator frame;
	
	float speed;
	sf::Clock animationClock;
};

