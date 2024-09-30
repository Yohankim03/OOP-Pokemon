#include "PokemonGym.h"

PokemonGym::PokemonGym()
    :Building()
{
    display_code = 'G';
    state = NOT_DEFEATED;
    max_number_of_battles = 4;
    num_battle_remaining = max_number_of_battles;
    health_cost_per_battle = 1;
    PokeDollar_cost_per_battle = 1.0;
    experience_per_battle = 2;
    cout<<"PokemonGym default constructed.\n";
}

PokemonGym::PokemonGym(unsigned int max_battle, unsigned int health_loss, double PokeDollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc)
    :Building('G', in_id, in_loc)
{
    id_num = in_id;
    state = NOT_DEFEATED;
    location = in_loc;
    max_number_of_battles = max_battle;
    num_battle_remaining = max_number_of_battles;
    health_cost_per_battle = health_loss;
    experience_per_battle = exp_per_battle;
    PokeDollar_cost_per_battle = PokeDollar_cost;
    cout<<"PokemonGym constucted.\n";
}

PokemonGym::~PokemonGym(){
    cout<<"PokemonGym deconstructed\n";
}

double PokemonGym::GetPokeDollarCost(unsigned int battle_qty){
    return battle_qty*PokeDollar_cost_per_battle;
}

unsigned int PokemonGym::GetHealthCost(unsigned int battle_qty){
    return battle_qty*health_cost_per_battle;
}

unsigned int PokemonGym::GetNumBattlesRemaining(){
    return num_battle_remaining;
}

bool PokemonGym::IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int health){
    if ((budget>=(PokeDollar_cost_per_battle*battle_qty))&&(health>=(health_cost_per_battle*battle_qty)))
        return true;
    else
        return false;
}

unsigned int PokemonGym::TrainPokemon(unsigned int battle_units){
    if ((num_battle_remaining>=battle_units)){
        num_battle_remaining-=battle_units;
        return battle_units*experience_per_battle;
    }
    else{
        int temp = num_battle_remaining;
        num_battle_remaining=0;
        return experience_per_battle*temp;
    }
}

unsigned int PokemonGym::GetExperiencePerBattle(){
    return experience_per_battle;
}

bool PokemonGym::Update(){
    if((state==NOT_DEFEATED) && (num_battle_remaining==0)){
        state = DEFEATED;
        display_code = 'g';
        cout<<"("<<display_code<<")("<<id_num<<") has been beaten.\n";
        return true;
    }
    else
        return false;
}

bool PokemonGym::passed(){
    if (num_battle_remaining==0)
        return true;
    else 
        return false;
}

void PokemonGym::ShowStatus(){
    cout<<"PokemonGymStatus: \n";
    Building::ShowStatus();
    cout<<"Max number of battles: "<<max_number_of_battles<<endl;
    cout<<"Health cost per battle: "<<health_cost_per_battle<<endl;
    cout<<"PokeDollar per battle: "<<PokeDollar_cost_per_battle<<endl;
    cout<<"Experience per battle: "<<experience_per_battle<<endl;
    if (num_battle_remaining==1)
        cout<<num_battle_remaining<<" battle is remaing for this PokemonGym.\n";
    else
        cout<<num_battle_remaining<<" battles are remaing for this PokemonGym.\n";
}