#include "Trainer.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
using namespace std;

Trainer::Trainer()
    :GameObject('T')
{
    speed = 5;
    cout<<"Trainer defualt constructed\n";
    is_at_center = false;
    is_in_gym = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = NULL;
    current_gym = NULL;
    name = "Ash";
    has_pokemon_following = false;

}

Trainer::Trainer(char in_code)
     :GameObject(in_code)
{
    speed = 5;
    state = STOPPED;
    cout<<"Trainer constructed\n";
    is_at_center = false;
    is_in_gym = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = NULL;
    current_gym = NULL;
    name = "Ash";
    has_pokemon_following = false;

}

Trainer::Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc)
    :GameObject(in_loc, in_id, in_code)
{
    speed = in_speed;
    name = in_name;
    cout<<"Trainer constructed\n";
    is_at_center = false;
    is_in_gym = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = NULL;
    current_gym = NULL;
    has_pokemon_following = false;
}

Trainer::~Trainer(){
    cout<<"Trainer deconstructed\n";
}

void Trainer::StartMoving(Point2D dest){
    SetupDestination(dest);
    bool canMove = true;
    if ((location.x==dest.x) && (location.y==dest.y)){
        cout<<"("<<display_code<<")("<<id_num<<"): I'm already there. See?\n";
        canMove = false;
    }
    if (state == FAINTED){
        cout<<"("<<display_code<<")("<<id_num<<"): My Pokemon have fainted. I may move but you cannot see me.\n";
        canMove = false;
    }
    if (canMove){
        cout<<display_code<<id_num<<": On my way.\n";
        if (state == IN_GYM)
            current_gym->RemoveOneTrainer();
        if (state == AT_CENTER)
            current_center->RemoveOneTrainer();
        state = MOVING;
    }
}

void Trainer::StartMovingToGym(PokemonGym* gym){
    Point2D gymLocation = gym->GetLocation();
    int gymId = gym->GetId();
    SetupDestination(gymLocation);
    bool canMove = true;
    if ((location.x==gymLocation.x) && (location.y==gymLocation.y)){
        cout<<"("<<display_code<<")("<<id_num<<"): I am already at the PokemonGym!.\n";
        canMove = false;
    }
    if (state == FAINTED){
        cout<<"("<<display_code<<")("<<id_num<<"): My Pokemon have fainted so I can't move to gym...\n";
        canMove = false;
    }
    if(canMove){
        cout<<display_code<<id_num<<": On my way to gym "<<gymId<<endl;
        if (state == IN_GYM)
            current_gym->RemoveOneTrainer();
        if (state == AT_CENTER)
            current_center->RemoveOneTrainer();
        current_gym = gym;
        state = MOVING_TO_GYM;
    }
}

void Trainer::StartMovingToCenter(PokemonCenter* center){
    Point2D centerLocation = center->GetLocation();
    int centerId = center->GetId();
    SetupDestination(centerLocation);
    if (state == FAINTED)
        cout<<"("<<display_code<<")("<<id_num<<"): My Pokemon have fainted so I should have go to the center...\n";
    else if ((location.x==centerLocation.x) && (location.y==centerLocation.y))
        cout<<"("<<display_code<<")("<<id_num<<"): I am already at the Center!\n";
    else {
        cout<<display_code<<id_num<<": On my way to Center "<<centerId<<endl;
        if (state == IN_GYM)
            current_gym->RemoveOneTrainer();
        if (state == AT_CENTER)
            current_center->RemoveOneTrainer();
        current_center = center;
        state = MOVING_TO_CENTER;
    }
}


void Trainer::StartBattling(unsigned int num_battles){
    bool canMove = true;
    if (state != IN_GYM){
        cout<<display_code<<id_num<<": I can only battle in a Pokemon Gym!\n";
        canMove = false;
    }
    if (state == FAINTED){
        cout<<display_code<<id_num<<": My Pokemon have fainted so no more battles for me...\n";
        canMove = false;
    }
    if (state == IN_GYM){
        if (!(current_gym->IsAbleToBattle(num_battles, PokeDollars, health))){
            cout<<display_code<<id_num<<": Not enough money for battles.\n";
            canMove = false;
        }
        if (current_gym->passed()){
            cout<<display_code<<id_num<<": Cannot battle! This Pokemon Gym has no more trainers to battle!\n";
            canMove = false;
        }
    }
    if (canMove){
        state = BATTLING_IN_GYM;
        int battles = current_gym->GetNumBattlesRemaining();
        if (battles>=num_battles)
            battles_to_buy = num_battles;
        else
            battles_to_buy = num_battles-(num_battles-battles);
        cout<<display_code<<": Started to battle at the Pokemon Gym "<<current_gym->GetId()<<" with "<<battles_to_buy<<" battles.\n"; 
    }
}

