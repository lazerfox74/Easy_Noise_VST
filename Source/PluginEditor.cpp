/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EasyNoiseAudioProcessorEditor::EasyNoiseAudioProcessorEditor (EasyNoiseAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);

    //Noise Filter Slider
    noiseFiltAttatchment.reset(new SliderAttachment(valueTreeState, NOISEFILT_ID, noiseFiltSlider));
    noiseFiltSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    noiseFiltSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    noiseFiltSlider.setLookAndFeel(&otherLookAndFeel);
    noiseFiltSlider.setSkewFactorFromMidPoint(0.1f);
    addAndMakeVisible(noiseFiltSlider);

    //Noise Amount Slider
    noiseAmtAttatchment.reset(new SliderAttachment(valueTreeState, NOISEAMT_ID, noiseAmtSlider));
    noiseAmtSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    noiseAmtSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    noiseAmtSlider.setLookAndFeel(&otherLookAndFeel);
    noiseAmtSlider.setSkewFactorFromMidPoint(0.5f);
    addAndMakeVisible(noiseAmtSlider);

    //Gain Amount Slider
    gainAmtAttatchment.reset(new SliderAttachment(valueTreeState, GAIN_ID, gainAmtSlider));
    gainAmtSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainAmtSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    gainAmtSlider.setLookAndFeel(&otherLookAndFeel);
    gainAmtSlider.setSkewFactorFromMidPoint(2.0f);
    addAndMakeVisible(gainAmtSlider);

    //But Rate Slider
    bitRateAttatchment.reset(new SliderAttachment(valueTreeState, BITRATE_ID, bitRateSlider));
    bitRateSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    bitRateSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    bitRateSlider.setLookAndFeel(&otherLookAndFeel);
    bitRateSlider.setSkewFactorFromMidPoint(2.0f);
    //bitRateSlider.setSkewFactorFromMidPoint(1);
    addAndMakeVisible(bitRateSlider);

    //background image
    backGround = ImageCache::getFromMemory(BinaryData::easynoiseBackground_png, BinaryData::easynoiseBackground_pngSize);

}

EasyNoiseAudioProcessorEditor::~EasyNoiseAudioProcessorEditor()
{
}

//==============================================================================
void EasyNoiseAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(juce::Colour(255, 255, 255));

    g.drawImageAt(backGround, 0, 0);
}

void EasyNoiseAudioProcessorEditor::resized()
{
    gainAmtSlider.setBounds(0, 100, 150, 150);
    bitRateSlider.setBounds(150, 100, 150, 150);

    noiseFiltSlider.setBounds(300, 100,150 , 150);
    noiseAmtSlider.setBounds(450, 100, 150, 150);

}
