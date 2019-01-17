#include "stdafx.h"
#include "ShapeGroup.h"
#include <algorithm>

using namespace std;

ShapeGroup::ShapeGroup() : Drawable() {}

ShapeGroup::ShapeGroup(shared_ptr<const Color>& c) :
	Drawable(c) {}

ShapeGroup::~ShapeGroup() {
	for (auto &shape : shapes) {
		shape->setGroup(NULL);
		shape.reset(); 
	}
}

const vector<shared_ptr<Drawable>>& ShapeGroup::getShapes() const { return shapes; }

double ShapeGroup::Area() const {
	double sum = 0;
	for (auto &shape : shapes) sum += shape->Area();
	return sum;
}

void ShapeGroup::setColor(const shared_ptr<const Color>& couleur) {
	for (auto &shape : shapes) { shape->setColor(couleur); }
}

void ShapeGroup::Translate(const Vector2D& vecteur) {
	for (auto &shape : shapes) { shape->Translate(vecteur); }
}

void ShapeGroup::Scale(const Vector2D & point, const double ratio) {
	for (auto &shape : shapes) { shape->Scale(point, ratio); }
}

void ShapeGroup::Rotate(const Vector2D & point, const double angle) {
	for (auto &shape : shapes) { shape->Rotate(point, angle); }
}

string ShapeGroup::getName() const {
	return string("shapegroup");
}

string * ShapeGroup::accept(Visitor * v) { return v->visit(this); }

ShapeGroup& ShapeGroup::operator+(shared_ptr<Drawable> d) {
	//Regarde dans chaque ShapeGroupe crées, y compris donc celui-ci, si le Drawable
	//Est déjà présent
	if (d->getGroup()) throw Erreur(-6, "Drawable already in a group !");
	
	d->setGroup(this);
	d->setColor(getColor());
	shapes.push_back(shared_ptr<Drawable>(d));

	return *this;
}

ShapeGroup& ShapeGroup::operator-(shared_ptr<Drawable> d) {
	for (auto it = shapes.begin(); it != shapes.end(); it++) {
		if (**it == *d) {
			d->setGroup(NULL);
			d.reset();
			shapes.erase(it);// retire le pointeur du vecteur
			return *this;
		}
	}
	return *this;
}

bool ShapeGroup::operator==(const shared_ptr<Drawable> s) const {
	if (getId() == s->getId()) return true;
	
	//On test si s est présent dans les shapes
	for (auto &shape : getShapes()) { 
		if (*shape == *s) return true;
	}
	return false;
}

ShapeGroup::operator string()const {
	ostringstream oss;
	oss << getName() << ": ";
	for (auto &shape : shapes)
		oss << *shape;
	return oss.str();
}