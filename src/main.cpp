#include <SFML/Graphics.hpp>
#include <random>
#include "events.h"
#include "config.h"
#include "rocket.h"

using namespace sf;
using namespace std;

void processGeometry(VertexArray& va, const int &idx, const Rocket &rocket) {

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
	RenderWindow window( VideoMode( conf::windowSize ), "stars ooga booga", Style::None );
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(conf::framerate);

	VertexArray va{PrimitiveType::Triangles, conf::vertexCount * conf::count};
	 vector<Rocket> rockets(conf::count, Rocket(0, 0));

	Angle rotation;
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
		for (int i = 0; i < conf::count; i++) {
			auto &rocket = rockets[i];
			if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
				rotation = degrees(-90);
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
				rotation = degrees(90);
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
				rotation = degrees(0);
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
				rotation = degrees(180);
			}
		}

		RenderStates states;
		states.transform.translate(conf::windowSizeF * 0.5f);
		states.transform.rotate(rotation);
		window.draw(va, states);

		window.display();
	}
}