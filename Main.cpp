#include <SFML/Graphics.hpp>


int main()
{
	int WWidth = 1080;
	int WHeight = 1920;
	sf::RenderWindow window(sf::VideoMode(WHeight, WWidth), "Window");

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
		window.clear();
		window.display();
	}
}