void Trainer::StartRecoveringHealth(unsigned int num_potions){
    bool canRecover = true;
    if (state != AT_CENTER){
        cout<<display_code<<id_num<<": I can only recover health at a Pokemon Center!\n";
        canRecover = false;
    }
    if (state == AT_CENTER){
        if (!(current_center->CanAffordPotion(num_potions, PokeDollars))){
            cout<<display_code<<id_num<<": Not enough money to recover health!\n";
            canRecover = false;
        }
        if (!(current_center->HasPotions())){
            cout<<display_code<<id_num<<": Cannot recover! No potions remaining in this Pokemon Center.\n";
            canRecover = false;
        }
    }
    if (canRecover){
        int centerId = current_center->GetId();
        potions_to_buy = current_center->DistributePotion(num_potions);
        PokeDollars-=current_center->GetPokeDollarCost(num_potions);
        cout<<display_code<<id_num<<": Started recovering at Pokemon Center "<<centerId<<endl;
        state = RECOVERING_HEALTH;
    }
}

void Trainer::Stop(){
    state = STOPPED;
    cout<<display_code<<id_num<<": Stopping...\n";
}

bool Trainer::HasFainted(){
    if (health == 0){
        return true;
    }
    else 
        return false;
}

bool Trainer::ShouldBeVisible(){
    if (state != FAINTED)
        return true;
    else
        return false;
}

string Trainer::GetName(){
    return name;
}

void Trainer::changePokemon(bool yesorno){
    has_pokemon_following = yesorno;
}

bool Trainer::HasPokemon(){
    if (has_pokemon_following)
        return true;
    else 
        return false;
}

void Trainer::TakeDamage(){
    if (HasPokemon()){
        int percent = rand()% 101;
        if (percent <= 25)
            health -= 2;
        else
            health--;
    }
    else 
        health--;
}

void Trainer::ShowStatus(){
    cout<<GetName()<<" status:\n";
    GameObject::ShowStatus();

    if (HasPokemon()){
        cout<<"Has a wild pokemon following them\n";
    }

    switch (state){
        case STOPPED:
            cout<<"Stopped\n";
            cout<<"Health: "<<health<<endl;
            cout<<"PokeDollars: "<<PokeDollars<<endl;
            cout<<"Experience: "<<experience<<endl;
            break;

        case MOVING:
            cout<<"Moving at a speed of "<<speed<<" to destination "<<destination<<" at each step of "<<delta<<".\n";
            cout<<"Health: "<<health<<endl;
            cout<<"PokeDollars: "<<PokeDollars<<endl;
            cout<<"Experience: "<<experience<<endl;
            break;

        case MOVING_TO_GYM:
            cout<<"Heading to Pokemon Gym "<<current_gym->GetId()<<" at a speed of "<<speed<<" at each step of "<<delta<<".\n";
            cout<<"Health: "<<health<<endl;
            cout<<"PokeDollars: "<<PokeDollars<<endl;
            cout<<"Experience: "<<experience<<endl;
            break;
            
        case MOVING_TO_CENTER:
            cout<<"Heading to Pokemon Center "<<current_center->GetId()<<" at a speed of "<<speed<<" at each step of "<<delta<<".\n";
            cout<<"Health: "<<health<<endl;
            cout<<"PokeDollars: "<<PokeDollars<<endl;
            cout<<"Experience: "<<experience<<endl;
            break;

        case IN_GYM:
            cout<<"Inside Pokemon Gym "<<current_gym->GetId()<<".\n";
            cout<<"Health: "<<health<<endl;
            cout<<"PokeDollars: "<<PokeDollars<<endl;
            cout<<"Experience: "<<experience<<endl;
            break;

        case AT_CENTER:
            cout<<"Inside Pokemon Center "<<current_center->GetId()<<".\n";
            cout<<"Health: "<<health<<endl;
            cout<<"PokeDollars: "<<PokeDollars<<endl;
            cout<<"Experience: "<<experience<<endl;
            break;

        case BATTLING_IN_GYM:
            cout<<"Battling in Pokemon Gym "<<current_gym->GetId()<<".\n";
            cout<<"Health: "<<health<<endl;
            cout<<"PokeDollars: "<<PokeDollars<<endl;
            cout<<"Experience: "<<experience<<endl;
            break;

        case RECOVERING_HEALTH:
            cout<<"Recovering health in Pokemon Center "<<current_center->GetId()<<".\n";
            cout<<"Health: "<<health<<endl;
            cout<<"PokeDollars: "<<PokeDollars<<endl;
            cout<<"Experience: "<<experience<<endl;
            break;

        case FAINTED:
            cout<<"Fainted\n";
            cout<<"Health: "<<health<<endl;
            cout<<"PokeDollars: "<<PokeDollars<<endl;
            cout<<"Experience: "<<experience<<endl;
            break;
    }
}

