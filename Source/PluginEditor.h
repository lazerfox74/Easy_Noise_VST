/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "customLookAndFeel.h"

//IDS for my strings used in the AudioProcessorValueTreeState object

#define NOISEFILT_ID "noiseFilt"
#define NOISEFILT_NAME "Noise Filter"

#define NOISEAMT_ID "noiseAmt"
#define NOISEAMT_NAME "Noise Amount"

#define GAIN_ID "gain"
#define GAIN_NAME "Gain"

#define BITRATE_ID "bitRate"
#define BITRATE_NAME "Bit Rate"

//types of AudioProcessorValueTree Objects

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;


//==============================================================================
/**
*/
class EasyNoiseAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    //feeding my editor reference to the processor and value tree when constructed
    EasyNoiseAudioProcessorEditor(EasyNoiseAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~EasyNoiseAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EasyNoiseAudioProcessor& processor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EasyNoiseAudioProcessorEditor)

    //reference to AudioProcessorValueTreeState  so it can be set to the valueTree in the plugin processor when constructed

    juce::AudioProcessorValueTreeState& valueTreeState;

    //Sliders and slider attatchments
    juce::Slider noiseFiltSlider;
    std::unique_ptr<SliderAttachment> noiseFiltAttatchment;

    juce::Slider noiseAmtSlider;
    std::unique_ptr<SliderAttachment> noiseAmtAttatchment;

    juce::Slider gainAmtSlider;
    std::unique_ptr<SliderAttachment> gainAmtAttatchment;

    juce::Slider bitRateSlider;
    std::unique_ptr<SliderAttachment> bitRateAttatchment;
    //my custom look and feel class
    customLookAndFeel otherLookAndFeel;
    //image for use in the background
    Image backGround;

};
