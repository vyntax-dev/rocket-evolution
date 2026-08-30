#include <SFML/Graphics.hpp>
#include "events.h"
#include "rocket.h"

using namespace sf;
using namespace std;

void processGeometry(VertexArray& va, const uint32_t &idx, const Rocket &rocket) {

	const uint32_t i = conf::vertexCount * idx;
	const Vector2f p = rocket.position;

	constexpr Vector2f local[3] = {
		{0.f, -conf::scale * 2},          // nose
		{-conf::scale, conf::scale},      // back-left
		{conf::scale, conf::scale}        // back-right
	};

	const float rad = (rocket.angle + degrees(90)).asRadians();
	const float c = cos(rad);
	const float s = sin(rad);

	for (int k = 0; k < 3; k++) {
		const Vector2f rotated{
			local[k].x * c - local[k].y * s,
			local[k].x * s + local[k].y * c
		};
		va[i + k].position = p + rotated;
		va[i + k].color = conf::color;
	}
}

int main()
{
	RenderWindow window( VideoMode( VideoMode::getDesktopMode().size ), "stars ooga booga", Style::None );
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(conf::framerate);

	// Initialize target
	Obstacle target{conf::targetOrigin, conf::targetWidth, conf::targetHeight};
	RectangleShape targetShape{{target.width, target.height}};
	targetShape.setFillColor(conf::targetColor);
	targetShape.setPosition(target.position);

	// Initialize obstacle
	Obstacle obstacle{conf::obstacleOrigin, conf::obstacleWidth, conf::obstacleHeight};
	RectangleShape obstacleShape{{obstacle.width, obstacle.height}};
	obstacleShape.setFillColor(conf::obstacleColor);
	obstacleShape.setPosition(obstacle.position);

	// Initialize text
	const Font font("res/Oswald.ttf");
	Text text(font);
	text.setCharacterSize(24);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold);

	// Initialize rockets
	VertexArray va{PrimitiveType::Triangles, conf::vertexCount * conf::count};
	Population rockets{};
	uint32_t lifeCounter = 0;

	while ( window.isOpen() ) {
		processEvents( window);

		if (window.hasFocus()) {
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				target.position = static_cast<Vector2f>(Mouse::getPosition());
				targetShape.setPosition(target.position);
			}
			if (Mouse::isButtonPressed(Mouse::Button::Right)) {
				obstacle.position = static_cast<Vector2f>(Mouse::getPosition());
				obstacleShape.setPosition(obstacle.position);
			}
		}

		uint32_t bestRocketIdx = 0;
		if (lifeCounter < conf::lifespan) {
			lifeCounter++;
			rockets.live(obstacle, target);
			text.setString(
				"Generation #: " + to_string(rockets.generations) +
				"\nCycles left until sacrifice: " + to_string(conf::lifespan - lifeCounter)
				+ "\n\n(Left click to set target position)");
		}
		else {
			lifeCounter = 0;
			rockets.fitness();
			rockets.selection();
			rockets.breed();
			rockets.generations++;
		}
		// Rendering
		window.clear(conf::bgColor);

		for ( int i = 0; i < conf::count; ++i ) {
			processGeometry(va, i, rockets.population[i]);
		}

		window.draw(targetShape);
		window.draw(obstacleShape);
		window.draw(va);
		window.draw(text);

		window.display();
	}
}