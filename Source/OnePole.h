/*
  ==============================================================================

    OnePole.h
    Created: 4 Dec 2020 6:41:30am
    Author:  josh

  ==============================================================================
*/

#pragma once

class myOnePole
{
public:
    float process(float in, float damp);

private:
    float z;
};
