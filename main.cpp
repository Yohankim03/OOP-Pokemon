#include <iostream>
#include <cctype>
#include "Vector2D.h"
#include "Point2D.h"
//#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "Model.h"
#include "GameCommand.h"
#include "View.h"
using namespace std;



int main(){
    View grid;
    Model main;
    main.Update();
    main.ShowStatus();
    main.Display(grid);
    do{
        int twoInputs[2];
        int id;
        int stopInput;
        char letterInput;

        for (int i=0;i<2;i++){
            cout<<"Enter the game command:\n";
            cin>>letterInput;
            letterInput = tolower(letterInput);

            if (letterInput=='a'){
                DoAdvanceCommand(main, grid);
                break;
            }
            if (letterInput=='r') {
                DoRunCommand(main, grid);
                break;
            }
            if (letterInput=='q'){
                cout<<"Quiting game\n";
                main.Quit();
                exit(0);
            }

            switch (letterInput){
                case ('s'):
                    cin>>stopInput;
                    DoStopCommand(main,stopInput);
                    break;

                case ('m'):
                    cin>>id;
                    for (int i=0;i<2;i++)
                        cin>>twoInputs[i];
                    DoMoveCommand(main, id, Point2D(twoInputs[0], twoInputs[1]));
                    break;
                
                case ('c'):
                    for (int i=0;i<2;i++)
                        cin>>twoInputs[i];
                    DoMoveToCenterCommand(main, twoInputs[0], twoInputs[1]);
                    break;

                case ('g'):
                    for (int i=0;i<2;i++)
                        cin>>twoInputs[i];
                    DoMoveToGymCommand(main, twoInputs[0], twoInputs[1]);
                    break;

                case ('p'):
                    for (int i=0;i<2;i++)
                        cin>>twoInputs[i];
                    DoRecoverInCenterCommand(main,twoInputs[0], twoInputs[1]);
                    break;
                
                case ('b'):
                    for (int i=0;i<2;i++)
                        cin>>twoInputs[i];
                    DoBattleCommand(main, twoInputs[0], twoInputs[1]);
                    break;
            }
            if(i==1){
                main.Update();
                main.ShowStatus();
                main.Display(grid);
            }
        }
    } while(true);
    return 0;

}