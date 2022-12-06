#ifndef BUILDING_H
#define BUILDING_H

#include "GameObject.h"

class Building: public GameObject{
    private:
        unsigned int trainer_count;
    public:
        Building();
        Building(char, int, Point2D);
        ~Building();

        void AddOneTrainer();
        void RemoveOneTrainer();
        void ShowStatus();
        bool ShouldBeVisible();
};
#endif