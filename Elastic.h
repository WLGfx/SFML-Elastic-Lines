/*
 * Elastic.h
 *
 *  Created on: 25 Oct 2022
 *      Author: wlgfx
 */

#ifndef ELASTIC_H_
#define ELASTIC_H_

#include <SFML/Graphics.hpp>
#include <vector>

#define RADIUS_MAX 120.0f
#define POINTS_MAX 150
#define POINT_SPEED 40.0f

struct Point {
	sf::Vector2f pos;
	sf::Vector2f dir;
};

class Elastic {
public:
	Elastic(sf::RenderWindow *windowParent);
	virtual ~Elastic();

	void update();
	void draw();

private:
	sf::RenderWindow *window;
	Point points[POINTS_MAX];
	sf::Clock clock;
	float delta = 0.0f;
	sf::CircleShape shape;
	sf::Vertex lines[POINTS_MAX * POINTS_MAX]; // big block yep
	uint line_count;

	void init();
	void update_points();
	void update_lines();
};

#endif /* ELASTIC_H_ */
