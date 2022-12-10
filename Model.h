#ifndef MODEL_H
#define MODEL_H

#include "GameObject.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include "WildPokemon.h"
#include <list>
using namespace std;

class Model{
    private:
        int time;
        //GameObject* object_ptrs[10];
        list<GameObject*>object_ptrs;    //Points to all GameObjects
        list<GameObject*>active_ptrs;    //Points to all GameObjects that are alive and needs to be updated/displayed
        //int num_objects;

        //Trainer* trainer_ptrs[10];
        //int num_trainers;
        list<Trainer*>trainer_ptrs;

        //PokemonCenter* center_ptrs[10];
        //int num_centers;
        list<PokemonCenter*>center_ptrs;

        //PokemonGym* gym_ptrs[10];
        //int num_gym;
        list<PokemonGym*>gym_ptrs;

        //WildPokemon* pokemon_ptrs[10];
        //int num_wildpokemon;
        list<WildPokemon*>pokemon_ptrs;

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