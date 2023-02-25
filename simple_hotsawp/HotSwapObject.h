//
// Created by Admin on 2023/2/25.
//

#pragma once

#include "hscpp/module/Tracker.h"

class HotSwapObject
{
    HSCPP_TRACK(HotSwapObject, "HotSwapObject");

public:
    hscpp_virtual ~HotSwapObject() = default;
    HotSwapObject();
    hscpp_virtual void Update();
};


