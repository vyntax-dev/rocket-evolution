#include <SFML/Graphics.hpp>
#include "events.h"
#include "rocket.h"

using namespace sf;
using namespace std;

void processGeometry(VertexArray& va, const uint32_t &idx, const Rocket &rocket) {

	const uint32_t i = conf::vertexCount * idx;
	const Vector2f p = rocket.position;
	va[i+0].position = Vector2f(p.x, p.y);
	va[i+1].position = Vector2f(p.x - conf::scale, p.y + conf::scale*2);
	va[i+2].position = Vector2f(p.x + conf::scale, p.y + conf::scale*2);

	va[i+0].color = conf::color;
	va[i+1].color = conf::color;
	va[i+2].color = conf::color;
}

int main()
{
	RenderWindow window( VideoMode( VideoMode::getDesktopMode().size ), "stars ooga booga", Style::None );
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(conf::framerate);

	CircleShape target{conf::radius};
	target.setFillColor(conf::targetColor);
	target.setPosition(conf::targetOrigin);

	const Font font("res/Oswald.ttf");
	Text text(font);
	text.setCharacterSize(24);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold);

	VertexArray va{PrimitiveType::Triangles, conf::vertexCount * conf::count};
	Population rockets{};
	uint32_t lifeCounter = 0;

	while ( window.isOpen() ) {
		processEvents( window);

		if (window.hasFocus()) {
			if (Mouse::isButtonPressed(Mouse::Button::Left))
				target.setPosition(static_cast<Vector2f>(Mouse::getPosition()));
		}

		uint32_t bestRocketIdx = 0;
		if (lifeCounter < conf::lifespan) {
			lifeCounter++;
			rockets.live();
			text.setString(
				"Generation #: " + to_string(rockets.generations) +
				"\nCycles left until sacrifice: " + to_string(conf::lifespan - lifeCounter)
				+ "\n\n(Left click to set target position)");
		}
		else {
			lifeCounter = 0;
			rockets.fitness(target.getPosition());
			rockets.selection();
			rockets.breed();
			rockets.generations++;
		}
		// Rendering
		window.clear(conf::bgColor);

		for ( int i = 0; i < conf::count; ++i ) {
			processGeometry(va, i, rockets.population[i]);
		}

		window.draw(va);
		window.draw(target);
		window.draw(text);

		window.display();
	}
}