#pragma once
#include "Vector2D.h"

class Asteroid
{
public:
	Asteroid();
	virtual ~Asteroid(){}
	bool inUse_ = false;
	
	void setPos(Vector2D p) { position_ = p; }
	void setVelocity(Vector2D v) { velocity_ = v; }
	void setSize(double w, double h) { width_ = w; height_ = h; }
	void setRotation(double	r) { rotation_ = r; }
	void setGeneracion(int g) { generaciones_ = g; }
	int getGeneracion() { return generaciones_; }
	double getRotation() { return rotation_; }

	Vector2D getPos() { return position_; }
	Vector2D getVel() { return velocity_; }
	int getScaleX() { return width_; }
	int getScaleY() { return height_; }

private:
	Vector2D position_;
	Vector2D velocity_;
	double width_;
	double height_;
	double rotation_;
	int generaciones_;
};

