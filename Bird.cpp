#include "Bird.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
using namespace std;

void Bird::find_birds(std::vector<Bird> list)
{
	vector<int> indexs;
	for (int i = 0; i < list.size(); i++)
	{
		float x_diff = x - list[i].get_x();
		float y_diff = y - list[i].get_y();
		float dist = sqrt(pow(x_diff, 2) + pow(y_diff, 2));
		float psi = 0.0f;
		if (x_diff > 0)
		{
			if (y_diff > 0)
			{
				psi = atan((x_diff / y_diff));
			}
			else
			{
				psi = atan((x_diff / (-y_diff)));
				psi += 270;
			}

		}
		else
		{
			if (y_diff > 0)
			{
				psi = atan(((-x_diff) / y_diff));
				psi += 90;
			}
			else
			{
				psi = atan(((-x_diff) / (-y_diff)));
				psi += 180;
			}
		}
		if ((dist > VisionR))
		{
			float lbound = dir - VisionTheta;
			if (lbound < 0)
			{
				lbound = 360 - lbound;
			}
			float ubound = dir + VisionTheta;
			if (ubound > 360)
			{
				ubound = 0 + (ubound - 360);
			}
			if (psi < ubound and psi > lbound)
			{
				indexs.push_back(i);
			}
		}
	}
	indexes = indexs;
}

Bird::Bird(float pos_x, float pos_y, int velocity, float direction, int visionR, int visionA, int seperation)
{
	x = pos_x;
	y = pos_y;
	vel = velocity;
	dir = direction;
	VisionR = visionR;
	VisionTheta = visionA;
	sep = seperation;
	self.setSize(sf::Vector2f(5, 5));
	self.setFillColor(sf::Color::Cyan);
	self.setPosition(x, y);
}

float Bird::get_dir()
{
	return 0.0f;
}

float Bird::get_x()
{
	return 0.0f;
}

float Bird::get_y()
{
	return 0.0f;
}

sf::RectangleShape Bird::get_shape()
{
	return sf::RectangleShape();
}

void Bird::alignment(std::vector<Bird> list)
{
	float angle = 0;
	for (int i = 0; i < indexes.size(); i++)
	{
		angle += list[indexes[i]].get_dir();
	}
	angle = angle / indexes.size();
	dir = angle;
}

void Bird::separation(std::vector<Bird> list)
{
	float angle = dir;
	for (int i = 0; i < indexes.size(); i++)
	{
		float distance = sqrt(pow(list[indexes[i]].get_x(), 2) + pow(list[indexes[i]].get_y(), 2));
		if (distance < sep)
		{
			float lbound = angle + 180;
			if (lbound > 360)
			{
				lbound = 0 + (lbound - 360);
			}
			float hbound = angle - 180;
			if (hbound < 0)
			{
				hbound = 360 + hbound;
			}

			if (list[indexes[i]].get_dir() > hbound or list[indexes[i]].get_dir() < lbound)
			{
				angle -= 20;
			}
			else
			{
				angle += 20;
			}
		}
	}
	dir = angle;
}

void Bird::cohesion(std::vector<Bird> list)
{
}

void Bird::update()
{
}
