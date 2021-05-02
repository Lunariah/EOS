#include <stdafx.h>
#include <iostream>
#include "Game.h"

using namespace std;
using json = nlohmann::json;

int main()
{
    Game EndOfSkeleton;
    
    EndOfSkeleton.Run();

    return EXIT_SUCCESS;
}