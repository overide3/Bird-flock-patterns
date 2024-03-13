#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Bird
{
private:
	float x;
	float y;
	int vel;
	float dir;
	int VisionR;
	int VisionTheta;
	sf::RectangleShape self;
	int sep;
	std::vector<int> find_birds(std::vector<Bird> list);
public:
	Bird(float x, float y, int velocity, float direction, int visionR, int visionA, int seperation);
	float get_dir();
	float get_x();
	float get_y();
	sf::RectangleShape get_shape();
	void alignment(std::vector<Bird> list);
	void separation(std::vector<Bird> list);
	void cohesion(std::vector<Bird> list);
	void update();
};

