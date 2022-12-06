#include "GameCommand.h"

void DoMoveCommand(Model& model, int trainer_id, Point2D p1){
    Trainer* trainer = model.GetTrainerPtr(trainer_id);

    if ((model.GetTrainerPtr(trainer_id))==NULL)
        cout<<"Error: Please enter a valid command!\n";
    else if (trainer->GetId()==trainer_id){
        cout<<"Moving "<<trainer->GetName()<<" to "<<p1<<endl;
        trainer->StartMoving(p1);
    }
}

void DoMoveToCenterCommand(Model& model, int trainer_id, int center_id){
    Trainer* trainer = model.GetTrainerPtr(trainer_id);
    PokemonCenter* center = model.GetPokemonCenterPtr(center_id);

    if (((model.GetTrainerPtr(trainer_id))==NULL) || (model.GetPokemonCenterPtr(center_id)==NULL))
        cout<<"Error: Please enter a valid command!\n";
    else if ((trainer->GetId()==trainer_id) && (center->GetId()==center_id)){
        cout<<"Moving "<<trainer->GetName()<<" to Pokemon Center "<<center_id<<endl;
        trainer->StartMovingToCenter(center);
    }
}

void DoMoveToGymCommand(Model& model, int trainer_id, int gym_id){
    Trainer* trainer = model.GetTrainerPtr(trainer_id);
    PokemonGym* gym = model.GetPokemonGymPtr(gym_id);

    if (((model.GetTrainerPtr(trainer_id))==NULL) || (model.GetPokemonGymPtr(gym_id)==NULL))
        cout<<"Error: Please enter a valid command!\n";
    else if ((trainer->GetId()==trainer_id) && (gym->GetId()==gym_id)){
        cout<<"Moving "<<trainer->GetName()<<" to Pokemon Center "<<gym_id<<endl;
        trainer->StartMovingToGym(gym);
    }
}

void DoStopCommand(Model& model, int trainer_id){
    Trainer* trainer = model.GetTrainerPtr(trainer_id);

    if ((model.GetTrainerPtr(trainer_id))==NULL)
        cout<<"Error: Please enter a valid command!\n";
    else if (trainer->GetId()==trainer_id){
        cout<<"Stopping "<<trainer->GetName()<<endl;
        trainer->Stop();
    }
}

void DoBattleCommand(Model& model, int trainer_id, unsigned int battles){
    Trainer* trainer = model.GetTrainerPtr(trainer_id);

    if ((model.GetTrainerPtr(trainer_id))==NULL)
        cout<<"Error: Please enter a valid command!\n";
    else if (trainer->GetId()==trainer_id){
        cout<<trainer->GetName()<<" is battling\n";
        trainer->StartBattling(battles);
    }
}

void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int potions_needed){
    Trainer* trainer = model.GetTrainerPtr(trainer_id);

    if ((model.GetTrainerPtr(trainer_id))==NULL)
        cout<<"Error: Please enter a valid command!\n";
    else if (trainer->GetId()==trainer_id){
        cout<<"Recovering "<<trainer->GetName()<<"'s Pokemon's health\n";
        trainer->StartRecoveringHealth(potions_needed);
    }
}

void DoAdvanceCommand(Model& model, View& view){
    cout<<"Advancing one tick\n";
    model.Update();
    model.ShowStatus();
    model.Display(view);
}

void DoRunCommand(Model& model, View& view){
    cout<<"Advancing to next event\n";
    for (int i=0;i<5;i++){
        if(!(model.Update()))
            break;
    }
            
    model.ShowStatus();
    model.Display(view);
}

