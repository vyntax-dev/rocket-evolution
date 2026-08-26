#include <SFML/Graphics.hpp>
#include <random>
#include "events.h"
#include "config.h"
#include "star.h"

using namespace sf;

std::vector<Star> createStars(const uint32_t &count, const float &scale) {
	std::vector<Star> stars;
	stars.reserve(count);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);
	for (uint32_t i = 0; i < count; ++i) {
		float const x = (dist(gen) - 0.5f) * conf::windowSize.x * scale;
		float const y = (dist(gen) - 0.5f) * conf::windowSize.y * scale;
		float const z = dist(gen) * (conf::far - conf::near) + conf::near;
		stars.push_back({{x, y}, z});
	}

	sort(stars.begin(), stars.end(), [](const Star& s1, const Star& s2) {
		return s1.z > s2.z;
	});
	return stars;
}

void updateGeometry(const uint32_t idx, const Star &star, VertexArray &va) {
	const float scale = 1 / star.z;
	const float depthRatio = star.z / conf::far;
	const float colorRatio = 1.0f - depthRatio;
	const auto c = static_cast<uint8_t>(colorRatio * 255);

	const Vector2f p = star.pos * scale;
	const float r = conf::radius * scale;
	const uint32_t i = conf::vertexCount * idx;

	va[i + 0].position = Vector2f(p.x + r, p.y + r);
	va[i + 1].position = Vector2f(p.x + r, p.y - r);
	va[i + 2].position = Vector2f(p.x - r, p.y - r);
	//va[i + 3].position = Vector2f(p.x - r, p.y - r);

	const Color color{c, c, c};
	va[i + 0].color = color;
	va[i + 1].color = color;
	va[i + 2].color = color;
	//va[i + 3].color = color;
}

int main()
{
	RenderWindow window( VideoMode( conf::windowSize ), "stars ooga booga", Style::None );
	window.setFramerateLimit(conf::framerate);

	const std::vector<Star> stars = createStars(conf::count, conf::far);
	VertexArray va{PrimitiveType::Triangles, conf::vertexCount * conf::count};

	Texture texture;
	texture.loadFromFile("res/star.png");
	texture.setSmooth(true);
	texture.generateMipmap();

	auto const textureSizeF = static_cast<Vector2f>(texture.getSize());
	for (uint32_t idx = conf::count; idx--;) {
		const uint32_t i =  conf::vertexCount * idx;
		va[i + 0].texCoords = {0.0f, 0.0f};
		va[i + 1].texCoords = {0.0f, textureSizeF.y};
		va[i + 2].texCoords = {textureSizeF.x, 0.0f};
		//va[i + 3].texCoords = {textureSizeF.x, textureSizeF.y};
	}

	uint32_t first = 0;
	while ( window.isOpen() )
	{
		processEvents( window);

		// Make move
		for (uint32_t i = conf::count; i--;) {
			const auto &star = stars[i];
			star.z -= conf::speed * conf::dt;
			if (star.z <= conf::near) {
				star.z = conf::far - conf::near - star.z;
				first = i;
			}
		}

		// Rendering
		window.clear();

		CircleShape shape(conf::radius);
		for (uint32_t i = 0; i < conf::count; i++) {
			uint32_t const idx = (first + i) % conf::count;
			Star star = stars[idx];

			updateGeometry(i, star, va);
		}
		RenderStates states;
		states.transform.translate(conf::windowSizeF * 0.5f);
		states.texture = &texture;
		window.draw(va, states);

		window.display();
	}
}
