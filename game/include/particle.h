#pragma once
#include "raylib.h"

#include "drawable.h"

#include <memory>
#include <functional>
#define _USE_MATH_DEFINES

#include <math.h>
#define MAX_PARTICLES 1024
class Particle : Drawable
{
public:
	Vector2 position;
	Vector2 velocity;
	Color color;
	float lifetime;
	float radius;
	bool alive;


	inline static float _GRAVITY = 980.0f;

	void (*Update)(Particle* p, float dt);

	static Particle particles[MAX_PARTICLES];
	inline static int _PARTICLES_CURRENT = 0;

	Rectangle GetPosition() override
	{
		return Rectangle{ position.x, position.y, radius, radius };
	}
	void Draw(Rectangle r, Color tint) override
	{
		DrawCircle((int)r.x, (int)r.y, r.width, color);
	}
	static void CreateParticle(Vector2 Position, float Angle, Color col, float Lifetime, float Radius, float initialSpeed, int DrawOrder, void (*update)(Particle* p, float dt))
	{
		Particle p = Particle(Position, Angle, col, Lifetime,Radius, initialSpeed, DrawOrder, update);
		particles[_PARTICLES_CURRENT] = p;
			_PARTICLES_CURRENT++;

		if (_PARTICLES_CURRENT >= MAX_PARTICLES)
			_PARTICLES_CURRENT = 0;

	}
	static void UpdateAllParticles(float dt)
	{
		for (int i = 0; i < MAX_PARTICLES; i++)
		{
			Particle* p = &particles[i];
			if (p->alive && p->Update)
				p->Update(p, dt);
		}
	}
	static void BasicUpdate(Particle* p, float dt)
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
	float DegreesToRadians(float deg) {
		return deg * DEG2RAD;
	}
	Particle() : Drawable("", 0)
	{
		position = Vector2{ 0,0 };
		velocity = Vector2{ 0,0 };
		color = Color{ 0,0,0,0 };
		lifetime = 0;
		radius = 0;
		alive = false;
		Update = nullptr;
		Drawable::HideDrawing();
	}
private:
	Particle(Vector2 Position, float Angle, Color col, float Lifetime, float Radius, float initialSpeed, int DrawOrder, void (*update)(Particle* p, float dt)) : Drawable("",DrawOrder)
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

};
