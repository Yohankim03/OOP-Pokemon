#include "View.h"

bool View::GetSubscripts(int& out_x, int& out_y, Point2D location){
    Vector2D vect = ((location-origin)/scale);

    if ((vect.x<=scale*size) && (vect.x>=0)){
        if ((vect.y<=scale*size) && (vect.y>=0)){
            out_x = (int)vect.x;
            out_y = (int)vect.y;
            return true;
        }
    }
    else{
        cout<<"An object is outside the display\n";
        return false;
    }
    return false;
}

View::View(){
    size = 11;
    scale = 2;
    origin = Point2D(0,0);
}

void View::clear(){
    for (int i=0;i<size;i++){
        for (int j=0;j<size;j++){
            grid[i][j][0] = '.';
            grid[i][j][1] = ' ';
        }
    }
}

void View::Plot(GameObject* ptr){
    int x,y;
    Point2D loc = ptr->GetLocation();
    char* characters = new char[2];
    if (GetSubscripts(x,y,loc)){
        ptr->DrawSelf(characters);
        if (grid[x][y][0]=='.'){
            if(ptr->GetState()==FAINTED){
                grid[x][y][0] = '.';
                grid[x][y][1] = ' ';
            }
            else{
                grid[x][y][0] = *characters;
                grid[x][y][1] = *(characters+1);
            }
        }
        else{
            grid[x][y][0] = '*';
            grid[x][y][1] = ' ';
        }
    }
    delete []characters;
}

void View::Draw()
{
    for (int j = size-1; j >= -1; j--)
    {
        for (int i = -1; i <= size-1; i++)
        {
            //grid axis
            if (i == -1 && j%2 == 0)
            {
                cout << j*2;
                if (j/5 == 0)
                {
                    cout << " ";
                }
            }
            else if (i == -1 && j%2 != 0)
            {
                cout << "  ";
            }
            else if (j == -1 && i%2 == 0)
            {
                cout << i*2;
                if (i/5 == 0)
                {
                    cout << " ";
                }
                cout << "  ";
            }
            //draw objects
            if (i >= 0 && j >=0)
            {
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;
    }
}






