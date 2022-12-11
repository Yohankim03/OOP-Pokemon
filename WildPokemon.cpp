#include "WildPokemon.h"

WildPokemon::WildPokemon(string name, double atck, double hp, bool var, int id, Point2D in_loc)
    :GameObject(in_loc, id, 'W')
{
    this->name = name;
    attack = atck;
    health = hp;
    variant = var;
    cout<<"WildPokemon constructed\n";
}

WildPokemon::~WildPokemon(){
    cout<<"WildPokemon deconstructed\n";
}

void WildPokemon::follow(Trainer* t){
    current_trainer = t;
}

bool WildPokemon::get_variant(){
    return variant;
}

double WildPokemon::get_attack(){
    return attack;
}

double WildPokemon::get_health(){
    return health;
}

bool WildPokemon::get_in_combat(){
    return in_combat;
}

void WildPokemon::changeState(char state){
    this->state = state;
}


bool WildPokemon::Update(){
    if (state == IN_ENVIRONMENT)
        return false;
    
    if (health ==0){
        state = DEAD;
        return true;
    }

    if (state == IN_TRAINER){
        this->location = current_trainer->GetLocation();
        if (current_trainer->HasFainted()){
            current_trainer = NULL;
            state = IN_ENVIRONMENT;
        }
        return false;
    }
        

    return false;
}

void WildPokemon::ShowStatus(){
    cout<<"Wild Pokemon status:\n";
    GameObject::ShowStatus();
    switch (state){
        case IN_ENVIRONMENT:
            cout<<"In Environment\n";
            cout<<"Health: "<<health<<endl;
            cout<<"Attack: "<<attack<<endl;
            break;
        case DEAD:
            cout<<"WildPokemon is out of health\n";
            break;
        case IN_TRAINER:
            cout<<"In Trainer\n";
            cout<<"Health: "<<health<<endl;
            cout<<"Attack: "<<attack<<endl;
            break;
    }
}

bool WildPokemon::isAlive(){
    if (health > 0)
        return true;
    else 
        return false;
}