#include <SFML/Graphics.hpp>
#include <random>
#include "events.h"
#include "config.h"
#include "rocket.h"

using namespace sf;
using namespace std;

void processGeometry(VertexArray& va, const int &idx, const Rocket &rocket) {

	const uint32_t i = conf::vertexCount * idx;
	const Vector2f p = rocket.pos;
	va[i+0].position = Vector2f(p.x, p.y);
	va[i+1].position = Vector2f(p.x - conf::scale, p.y + conf::scale*2);
	va[i+2].position = Vector2f(p.x + conf::scale, p.y + conf::scale*2);

	va[i+0].color = conf::color;
	va[i+1].color = conf::color;
	va[i+2].color = conf::color;
}

int main()
{
	RenderWindow window( VideoMode( conf::windowSize ), "stars ooga booga", Style::None );
	window.setFramerateLimit(conf::framerate);

	VertexArray va{PrimitiveType::Triangles, conf::vertexCount * conf::count};
	const vector<Rocket> rockets(conf::count, {{0.f, 0.f}});

	Vector2f offset{0, 0};
	while ( window.isOpen() )
	{
		processEvents( window);


		// Rendering
		window.clear(conf::bgColor);

		for (int i = 0; i < conf::count; i++) {
			Rocket rocket = rockets[i];
			processGeometry(va, i, rocket);
		}

		// Moving it
		if (Keyboard::isKeyPressed(Keyboard::Key::A))
			offset.x -= conf::speed;
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
			offset.x += conf::speed;
		if (Keyboard::isKeyPressed(Keyboard::Key::W))
			offset.y -= conf::speed;
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
			offset.y += conf::speed;

		RenderStates states;
		states.transform.translate(conf::windowSizeF * 0.5f + offset);
		states.transform.rotate(degrees(180));
		window.draw(va, states);

		window.display();
	}
}