bool Trainer::Update(){
    bool locationResult;

    if (health == 0){
        if (state==FAINTED)
            return false;
        else{
            state=FAINTED;
            cout<<GetName()<<" is out of health and can't move.\n";
            changePokemon(false);
            return true;
        }
    }

    switch (state){
        case STOPPED:
            return false;
            break;

        case MOVING:
            TakeDamage();
            PokeDollars+=GetRandomAmountOfPokeDollars();    // get random # of pokedollars for battling random pokemon
            locationResult = UpdateLocation();
            if (locationResult){
                state = STOPPED;
                return true;
            }
            else
                return false;
            break;

        case MOVING_TO_GYM:
            TakeDamage();
            PokeDollars+=GetRandomAmountOfPokeDollars();    // get random # of pokedollars for battling random pokemon
            locationResult = UpdateLocation();
            if (locationResult){
                state = IN_GYM;
                current_gym->AddOneTrainer();
                return true;
            }
            else
                return false;
            break;

        case MOVING_TO_CENTER:
            TakeDamage();
            PokeDollars+=GetRandomAmountOfPokeDollars();    // get random # of pokedollars for battling random pokemon
            locationResult = UpdateLocation();
            if (locationResult){
                state = AT_CENTER;
                current_center->AddOneTrainer();
                return true;
            }
            else
                return false;
            break;

        case IN_GYM:
            return false;
            break;

        case AT_CENTER:
            return false;
            break;

        case BATTLING_IN_GYM:
            health-=current_gym->GetHealthCost(battles_to_buy);
            PokeDollars-=current_gym->GetPokeDollarCost(battles_to_buy);
            experience+=current_gym->TrainPokemon(battles_to_buy);
            if (battles_to_buy>1)
                cout<<"**"<<GetName()<<" completed "<<battles_to_buy<<" battles!**\n";
            else 
                cout<<"**"<<GetName()<<" completed "<<battles_to_buy<<" battle!**\n";
            cout<<"**"<<GetName()<<" gained "<<experience<<" experience!**\n";
            state = IN_GYM;
            return true;
            break;

        case RECOVERING_HEALTH:
            int recoveredHealth = 5*potions_to_buy;
            health+=recoveredHealth;

            if (potions_to_buy>1)
                cout<<"**"<<GetName()<<" bought "<<potions_to_buy<<" potions!**\n";
            else 
                cout<<"**"<<GetName()<<" bought "<<potions_to_buy<<" potions!**\n";
            cout<<"**"<<GetName()<<" recovered "<<recoveredHealth<<" health!**\n";
            state = AT_CENTER;
            return true;
            break;
    }
    return false;
}

bool Trainer::UpdateLocation(){
    // Sees if object is within one step of its destination it sets dest to location
    double oneStepX = fabs(destination.x-location.x);
    double oneStepY = fabs(destination.y-location.y);
    double absDeltaX = fabs(delta.x);
    double absDeltaY = fabs(delta.y);

    if ((absDeltaX>=oneStepX) && (absDeltaY>=oneStepY)){
        cout<<display_code<<id_num<<": I'm there!\n";
        location = destination;
        return true;
    }
    else{
        cout<<display_code<<id_num<<": Step...\n";
        location.x = location.x + delta.x;
        location.y = location.y + delta.y;
        return false;
    }
}

void Trainer::SetupDestination(Point2D dest){
    destination = dest;
    delta = (dest-location)*(speed/GetDistanceBetween(dest,location));
}

static double GetRandomAmountOfPokeDollars(){
    srand(time(NULL));
    return (rand()%3);
}