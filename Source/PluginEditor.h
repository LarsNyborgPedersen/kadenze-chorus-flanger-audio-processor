/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class KadenzaPluginDelayAudioProcessorEditor : public AudioProcessorEditor
{
public:
    KadenzaPluginDelayAudioProcessorEditor(KadenzaPluginDelayAudioProcessor&);
    ~KadenzaPluginDelayAudioProcessorEditor();

    //==============================================================================
    void paint(Graphics&) override;
    void resized() override;
    void createUI(AudioParameterFloat* parameter, Slider& slider, Label& label, String labelText, int x, int y);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KadenzaPluginDelayAudioProcessor& processor;


    Slider mDryWetSlider;
    Slider mDepthSlider;
    Slider mRateSlider;
    Slider mPhaseOffsetSlider;
    Slider mFeedbackSlider;

    Label mDryWetLabel;
    Label mDepthLabel;
    Label mRateLabel;
    Label mPhaseOffsetLabel;
    Label mFeedbackLabel;

    ComboBox mType;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KadenzaPluginDelayAudioProcessorEditor)
};
