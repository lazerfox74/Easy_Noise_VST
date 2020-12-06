/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EasyNoiseAudioProcessor::EasyNoiseAudioProcessor()
//setting up my audioProcessorValueTreeSate before the constructor
    : parameters(*this, nullptr, juce::Identifier("easyNoise"),
        {
            std::make_unique<juce::AudioParameterFloat>(NOISEFILT_ID,     // parameterID
                                                        NOISEFILT_NAME,   // parameter name
                                                         0.0f,              // minimum value
                                                         1.0f,              // maximum value
                                                         0.5f),             // default value
            std::make_unique<juce::AudioParameterFloat>(NOISEAMT_ID,      // parameterID
                                                        NOISEAMT_NAME,    // parameter name
                                                         0.0f,
                                                         2.0f,
                                                         0.5f),             // default value
            std::make_unique<juce::AudioParameterFloat>(GAIN_ID,      // parameterID
                                                        GAIN_NAME,    // parameter name
                                                         1.0f,
                                                         5.0f,
                                                         1.0f),             // default value
            std::make_unique<juce::AudioParameterFloat>(BITRATE_ID,      // parameterID
                                                      BITRATE_NAME,    // parameter name
                                                         1.0f,
                                                         60.0f,
                                                         1.0f)             // default value
        })
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    )

#endif
{
    //storing pointers to my paramaters to dereferene them later 
    noiseFiltPointer = parameters.getRawParameterValue(NOISEFILT_ID);
    noiseAmtPointer = parameters.getRawParameterValue(NOISEAMT_ID);
    gainAmtPointer = parameters.getRawParameterValue(GAIN_ID);
    bitRatePointer = parameters.getRawParameterValue(BITRATE_ID);
}

EasyNoiseAudioProcessor::~EasyNoiseAudioProcessor()
{
}

//==============================================================================
const String EasyNoiseAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EasyNoiseAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EasyNoiseAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EasyNoiseAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EasyNoiseAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EasyNoiseAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EasyNoiseAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EasyNoiseAudioProcessor::setCurrentProgram (int index)
{
}

const String EasyNoiseAudioProcessor::getProgramName (int index)
{
    return {};
}

void EasyNoiseAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void EasyNoiseAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void EasyNoiseAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EasyNoiseAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EasyNoiseAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    //array of buffer write pointers for my left and right channels
    float* chanelPointArray[2];

    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        //only generating a new random noise depending on if my bitRateCount modulo my bit rate amount is 0 to reduce bit rate
        if ((bitRateCount % (int)floor(*bitRatePointer)) == 0)
        {   
            //one pole processed random noise
            noise = onePole(((rand() % 200) / 100.0f - 1.0f), *noiseFiltPointer) * *noiseAmtPointer;
            bitRateCount = 0;
        }

        for (int channel = 0; channel < totalNumInputChannels; channel++)
        {
            //taking the input sample and multiplying it by the noise sample for the left and right channels
            chanelPointArray[channel] = buffer.getWritePointer(channel);
            float newSample{ (chanelPointArray[channel][sample] * *gainAmtPointer) * (1 + noise)};

            //hard clipping if sample is above 1/below -1
            if (newSample > 1.0f) { newSample = 1.0; } else if (newSample < -1.0f) { newSample = -1.0f;}

            chanelPointArray[channel][sample] = newSample;
        }

        bitRateCount++;
    }
}

//==============================================================================
bool EasyNoiseAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* EasyNoiseAudioProcessor::createEditor()
{
    return new EasyNoiseAudioProcessorEditor (*this,parameters);
}

//==============================================================================
void EasyNoiseAudioProcessor::getStateInformation (MemoryBlock& destData)
{

    //storing my paramaters to and XML file in meory
    juce::ValueTree state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void EasyNoiseAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //restoring my paramaters based on the XML file in memory
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

float EasyNoiseAudioProcessor::onePole(float in,float damp)
{
    
    //controlling how much the raw signal effects the output of the sound
    int a = damp;
    int b = 1 - damp;
    return z = (in * a) + (z * b);
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EasyNoiseAudioProcessor();
}


