#include "PokemonCenter.h"
#include <iostream>
using namespace std;

PokemonCenter::PokemonCenter()
    :Building()
{
    display_code = 'C';
    potion_capacity = 2;
    num_potions_remaining = potion_capacity;
    pokedollar_cost_per_potion = 5;
    state = POTIONS_AVAILABLE;
    cout<<"PokemonCenter defualt constructed\n";
}

PokemonCenter::PokemonCenter(int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc)
    :Building('C',in_id, in_loc)
{
    pokedollar_cost_per_potion = potion_cost;
    potion_capacity = potion_cap;
    num_potions_remaining = potion_cap;
    state = POTIONS_AVAILABLE;
    cout<<"PokemonCenter constructed\n";
}

PokemonCenter::~PokemonCenter(){
    cout<<"PokemonCenter deconstructed\n";
}

bool PokemonCenter::HasPotions(){
    if (num_potions_remaining>0)
        return true;
    else
        return false;
}

unsigned int PokemonCenter::GetNumPotionRemaining(){
    return num_potions_remaining;
}

bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget){
    if (budget>=potion*pokedollar_cost_per_potion)
        return true;
    else 
        return false;
}

double PokemonCenter::GetPokeDollarCost(unsigned int potion){
    return potion*pokedollar_cost_per_potion;
}

unsigned int PokemonCenter::DistributePotion(unsigned int potion_needed){
    if (num_potions_remaining>=potion_needed){
        num_potions_remaining-=potion_needed;
        return potion_needed;
    }
    else{
        int temp = num_potions_remaining;
        num_potions_remaining=0;
        return temp;
    }
}

bool PokemonCenter::Update(){
    if (state == POTIONS_AVAILABLE && num_potions_remaining==0){
        state = NO_POTIONS_AVAILABLE;
        display_code = 'c';
        cout<<"PokemonCenter ("<<id_num<<") has ran out of potions.\n";
        return true;
    }
    else
        return false;
}

void PokemonCenter::ShowStatus(){
    cout<<"PokemonCenter Status: \n";
    Building::ShowStatus();
    cout<<"PokeDollars per potion: "<<pokedollar_cost_per_potion<<endl;
    if (num_potions_remaining>=0 && num_potions_remaining<=1)
        cout<<"has "<<num_potions_remaining<<" potion remaining.\n";
    else
        cout<<"has "<<num_potions_remaining<<" potions remaining.\n";
}