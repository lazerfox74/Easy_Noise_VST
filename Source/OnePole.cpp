/*
  ==============================================================================

    OnePole.cpp
    Created: 4 Dec 2020 6:41:30am
    Author:  josh

  ==============================================================================
*/

#include "OnePole.h"

float myOnePole::process(float in, float damp)
{
    int a = damp;
    int b = 1 - damp;
    return z = (in * a) + (z * b);
}
