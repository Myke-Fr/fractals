#include <ctime>
#include <cstdio>
#include "node.hpp"

void drawNode(node &current, sf::RenderWindow &window);
void drawTree(node *n, sf::RenderWindow &window);
void zoom(sf::RenderWindow &window, float mx, float my, int delta);
node *createTree();

const float DEFAULT_SIZE = 600;

int main(){

	srand(time(NULL));

	node::set_minLength(8);

	node* n = createTree();

	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Fractal Tree (Custom)");


	window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width - screenWidth) / 2.f, 0));

	drawTree(n, window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
			else {
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
					delete n;

					n = createTree();

					drawTree(n, window);
				}
				if (event.type == sf::Event::MouseWheelMoved) {
					zoom(window, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, event.mouseWheel.delta);
					drawTree(n, window);
				}
			}
		}
	}
	 
	delete n;

	return 0;
}

void zoom(sf::RenderWindow &window, float mx, float my, int delta) {
	
	float zoom = delta == 1 ? 1.8f : 1.25f;

	sf::View view;
	view.setCenter(mx, my);
	view.zoom(zoom);

	window.setView(view);
}

float rainbow(float x) {
	return sin(1.f/tan(x));
}
sf::Color color(float x) {
	return sf::Color((sf::Uint8)(rainbow(x - 0.75f) * 255), (sf::Uint8)(rainbow(x - 0.5f) * 255), (sf::Uint8)(rainbow(x - 0.25f) * 255));
}

node *createTree() {
	node* n = new node(1, screenWidth / 2.f, (float)screenHeight);

	n->create_branch(0, DEFAULT_SIZE, -90);

	(*n)[0]->tree(DEFAULT_SIZE, -90);

	return n;
}

void drawTree(node *n, sf::RenderWindow &window) {
	window.clear();
	drawNode(*n, window);
	window.display();
}

void drawNode(node &current, sf::RenderWindow &window) {

	for (unsigned i = 0; i < current.getN(); i++) {

		//sf::Color col = color(current[i]->length());
		sf::Color col = current[i]->length() < 30 ? sf::Color(0, 255, 0, 100) : sf::Color(153, 77, 0); //165,42,42

		
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(current.X(), current.Y()), col),
			sf::Vertex(sf::Vector2f(current[i]->X(), current[i]->Y()), col)
		};

		window.draw(line, 2, sf::Lines);

		drawNode(*current[i], window);
	}

}
