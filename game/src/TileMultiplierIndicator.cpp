#include "TileMultiplierIndicator.h"
#include "render.h"
#include <format>

void TileMultiplierIndicator::Draw(Rectangle r, Color tint)
{
	DrawRectangleV(Vector2{ r.x,r.y }, Vector2{ r.width, r.height }, tint);

	std::string mult = std::format("{:.2f}", multiplier);
	Render::DrawText(mult, font, fontSize, r, WHITE, Sprite::SPRITE_ALIGN::CENTER);
}
