#pragma once
#include "Vector2D.h"

class Bullet
{
public:
	Bullet();
	virtual ~Bullet();
	bool inUse_ = false;

	void setPos(Vector2D p);
	void setVelocity(Vector2D v);
	void setSize(double w, double h);
	void setRotation(double	r);

	Vector2D getPos();
	Vector2D getVel();
	double getW() { return width_; }
	double getH() { return height_; }
	double getRot() { return rotation_; }

private:
	Vector2D position_;
	Vector2D velocity_;
	double width_;
	double height_;
	double rotation_;
};

