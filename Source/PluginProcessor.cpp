/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <fstream>
#include <iostream>
#include <windows.h>

//==============================================================================
KadenzaPluginDelayAudioProcessor::KadenzaPluginDelayAudioProcessor()
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
    //I've created these myself. Not part of example:
    outfile.open("hey.txt");
    outfile << "Hey babe" << std::endl;
    highest = 0;
    lowest = 0;




    addParameter(mDryWetParameter = new AudioParameterFloat("drywet", "Dry Wet", 0, 1, 0.5));
    addParameter(mDepthParameter = new AudioParameterFloat("depth", "Depth", 0, 1, 0.5));
    addParameter(mRateParameter = new AudioParameterFloat("rate", "Rate", 0.1f, 20.f, 10.f));
    addParameter(mPhaseOffsetParameter = new AudioParameterFloat("phaseoffset", "Phase Offset", 0.0f, 1.f, 0.f));
    addParameter(mFeedbackParameter = new AudioParameterFloat("feedback", "Feedback", 0, 0.98, 0.5));
    addParameter(mTypeParameter = new AudioParameterInt("type", "Type", 0, 1, 0));

    mDelayTimeSmoothed = 0;
    mCircularBufferLeft = nullptr;
    mCircularBufferRight = nullptr;
    mCircularBufferWriteHead = 0;
    mCircularBufferLenght = 0;
    mDelayTimeInSamples = 0;
    mDelayReadHead = 0;

    mFeedbackLeft = 0;
    mFeedbackRight = 0;

    mLFOPhase = 0;

}

KadenzaPluginDelayAudioProcessor::~KadenzaPluginDelayAudioProcessor()
{
    if (mCircularBufferLeft != nullptr)
    {
        delete[] mCircularBufferLeft;
        mCircularBufferLeft = nullptr;
    }

    if (mCircularBufferRight != nullptr)
    {
        delete[] mCircularBufferRight;
        mCircularBufferRight = nullptr;
    }
}

//==============================================================================
const String KadenzaPluginDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KadenzaPluginDelayAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool KadenzaPluginDelayAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool KadenzaPluginDelayAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double KadenzaPluginDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KadenzaPluginDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KadenzaPluginDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KadenzaPluginDelayAudioProcessor::setCurrentProgram(int index)
{
}

const String KadenzaPluginDelayAudioProcessor::getProgramName(int index)
{
    return {};
}

void KadenzaPluginDelayAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void KadenzaPluginDelayAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    mDelayTimeSmoothed = 1;
    mLFOPhase = 0;

    //2 is the amount of seconds
    mCircularBufferLenght = sampleRate * 2;


    if (mCircularBufferLeft == nullptr)
    {
        mCircularBufferLeft = new float[mCircularBufferLenght];
    }

    zeromem(mCircularBufferLeft, mCircularBufferLenght * sizeof(float));

    if (mCircularBufferRight == nullptr)
    {
        mCircularBufferRight = new float[mCircularBufferLenght];
    }

    zeromem(mCircularBufferRight, mCircularBufferLenght * sizeof(float));

    mCircularBufferWriteHead = 0;



    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void KadenzaPluginDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KadenzaPluginDelayAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
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

void KadenzaPluginDelayAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());



    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    //float highest = 0;

    std::cout << "This is printed to console";

    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        float M_PI = 3.1415926535897932384626433832795028841971693993;

        float lfoOut = sin(2 * M_PI * mLFOPhase);

        mLFOPhase = *mRateParameter * getSampleRate();

        if (mLFOPhase > 1) {
            mLFOPhase -= 1;
        }

        float lfoOutMapped = jmap(lfoOut, -1.0f, 1.0f, 0.005f, 0.03f);

        /*if (leftChannel[i] > highest) {
            highest = leftChannel[i];
            outfile << std::to_string(highest) << std::endl;
            outfile << std::to_string(lowest) << std::endl;
        }
        if (leftChannel[i] < lowest) {
            lowest = leftChannel[i];
            outfile << std::to_string(highest) << std::endl;
            outfile << std::to_string(lowest) << std::endl;
        }

        float maxValue = 0.1;*/

        /*if (leftChannel[i] > maxValue) {
            leftChannel[i] = maxValue + 0.5 * (leftChannel[i] - maxValue);
        }
        if (leftChannel[i] < -maxValue) {
            leftChannel[i] = -maxValue - 0.5 * (leftChannel[i] - maxValue);;
        }

        if (rightChannel[i] > maxValue) {
            rightChannel[i] = maxValue + 0.5 * (leftChannel[i] - maxValue);;
        }
        if (rightChannel[i] < -maxValue) {
            rightChannel[i] = -maxValue - 0.5 * (leftChannel[i] - maxValue);;
        }

        leftChannel[i] *= 1/ maxValue;
        rightChannel[i] *= 1/ maxValue;*/


        //Not sure if it should be mRateParameter or not...
        mDelayTimeSmoothed = mDelayTimeSmoothed - 0.001 * (mDelayTimeSmoothed - lfoOutMapped);
        mDelayTimeInSamples = getSampleRate() * mDelayTimeSmoothed;

        mCircularBufferLeft[mCircularBufferWriteHead] = leftChannel[i] + mFeedbackLeft;
        mCircularBufferRight[mCircularBufferWriteHead] = rightChannel[i] + mFeedbackRight;

        mDelayReadHead = mCircularBufferWriteHead - mDelayTimeInSamples;

        if (mDelayReadHead < 0)
        {
            mDelayReadHead += mCircularBufferLenght;
        }

        int readHead_x = (int)mDelayReadHead;
        int readHead_x1 = (int)mDelayReadHead + 1;
        float readheadFloat = mDelayReadHead - readHead_x;

        if (readHead_x1 >= mCircularBufferLenght)
        {
            readHead_x1 -= mCircularBufferLenght;
        }


        float delay_sample_left = lin_interp(mCircularBufferLeft[readHead_x], mCircularBufferLeft[readHead_x1], readheadFloat);
        float delay_sample_right = lin_interp(mCircularBufferRight[readHead_x], mCircularBufferRight[readHead_x1], readheadFloat);

        mFeedbackLeft = delay_sample_left * *mFeedbackParameter;
        mFeedbackRight = delay_sample_right * *mFeedbackParameter;

        mCircularBufferWriteHead++;

        buffer.setSample(0, i, buffer.getSample(0, i) * (1 - *mDryWetParameter) + delay_sample_left * *mDryWetParameter);
        buffer.setSample(1, i, buffer.getSample(1, i) * (1 - *mDryWetParameter) + delay_sample_right * *mDryWetParameter);



        if (mCircularBufferWriteHead > mCircularBufferLenght)
        {
            mCircularBufferWriteHead = 0;
        }
    }
}

//==============================================================================
bool KadenzaPluginDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* KadenzaPluginDelayAudioProcessor::createEditor()
{
    return new KadenzaPluginDelayAudioProcessorEditor(*this);
}

//==============================================================================
void KadenzaPluginDelayAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void KadenzaPluginDelayAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KadenzaPluginDelayAudioProcessor();
}

float KadenzaPluginDelayAudioProcessor::lin_interp(float sample_x, float sample_x1, float inPhase)
{
    return (1 - inPhase) * sample_x + inPhase * sample_x1;
}
