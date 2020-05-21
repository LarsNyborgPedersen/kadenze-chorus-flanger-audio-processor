/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <fstream>
#include <iostream>

//==============================================================================
/**
*/
class KadenzaPluginDelayAudioProcessor : public AudioProcessor
{
public:
    //==============================================================================
    KadenzaPluginDelayAudioProcessor();
    ~KadenzaPluginDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(AudioBuffer<float>&, MidiBuffer&) override;

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
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    void changeProgramName(int index, const String& newName) override;

    //==============================================================================
    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    float lin_interp(float sample_x, float sample_x1, float inPhase);

private:
    //I've created these myself. Not part of example:
    std::ofstream outfile;
    float highest;
    float lowest;
    
    
    
    float mLFOPhase;
    


    AudioParameterFloat* mDryWetParameter;
    AudioParameterFloat* mDepthParameter;
    AudioParameterFloat* mRateParameter;
    AudioParameterFloat* mPhaseOffsetParameter;
    AudioParameterFloat* mFeedbackParameter;
    AudioParameterInt* mTypeParameter;

    float mFeedbackLeft;
    float mFeedbackRight;

    int mCircularBufferWriteHead;
    int mCircularBufferLenght;
    float* mCircularBufferLeft;
    float* mCircularBufferRight;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KadenzaPluginDelayAudioProcessor)
};
