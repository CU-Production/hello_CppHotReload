//
// Created by Admin on 2023/2/25.
//

#include "HotSwapObject.h"
#include "GlobalUserData.h"
#include <iostream>

HotSwapObject::HotSwapObject()
{
    hscpp::GlobalUserData::GetAs<GlobalUserData>()->pObj = this;
}

void HotSwapObject::Update()
{
    if (Hscpp_IsSwapping())
    {
        return;
    }

    std::cout << "Hello, World!" << std::endl;
    std::cout << "Change this line!" << std::endl;
}
