#pragma once
#include "raylib.h"

#include "drawable.h"

#define MAX_PARTICLES 1024

//class is final as using inheritance would mean we have to store a Particle as a pointer and lose locality
class Particle final : Drawable
{
public:

	static void CreateParticle(Vector2 Position, float Angle, Color col, float Lifetime, float Radius, float initialSpeed, int DrawOrder, void (*update)(Particle* p, float dt));
	static void UpdateAllParticles(float dt);

	//Base update function, custom functions to be added here and then passed as the update argument in the constructor
	static void BasicUpdate(Particle* p, float dt);

	//Converts degrees to radians
	static float DegreesToRadians(float deg);

	Rectangle GetPosition() override;
	void Draw(Rectangle r, Color tint) override;

private:
	Particle(Vector2 Position, float Angle, Color col, float Lifetime, float Radius, float initialSpeed, int DrawOrder, void (*update)(Particle* p, float dt));
	Particle();

	//Circular queue of particles
	static Particle particles[MAX_PARTICLES];

	//Current creation position in the circular queue - added to when a particle is created, and set to 0 when it reaches MAX_PARTICLES
	inline static int _PARTICLES_CURRENT = 0;

	Vector2 position;
	Vector2 velocity;
	Color color;
	float lifetime;
	float radius;
	bool alive;

	inline static float _GRAVITY = 980.0f;

	//Function pointer to the update function the Particle should use
	void (*Update)(Particle* p, float dt);

};
