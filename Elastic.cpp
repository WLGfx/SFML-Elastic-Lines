/*
 * Elastic.cpp
 *
 *  Created on: 25 Oct 2022
 *      Author: wlgfx
 */

#include <stdlib.h>
#include <math.h>
#include "Elastic.h"

Elastic::Elastic(sf::RenderWindow *windowParent) {
	window = windowParent;
	init();
}

Elastic::~Elastic() {}

void Elastic::init() {
	sf::Vector2u size = window->getSize();

	for (Point &pt : points) {
		pt.pos = sf::Vector2f(rand() % size.x, rand() % size.y);
		pt.dir = sf::Vector2f(
				(float(rand() % 1000) / 500.0f - 1.0f) * POINT_SPEED,
				(float(rand() % 1000) / 500.0f - 1.0f) * POINT_SPEED);
	}

	shape.setRadius(5);
	shape.setOrigin(5, 5);
}

void Elastic::update() {
	update_points();
	update_lines();
}

void Elastic::update_points() {
	sf::Vector2u size = window->getSize();

	for (Point &pt : points) {
		sf::Vector2f dest = pt.pos + pt.dir * delta;

		if (dest.x < 0.0f || dest.x > size.x) {
			dest.x = pt.pos.x;
			pt.dir.x = -pt.dir.x;
		}

		if (dest.y < 0.0f || dest.y > size.y) {
			dest.y = pt.pos.y;
			pt.dir.y = -pt.dir.y;
		}

		pt.pos = dest;
	}
}

void Elastic::update_lines() {
	line_count = 0;

	for (Point &pt1 : points) {
		for (Point &pt2 : points) {
			if (&pt1 != &pt2) {
				float xd = pt2.pos.x - pt1.pos.x;
				float yd = pt2.pos.y - pt1.pos.y;
				float dist = sqrt(xd * xd + yd * yd);
				if (dist < RADIUS_MAX) {
					int c = 255 - (255 * dist / RADIUS_MAX);
					lines[line_count].position = pt1.pos;
					lines[line_count].color = sf::Color(c, c, c);
					line_count++;
					lines[line_count].position = pt2.pos;
					lines[line_count].color = sf::Color(c, c, c);
					line_count++;
				}
			}
		}
	}
}

void Elastic::draw() {
	for (Point &pt : points) {
		shape.setPosition(pt.pos);
		window->draw(shape);
	}

	window->draw(lines, line_count, sf::Lines);

	delta = clock.restart().asSeconds();
}
