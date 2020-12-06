/*
  ==============================================================================

    customLookAndFeel.h
    Created: 4 Dec 2020 2:39:09am
    Author:  josh

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
//custom look and feel class for drawing the dials in my UI
class customLookAndFeel : public LookAndFeel_V4
{
public:
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
};