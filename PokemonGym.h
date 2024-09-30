#ifndef POKEMONGYM_H
#define POKEMONGYM_H
#include "Building.h"

enum PokemonGymStates {
    NOT_DEFEATED = 0,
    DEFEATED = 1
};

class PokemonGym: public Building{
    private:
        unsigned int num_battle_remaining;
        unsigned int max_number_of_battles;
        unsigned int health_cost_per_battle;
        double PokeDollar_cost_per_battle;
        unsigned int experience_per_battle;
    
    public:
        PokemonGym();
        PokemonGym(unsigned int, unsigned int, double, unsigned int, int, Point2D);
        ~PokemonGym();

        double GetPokeDollarCost(unsigned int);
        unsigned int GetHealthCost(unsigned int);
        unsigned int GetNumBattlesRemaining();
        bool IsAbleToBattle(unsigned int, double, unsigned int);
        unsigned int TrainPokemon(unsigned int);
        unsigned int GetExperiencePerBattle();
        bool Update();
        bool passed();
        void ShowStatus();
};


#endif
