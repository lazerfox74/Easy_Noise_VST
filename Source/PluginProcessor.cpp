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

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

  
    float* Lchannel = buffer.getWritePointer(0);
    float* Rchannel = buffer.getWritePointer(1);

    float* chanelPointArray[2];

    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        if ((bitRateCount % (int)floor(*bitRatePointer)) == 0)
        {
            noise = onePole(((rand() % 200) / 100.0f - 1.0f), *noiseFiltPointer) * *noiseAmtPointer;
            bitRateCount = 0;
        }

        for (int channel = 0; channel < totalNumInputChannels; channel++)
        {
            chanelPointArray[channel] = buffer.getWritePointer(channel);
            float newSample{ (chanelPointArray[channel][sample] * *gainAmtPointer) * (1 + noise)};
            //hard clipping
            if (newSample > 1.0f) { newSample = 1.0; } else if (newSample < -1.0f) { newSample = -1.0f;}

            chanelPointArray[channel][sample] = newSample;
        }

        bitRateCount++;
    }


    //for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    //{

    //    Lchannel[sample] = Lchannel[sample] * (1 + noise);
    //    Rchannel[sample] = Rchannel[sample] * (1 + noise);
    //}


    //for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //{
    //    float* channelData = buffer.getWritePointer (channel);

    //    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    //    {
    //        channelData[sample] = 
    //    }
    //}

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
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ValueTree state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void EasyNoiseAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

float EasyNoiseAudioProcessor::onePole(float in,float damp)
{
    float a = damp;
    float b = 1 -damp;
    z = (in * a) + (z * b);
    return z;
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EasyNoiseAudioProcessor();
}


