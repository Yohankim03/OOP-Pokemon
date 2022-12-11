#include <iostream>
#include <stdlib.h>
using namespace std;

class Invalid_Input
{
 public :
    Invalid_Input(string in_ptr) : msg_ptr (in_ptr) { }
    const string msg_ptr;
 private :
    Invalid_Input ();
    // no default construction
};


int main(){
    try{
        char letter;
        int i;
        cin>>letter;
        if (!(cin>>i))
            throw i;
        else
            cout<<"letter: "<<letter<<" and num: "<<i<<endl;
    }
    catch (Invalid_Input& except) {
        cout << "Invalid input - " << except.msg_ptr << endl;
    }
}