/*
  ==============================================================================

    customLookAndFeel.cpp
    Created: 4 Dec 2020 2:39:09am
    Author:  josh

  ==============================================================================
*/

#include "customLookAndFeel.h"
//draw my rotary slider
void customLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    auto radius = jmin(width / 2, height / 2) -20.0f;
    auto centreX = x + width * 0.5f;
    auto centreY = y + height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

    {
        Path backGroundArc;
        g.setColour(juce::Colour(180, 180, 180));
        g.setOpacity(0.5);
        backGroundArc.addArc(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, true);
        g.strokePath(backGroundArc, PathStrokeType(20.0f));
    }
    {
        Path filledArc;
        g.setColour(juce::Colour(0, 0, 0));
        g.setOpacity(1.0);
        filledArc.addArc(rx, ry, rw, rw, rotaryStartAngle, angle, true);
        g.strokePath(filledArc,PathStrokeType(20.0f));
    }
}