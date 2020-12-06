/*
  ==============================================================================

    OnePole.h
    Created: 4 Dec 2020 6:41:30am
    Author:  josh

  ==============================================================================
*/

#pragma once
//class for my one pole filter
class myOnePole
{
public:
    float process(float in, float damp);

private:
    //value for storing the previous value of my onePole filter
    float z;
};
