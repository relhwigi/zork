#ifndef ITEM_H
#define ITEM_H
#include <stdio.h>
#include <string>
#include <vector>


using namespace std;

class item
{
    private:
    string description;
    
    public:
    item(string str);
    string getDescription();
    
};
#endif //ITEM_H
