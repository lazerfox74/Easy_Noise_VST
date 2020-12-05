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

#define NOISEFILT_ID "noiseFilt"
#define NOISEFILT_NAME "Noise Filter"

#define NOISEAMT_ID "noiseAmt"
#define NOISEAMT_NAME "Noise Amount"

#define GAIN_ID "gain"
#define GAIN_NAME "Gain"

#define BITRATE_ID "bitRate"
#define BITRATE_NAME "Bit Rate"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;


//==============================================================================
/**
*/
class EasyNoiseAudioProcessorEditor  : public AudioProcessorEditor, juce::Slider::Listener
{
public:
    EasyNoiseAudioProcessorEditor(EasyNoiseAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~EasyNoiseAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EasyNoiseAudioProcessor& processor;

    //sliders

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EasyNoiseAudioProcessorEditor)

    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Slider noiseFiltSlider;
    std::unique_ptr<SliderAttachment> noiseFiltAttatchment;

    juce::Slider noiseAmtSlider;
    std::unique_ptr<SliderAttachment> noiseAmtAttatchment;

    juce::Slider gainAmtSlider;
    std::unique_ptr<SliderAttachment> gainAmtAttatchment;

    juce::Slider bitRateSlider;
    std::unique_ptr<SliderAttachment> bitRateAttatchment;

    customLookAndFeel otherLookAndFeel;

    Image backGround;

};
