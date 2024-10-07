#include "particle.h"

#define _USE_MATH_DEFINES
#include <math.h>

Particle Particle::particles[MAX_PARTICLES];

Particle::Particle(Vector2 Position, float Angle, Color col, float Lifetime, float Radius, float initialSpeed, int DrawOrder, void (*update)(Particle* p, float dt)) : Drawable("", DrawOrder)
{
	position = Position;
	float rad = DegreesToRadians(Angle);

	velocity.x = cos(rad) * initialSpeed;
	velocity.y = sin(rad) * initialSpeed;

	color = col;
	lifetime = Lifetime;
	Update = update;

	alive = true;
	radius = Radius;

	Drawable::ShowDrawing();
}
Particle::Particle() : Drawable("", 0)
{
	position = Vector2{ 0,0 };
	velocity = Vector2{ 0,0 };
	color = Color{ 0,0,0,0 };
	lifetime = 0;
	radius = 0;
	alive = false;
	Update = BasicUpdate;
	Drawable::HideDrawing();
}

Rectangle Particle::GetPosition()
{
	return Rectangle{ position.x, position.y, radius, radius };
}
void Particle::Draw(Rectangle r, Color tint) 
{
	DrawCircle((int)r.x, (int)r.y, r.width, color);
}
void Particle::CreateParticle(Vector2 Position, float Angle, Color col, float Lifetime, float Radius, float initialSpeed, int DrawOrder, void (*update)(Particle* p, float dt))
{
	Particle p = Particle(Position, Angle, col, Lifetime, Radius, initialSpeed, DrawOrder, update);
	
	//circular queue: when the index reaches MAX_PARTICLES, it resets to 0 and overwrites the particle in that position
	particles[_PARTICLES_CURRENT] = p;
	_PARTICLES_CURRENT++;

	if (_PARTICLES_CURRENT >= MAX_PARTICLES)
		_PARTICLES_CURRENT = 0;

}
void Particle::UpdateAllParticles(float dt)
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		Particle* p = &particles[i];
		if (p->alive && p->Update)
			p->Update(p, dt);
	}
}
void Particle::BasicUpdate(Particle* p, float dt)
{
	p->position.x += p->velocity.x * dt;
	p->position.y += p->velocity.y * dt;

	p->velocity.y += _GRAVITY * dt;
	p->lifetime -= dt;

	if (p->lifetime <= 0)
	{
		p->Drawable::HideDrawing();
		p->alive = false;
	}
}
float Particle::DegreesToRadians(float deg) {
	return deg * DEG2RAD;
}