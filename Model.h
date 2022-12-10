#ifndef MODEL_H
#define MODEL_H

#include "GameObject.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include "WildPokemon.h"

class Model{
    private:
        int time;
        GameObject* object_ptrs[10];
        int num_objects;
        Trainer* trainer_ptrs[10];
        int num_trainers;
        PokemonCenter* center_ptrs[10];
        int num_centers;
        PokemonGym* gym_ptrs[10];
        int num_gym;
        WildPokemon* pokemon_ptrs[10];
        int num_wildpokemon;

    public:
        Model();
        ~Model();

        Trainer* GetTrainerPtr(int);
        PokemonCenter* GetPokemonCenterPtr(int);
        PokemonGym* GetPokemonGymPtr(int);
        bool Update();
        void Display(View&);
        void ShowStatus();
        void Quit();
};

#endif