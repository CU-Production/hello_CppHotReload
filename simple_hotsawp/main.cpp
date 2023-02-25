//
// Created by Admin on 2023/2/25.
//

#include "hscpp/Hotswapper.h"
#include "HotSwapObject.h"
#include "GlobalUserData.h"
#include <iostream>
#include <thread>
#include <chrono>


int main()
{
    std::cout << "Hello world!" << std::endl;
    std::cout << HELLO_HSCPP_ROOT_PATH << std::endl;

    hscpp::Hotswapper swapper;

    auto srcPath = HELLO_HSCPP_ROOT_PATH"/simple_hotsawp";
    auto includePath = HELLO_HSCPP_ROOT_PATH"/simple_hotsawp";

    swapper.AddSourceDirectory(srcPath);
    swapper.AddIncludeDirectory(includePath);

    // When an object is recompiled, a new dynamic library is linked into the running program
    // with its own statics and globals. You can give a pointer to user-defined data which will
    // be shared across all modules, since normal statics and globals will not be visible in
    // the newly compiled library.
    GlobalUserData globalUserData;
    swapper.SetGlobalUserData(&globalUserData);

    globalUserData.pObj = swapper.GetAllocationResolver()->Allocate<HotSwapObject>();

    while (true)
    {
        globalUserData.pObj->Update();
        swapper.Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
