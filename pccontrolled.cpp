#include "pccontrolled.h"
#include <algorithm>
#include <random>
#include "gamestate.h"

PCControlled PCControlled::CurrentPlayer = PCControlled("");
int PCControlled::DefaultBagSize = 100;

void PCControlled::Update(float dt)
{
}

void PCControlled::ShuffleBag(std::vector<Tile>* bag)
{
    std::shuffle(std::begin(*bag), std::end(*bag), GameState::rng);
}
