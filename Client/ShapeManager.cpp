#include "stdafx.h"
#include "ShapeManager.h"

ShapeManager* ShapeManager::instance = nullptr;

ShapeManager::ShapeManager() {
	shapes = {};
}

ShapeManager::~ShapeManager() {}

ShapeManager* ShapeManager::getInstance() {
	if (instance == nullptr) instance = new ShapeManager();
	return instance; 
}

const std::vector<shared_ptr<Drawable>> ShapeManager::getShapes() const { return shapes; }

ShapeManager* ShapeManager::operator+(shared_ptr<Drawable> drawable) {
	shapes.push_back(drawable);
	return instance;
}

string * ShapeManager::accept(Visitor * v) { return v->visit(this); }
