#include "Building.h"

Building::Building()
    :GameObject('B')
{
    trainer_count=0;
    cout<<"Building default constructed\n";
}

Building::Building(char in_code, int in_id, Point2D in_loc)
    :GameObject(in_loc, in_id, in_code)
{
    trainer_count=0;
    cout<<"Building constructed\n";
}

Building::~Building(){
    cout<<"Building deconstructed\n";
}

void Building::AddOneTrainer(){
    trainer_count++;
}

void Building::RemoveOneTrainer(){
    trainer_count--;
}

void Building::ShowStatus(){
    cout<<display_code<<id_num<<" at "<<location<<endl;
    if (trainer_count>=0 && trainer_count<=1)
        cout<<trainer_count<< " trainer is in this building\n";
    else
        cout<<trainer_count<< " trainers are in this building\n";
}

bool Building::ShouldBeVisible(){
    return true;
}