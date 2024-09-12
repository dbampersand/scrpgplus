#include "pccontrolled.h"
#include <algorithm>
#include <random>


PCControlled PCControlled::CurrentPlayer = PCControlled("");
int PCControlled::DefaultBagSize = 100;

void PCControlled::Update(float dt)
{
}

void PCControlled::ShuffleBag(std::vector<Tile>* bag)
{
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(*bag), std::end(*bag), rng);
}
