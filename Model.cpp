#include "Model.h"
#include <iostream>
using namespace std;

Model::Model(){
    time = -1;  //So when u run show status first the time is 0

    PokemonCenter* Center1 = new PokemonCenter(1,1,100,Point2D(1,20));  //100
    PokemonCenter* Center2 = new PokemonCenter(2,2,200,Point2D(10,20)); //200

    Trainer* Trainer1 = new Trainer("Ash",1,'T',2,Point2D(5,1));
    Trainer* Trainer2 = new Trainer("Misty",2,'T',2,Point2D(10,1));

    PokemonGym* Gym1 = new PokemonGym(10,1,2,3,1,Point2D(0,0));
    PokemonGym* Gym2 = new PokemonGym(10,5,7.5,4,2,Point2D(5,5));

    WildPokemon* pokemon1 = new WildPokemon("Charmander", 2, 5, false, 1, Point2D(10,12));
    WildPokemon* pokemon2 = new WildPokemon("Bulbasaur", 2, 5, false, 2, Point2D(15,5));

    // Adding classes to object pointer
    object_ptrs.push_back(Trainer1);
    object_ptrs.push_back(Trainer2);
    object_ptrs.push_back(Center1);
    object_ptrs.push_back(Center2);
    object_ptrs.push_back(Gym1);
    object_ptrs.push_back(Gym2);
    object_ptrs.push_back(pokemon1);
    object_ptrs.push_back(pokemon2);

    // Adding classes to active pointer
    active_ptrs.push_back(Trainer1);
    active_ptrs.push_back(Trainer2);
    active_ptrs.push_back(Center1);
    active_ptrs.push_back(Center2);
    active_ptrs.push_back(Gym1);
    active_ptrs.push_back(Gym2);
    active_ptrs.push_back(pokemon1);
    active_ptrs.push_back(pokemon2);

    // Adding trainer pointers
    trainer_ptrs.push_back(Trainer1);
    trainer_ptrs.push_back(Trainer2);

    // Adding center pointers
    center_ptrs.push_back(Center1);
    center_ptrs.push_back(Center2);

    // Adding gym pointers
    gym_ptrs.push_back(Gym1);
    gym_ptrs.push_back(Gym2);

    // Adding wild pokemon pointers
    pokemon_ptrs.push_back(pokemon1);
    pokemon_ptrs.push_back(pokemon2);

    cout<<"Model defualt constructed\n";
}

Model::~Model(){
    cout<<"Model deconstructed\n";
}

Trainer* Model::GetTrainerPtr(int id){
    for (Trainer* i: trainer_ptrs){
        if(i->GetId() == id)
            return i;
    }
    return NULL;
}

PokemonCenter* Model::GetPokemonCenterPtr(int id){
    for (PokemonCenter* i: center_ptrs){
        if (i->GetId() == id)
            return i;
    }
    return 0;
}

PokemonGym* Model::GetPokemonGymPtr(int id){
    for (PokemonGym* i: gym_ptrs){
        if (i->GetId() == id)
            return i;
    }
    return 0;
}

void Model::Quit(){
    for (GameObject* i: object_ptrs){
        delete i;
    }

    exit(0);
}

bool Model::Update(){
    time++;

    // Update objects in active ptr
    int updateCheck = 0;
    for (GameObject* i: active_ptrs){
        if (i->Update()){
            updateCheck++;
        }
    }

    //Loops through active pointers and deletes any innactive ones
    for (list<Trainer*>::iterator it = trainer_ptrs.begin(); it != trainer_ptrs.end(); it++) {
        if ((*it)->GetState() == FAINTED){
            active_ptrs.remove(*it);
            cout << "Dead object removed" << endl;
        }
    }

    // Check if all gyms are deafeated
    int gymPassed = 0;
    for (PokemonGym* i: gym_ptrs){
        if (i->passed())
            gymPassed++;
    }
    if (gymPassed == gym_ptrs.size()){
        cout<<"GAME OVER: You Win! All Battles Done!\n";
        Model::Quit();
    }

    // Check if all trainers are dead
    int trainersDead = 0;
    for (Trainer* i: trainer_ptrs){
        if (i->HasFainted())
            trainersDead++;
    }
    if (trainersDead == trainer_ptrs.size()){
        cout<<"GAME OVER: You Lose! All of your Trainer's pokemon have fainted!\n";
        Model::Quit();
    }

    // Updates wildpokemon and trainers
    for (WildPokemon* i: pokemon_ptrs){
        for (Trainer* j: trainer_ptrs){
            if (i->GetState() != IN_TRAINER && (i->GetLocation() == j->GetLocation())){
                if (!(j->HasFainted())){
                    i->changeState(IN_TRAINER);
                    i->follow(j);
                    j->changePokemon(true);
                }
                else
                    j->changePokemon(false);
            }
        }
    }

    if (updateCheck != 0)
        return true;
    else
        return false;
}

