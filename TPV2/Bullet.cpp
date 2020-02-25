#include "Bullet.h"

Bullet::Bullet()
{
	position_ = Vector2D(0,0);
	velocity_ = Vector2D(0,0);
	width_ = 0;
	height_ = 0;
	rotation_ = 0;
}

Bullet::~Bullet()
{
}

void Bullet::setPos(Vector2D p)
{
	position_ = p;
}

void Bullet::setVelocity(Vector2D v)
{
	velocity_ = v;
}

void Bullet::setSize(double w, double h)
{
	width_ = w;
	height_ = h;
}

void Bullet::setRotation(double r)
{
	rotation_ = r;
}

Vector2D Bullet::getPos()
{
	return position_;
}

Vector2D Bullet::getVel()
{
	return velocity_;
}
