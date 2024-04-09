#include <SFML/Graphics.hpp>
#include <vector>
#include "bird.h"


int main()
{
	int WWidth = 1080;
	int WHeight = 1920;
	sf::RenderWindow window(sf::VideoMode(WHeight, WWidth), "Window");
	std::vector<Bird> bird_array;
	int velocity = 1;
	int vr = 1;
	int va = 90;
	int seperation = 5;
	int no_birds = 100;
	for (int i = 0; i < no_birds; i++)
	{
		bird_array.push_back(Bird(rand() % WHeight, rand() % WWidth, velocity, rand() % 361, vr, va, seperation));
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		/*
		for (int i = 0; i < bird_array.size(); i++)
		{
			bird_array[i].alignment(bird_array);
		}
		*/
		
		for (int i = 0; i < bird_array.size(); i++)
		{
			bird_array[i].cohesion(bird_array);
		}
		/*
		for (int i = 0; i < bird_array.size(); i++)
		{
			bird_array[i].separation(bird_array);
		}
		for (int i = 0; i < bird_array.size(); i++)
		{
			bird_array[i].update(WWidth,WHeight);
		}
		*/
		window.clear();
		for (int i = 0; i < bird_array.size(); i++)
		{
			window.draw(bird_array[i].get_shape());
		}
		window.display();
	}
}