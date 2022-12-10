#include "Model.h"
#include <iostream>
using namespace std;

Model::Model(){
    time = -1;  //So when u run show status first the time is 0
    // num_objects = 8;
    // num_centers = 2;
    // num_trainers = 2;
    // num_gym = 2;
    // num_wildpokemon = 2;

    PokemonCenter* Center1 = new PokemonCenter(1,1,100,Point2D(1,20));  //100
    PokemonCenter* Center2 = new PokemonCenter(2,2,200,Point2D(10,20)); //200
    // object_ptrs[2] = Center1;
    // object_ptrs[3] = Center2;
    // center_ptrs[0] = Center1;
    // center_ptrs[1] = Center2;

    Trainer* Trainer1 = new Trainer("Ash",1,'T',2,Point2D(5,1));
    Trainer* Trainer2 = new Trainer("Misty",2,'T',2,Point2D(10,1));
    // object_ptrs[0] = Trainer1;
    // object_ptrs[1] = Trainer2;
    // trainer_ptrs[0] = Trainer1;
    // trainer_ptrs[1] = Trainer2;

    PokemonGym* Gym1 = new PokemonGym(10,1,2,3,1,Point2D(0,0));
    PokemonGym* Gym2 = new PokemonGym(10,5,7.5,4,2,Point2D(5,5));
    // object_ptrs[4] = Gym1;
    // object_ptrs[5] = Gym2;
    // gym_ptrs[0] = Gym1;
    // gym_ptrs[1] = Gym2;

    WildPokemon* pokemon1 = new WildPokemon("Charmander", 2, 5, false, 1, Point2D(10,12));
    WildPokemon* pokemon2 = new WildPokemon("Bulbasaur", 2, 5, false, 2, Point2D(15,5));
    // object_ptrs[6] = pokemon1;
    // object_ptrs[7] = pokemon2;
    // pokemon_ptrs[0] = pokemon1;
    // pokemon_ptrs[1] = pokemon2;

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

    // for (int i=0;i<num_trainers;i++){
    //     if ((*trainer_ptrs[i]).GetId()==id)
    //         return trainer_ptrs[i];
    // }
    // return NULL;
}

PokemonCenter* Model::GetPokemonCenterPtr(int id){
    for (PokemonCenter* i: center_ptrs){
        if (i->GetId() == id)
            return i;
    }
    return 0;

    // for (int i=0;i<num_centers;i++){
    //     if ((*center_ptrs[i]).GetId()==id)
    //         return center_ptrs[i];
    // }
    // return 0;
}

PokemonGym* Model::GetPokemonGymPtr(int id){
    for (PokemonGym* i: gym_ptrs){
        if (i->GetId() == id)
            return i;
    }
    return 0;

    // for (int i=0;i<num_gym;i++){
    //     if ((*gym_ptrs[i]).GetId()==id)
    //         return gym_ptrs[i];
    // }
    // return 0;
}

void Model::Quit(){
    object_ptrs.clear();
    // for (GameObject* i: object_ptrs){
    //     delete[] i;
    // }
    cout<<"Supposed to deconstruct\n";
    exit(0);

    // for (int i=0;i<num_objects;i++){
    //     delete object_ptrs[i];
    // }
    // exit(0);
}

bool Model::Update(){
    time++;

    // Update objects in active ptr
    int updateCheck = 0;
    for (GameObject* i: active_ptrs){
        if (i->Update()){
            updateCheck++;
            cout<<"Something updated\n";
        }
    }

    // Loops through active pointers and deletes any innactive ones
    for (list<GameObject*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); it++) {
        if ((*it)->GetState() == FAINTED){
            active_ptrs.erase(it);
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

    // for (int i=0;i<num_wildpokemon;i++){
    //     for (int j=0;j<num_trainers;j++){
    //         if (pokemon_ptrs[i]->GetState() != IN_TRAINER && (pokemon_ptrs[i]->GetLocation() == trainer_ptrs[j]->GetLocation())){
    //             if (!(trainer_ptrs[i]->HasFainted())){
    //                 pokemon_ptrs[i]->changeState(IN_TRAINER);
    //                 pokemon_ptrs[i]->follow(trainer_ptrs[j]);
    //                 trainer_ptrs[j]->changePokemon(true);
    //                 //return true;
    //             }
    //             else{
    //                 trainer_ptrs[j]->changePokemon(false);
    //             }
    //         }
    //     }
    // }

    // bool updateTrue = false;
    // for (int i=0;i<num_objects;i++){
    //     bool check = (*object_ptrs[i]).Update();
    //     if(check == true){
    //         updateTrue = true;
    //         break;
    //     }
    // }

    // int gymPassed = 0;
    // for (int i=0;i<num_gym;i++){
    //     if((*gym_ptrs[i]).passed())
    //         gymPassed++;
    // }
    // if (gymPassed==num_gym){
    //     cout<<"GAME OVER: You Win! All Battles Done!\n";
    //     Model::Quit();
    // }

    // int trainersFainted = 0;
    // for (int i=0;i<num_trainers;i++){
    //     if ((*trainer_ptrs[i]).HasFainted())
    //         trainersFainted++;
    // }
    // if (trainersFainted==num_trainers){
    //     cout<<"GAME OVER: You Lose! All of your Trainer's pokemon have fainted!\n";
    //     Model::Quit();
    // }

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

    // for (int i=0;i<num_objects;i++){
    //     view.Plot(object_ptrs[i]);
    // }
    view.Draw();
}

void Model::ShowStatus(){
    cout<<"Time: "<<time<<endl;

    for (GameObject* i: object_ptrs){
        i->ShowStatus();
    }

    // for (int i=0;i<num_objects;i++){
    //     (*object_ptrs[i]).ShowStatus();
    // }
}
