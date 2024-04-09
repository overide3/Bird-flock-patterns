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
		float psi = get_angle(list[i]);
		float x_diff = x - list[i].get_x();
		float y_diff = y - list[i].get_y();
		float dist = sqrt(pow(x_diff, 2) + pow(y_diff, 2));
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

float Bird::get_angle(Bird other)
{
	float x_diff = x - other.get_x();
	float y_diff = y - other.get_y();
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
	return psi;
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
	return dir;
}

float Bird::get_x()
{
	return x;
}

float Bird::get_y()
{
	return y;
}

sf::RectangleShape Bird::get_shape()
{
	return self;
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

bool Bird::separation(std::vector<Bird> list)
{
	bool check = false;
	float angle = dir;
	for (int i = 0; i < indexes.size(); i++)
	{
		float distance = sqrt(pow(list[indexes[i]].get_x() - x, 2) + pow(list[indexes[i]].get_y() - y, 2));
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
			check = true;
		}
	}
	if (angle < 0)
	{
		angle = 360 + angle;
	}
	else if (angle > 360)
	{
		angle = 0 + (angle - 360);
	}
	dir = angle;

	return check;
}

void Bird::cohesion(std::vector<Bird> list)
{
	float angle = dir;
	int max_i = 0;
	float max_d = 0;
	for (int i = 0; i > indexes.size(); i++)
	{
		float distance = sqrt(pow(list[indexes[i]].get_x() - x, 2) + pow(list[indexes[i]].get_y() - y, 2));
		if (distance >= max_d)
		{
			max_i = i;
			max_d = distance;
		}
	}
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

	if (list[indexes[max_i]].get_dir() > hbound or list[indexes[max_i]].get_dir() < lbound)
	{
		angle += 20;
	}
	else
	{
		angle -= 20;
	}
	if (angle < 0)
	{
		angle = 360 + angle;
	}
	else if (angle > 360)
	{
		angle = 0 + (angle - 360);
	}
	dir = angle;
}

void Bird::update(int ww, int wh)
{
	float n_x = cos(dir)*vel;
	float n_y = sin(dir)*vel;

	x += n_x;
	y += n_y;

	if (x > ww)
	{
		x = ww - (x - ww);

	}
	if (x < 0)
	{
		x = 0 - x;

	}
	if (y > wh)
	{
		y = wh - (y - wh);
	}
	if (y < 0)
	{
		y = 0 - y;
	}
	dir = atan(x / y);
}
