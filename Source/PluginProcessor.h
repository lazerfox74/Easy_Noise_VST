/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "OnePole.h"

//==============================================================================
/**
*/
class EasyNoiseAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    EasyNoiseAudioProcessor();
    ~EasyNoiseAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EasyNoiseAudioProcessor)

    juce::AudioProcessorValueTreeState parameters;
    //pointers that will be set to the values in my XML file
    std::atomic<float>* noiseFiltPointer = nullptr;
    std::atomic<float>* noiseAmtPointer = nullptr;
    std::atomic<float>* gainAmtPointer = nullptr;
    std::atomic<float>* bitRatePointer = nullptr;

    //One pole function for dampening the noise
    float onePole(float in,float damp);
    //noise float and z float for storing the previous value from the one pole
    float z{ 0.0f }, noise{0.0f};
    int bitRateCount{1};
};
