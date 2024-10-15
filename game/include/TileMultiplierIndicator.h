#pragma once

#include "drawable.h"
#include "raylib.h"
#include "slot.h"

class TileMultiplierIndicator : Drawable
{
	static inline const std::string font = "assets/fonts/PlayfairDisplay/PlayfairDisplay-Bold.ttf";
	static const int fontSize = 6;

	int x; int y;  int size;
	float multiplier;
	public:
		TileMultiplierIndicator(int X, int Y, int Size, Color col) : Drawable("", Slot::RenderOrder)
		{
			x = X;
			y = Y;
			size = Size;
			multiplier = 1.0f;
			SetTint(col);
			DisableShadow();
		}
		void Draw(Rectangle r, Color tint) override;

		Rectangle GetPosition() override
		{
			return Rectangle{ (float)x,(float)y,(float)size,(float)size };
		}
		void SetPosition(int X, int Y)
		{
			x = X; y = Y;
		}
		void SetMultiplier(float mult)
		{
			multiplier = mult;
		}
};