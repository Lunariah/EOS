#include <stdafx.h>
#include <iostream>
#include "Game.h"

using namespace std;
using json = nlohmann::json;

int main()
{
    // TEST ZONE

    //Map m_debug("Assets/testmap.json");
    //m_debug.ReadTileMap("Assets/testmap.json");
    //json j = m_debug.tilemap;
    //
    //for (int i = 0; i < (int)j["layers"][0]["height"] * (int)j["layers"][0]["width"]; i++)
    //{
    //    cout << j["layers"][0]["data"][i] << endl;
    //}
    ////////////

    Game EndOfSkeleton;
    
    EndOfSkeleton.Run();

    return EXIT_SUCCESS;
}