void Model::Display(View& view){
    view.clear();
    for (GameObject* i: active_ptrs){
        view.Plot(i);
    }
    view.Draw();
}

void Model::ShowStatus(){
    cout<<"Time: "<<time<<endl;

    for (GameObject* i: object_ptrs){
        i->ShowStatus();
    }
}

void Model::NewCommand(char letterID, int id, int x, int y) {
    if (checkXandY(x,y) && checkID(letterID, id) && checkLetterID(letterID)){
        if (letterID == 'c'){
            PokemonCenter* temp = new PokemonCenter(id, 1, 100, Point2D(x,y));
            center_ptrs.push_back(temp);
            object_ptrs.push_back(temp);
            active_ptrs.push_back(temp);
        }
        if (letterID == 'g'){
            PokemonGym* temp = new PokemonGym(10, 1, 2, 3, id, Point2D(x,y));
            gym_ptrs.push_back(temp);
            object_ptrs.push_back(temp);
            active_ptrs.push_back(temp);
        }
        if (letterID == 't'){
            Trainer* temp = new Trainer("New Trainer", id, 'T', 2, Point2D(x,y));
            trainer_ptrs.push_back(temp);
            object_ptrs.push_back(temp);
            active_ptrs.push_back(temp);
        }
        if (letterID =='w'){
            WildPokemon* temp = new WildPokemon("Wild Pokemon", 3, 5, false, id, Point2D(x,y));
            pokemon_ptrs.push_back(temp);
            object_ptrs.push_back(temp);
            active_ptrs.push_back(temp);
        }
    }
}


bool Model::checkXandY(int x, int y){
    Point2D temp = Point2D(x,y);
    for (GameObject* i: active_ptrs){
        if ((i->GetLocation() == temp)){
            cout<<"Object already in location\n";
            return false;
        }
        else if ((temp.x>20 || temp.x<0) && (temp.y>20 || temp.y<0)){
            cout<<"Location out of grid\n";
            return false;
        }
    }
    return true;
}

bool Model::checkID(char letterID, int id){
    switch (letterID){
        case ('c'):
            for (PokemonCenter* i: center_ptrs){
                if (i->GetId() == id){
                    cout<<"Pokemon Center with ID: "<<id<<" is already in the game!\n";
                    return false;
                }
            }
            return true;
            break;

        case ('t'):
            for (Trainer* i: trainer_ptrs){
                if (i->GetId() == id){
                    cout<<"Trainer with ID: "<<id<<" is already in the game!\n";
                    return false;
                }
            }
            return true;
            break;

        case ('g'):
            for (PokemonGym* i: gym_ptrs){
                if (i->GetId() == id){
                    cout<<"Pokemon Gym with ID: "<<id<<" is already in the game!\n";
                    return false;
                }
            }
            return true;
            break;

        case ('w'):
            for (WildPokemon* i: pokemon_ptrs){
                if (i->GetId() == id){
                    cout<<"Wild Pokemon with ID: "<<id<<" is already in the game!\n";
                    return false;
                }
            }
            return true;
            break;

        default:
            cout<<"Invalid type id\n";
            return false;
    }
    return false;
}

bool Model::checkLetterID(char letterID){
    if (letterID == 'c' || letterID == 'g'|| letterID == 't'|| letterID == 'w')
        return true;
    else 
        return false;
}