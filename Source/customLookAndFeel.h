/*
  ==============================================================================

    customLookAndFeel.h
    Created: 4 Dec 2020 2:39:09am
    Author:  josh

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class customLookAndFeel : public LookAndFeel_V4
{
public:
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
};