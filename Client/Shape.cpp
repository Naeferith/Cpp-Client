#include "stdafx.h"
#include "Shape.h"
#include "SingletonWSA.h"
#include "Circle.h"

using namespace std;

Shape::Shape() : Drawable() {}

Shape::Shape(const Vector2D &v) : Drawable(){ operator+(v); }

Shape::Shape(const Vector2D &v, const shared_ptr<const Color>& c) : Drawable(c) { operator+(v); }

Shape::Shape(const vector<Vector2D>& v, const shared_ptr<const Color>& c) :
	Drawable(c) { setVertices(v); }

Shape::Shape(const Shape& s): Drawable(s), vertices(vector<Vector2D>(s.getVertices())) {}

Shape::~Shape() {}

const vector<Vector2D> Shape::getVertices() const { return vertices; }

void Shape::setColor(const shared_ptr<const Color>& c) { color = c; }

void Shape::setVertices(const vector<Vector2D>& v) { vertices = v; }

bool Shape::operator==(const Shape& s) const {
	return Drawable::operator==(s) && (vertices == s.vertices);
}

void Shape::Translate(const Vector2D& V) {
	for (auto &vertice : vertices) {
		vertice.setX(round( vertice.x + V.x ));
		vertice.setY(round( vertice.y + V.y ));
	}
}

void Shape::Scale(const Vector2D& point, const double ratio) {
	for (auto &vertice : vertices) {
		vertice.setX(round( (vertice.x - point.x) * ratio ));
		vertice.setY(round( (vertice.y - point.y) * ratio ));
	}
}

void Shape::Rotate(const Vector2D& point, const double rad) {
	for (auto &vertice : vertices) {
		double newX = round((vertice.x - point.x) * cos(rad) - (vertice.y - point.y) * sin(rad));
		double newY = round((vertice.x - point.x) * sin(rad) + (vertice.y - point.y) * cos(rad));
		vertice.setX(newX);
		vertice.setY(newY);
	}
}

string Shape::getName() const {
	return string("shape");
}

const int Shape::getNb()const {
	return vertices.size();
}

string* Shape::accept(Visitor * v) { return v->visit(this); }

Shape Shape::operator+(const Vector2D & vecteur) {
	vertices.push_back(vecteur);
	return *this;
}

Shape Shape::operator--() {
	vertices.pop_back();
	return *this;
}

Shape::operator string() const {
	ostringstream oss;
	oss << getName() << ": " << getColor() << " [>> ";
	for (auto &vertice : vertices) oss << vertice << " ";
	oss << "<<]";
	return oss.str();
}