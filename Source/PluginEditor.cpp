/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KadenzaPluginDelayAudioProcessorEditor::KadenzaPluginDelayAudioProcessorEditor(KadenzaPluginDelayAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    setSize(800, 200);

    auto& params = processor.getParameters();

    //Adding sliders
    AudioParameterFloat* dryWetParameter = (AudioParameterFloat*)params.getUnchecked(0);
    createUI(dryWetParameter, mDryWetSlider, mDryWetLabel, "Dry/Wet", 100, 0);
    AudioParameterFloat* mPhaseOffsetParameter = (AudioParameterFloat*)params.getUnchecked(3);
    createUI(mPhaseOffsetParameter, mPhaseOffsetSlider, mPhaseOffsetLabel, "Phase", 300, 0);
    AudioParameterFloat* mDepthParameter = (AudioParameterFloat*)params.getUnchecked(1);
    createUI(mDepthParameter, mDepthSlider, mDepthLabel, "Depth", 100, 100);
    AudioParameterFloat* mRateParameter = (AudioParameterFloat*)params.getUnchecked(2);
    createUI(mRateParameter, mRateSlider, mRateLabel, "Rate", 300, 100);
    AudioParameterFloat* mfeedbackParameter = (AudioParameterFloat*)params.getUnchecked(4);
    createUI(mfeedbackParameter, mFeedbackSlider, mFeedbackLabel, "Feedback", 500, 100);

    //Adding combobox
    AudioParameterInt* typeParameter = (AudioParameterInt*)params.getUnchecked(5);
    mType.setBounds(500, 50, 100, 20);
    mType.addItem("Chorus", 1);
    mType.addItem("Flanger", 2);
    addAndMakeVisible(mType);

    mType.onChange  = [this, typeParameter] {
        typeParameter->beginChangeGesture();
    *typeParameter = mType.getSelectedItemIndex();
    typeParameter->endChangeGesture();
    };

    mType.setSelectedItemIndex(*typeParameter);
}

void KadenzaPluginDelayAudioProcessorEditor::createUI(AudioParameterFloat* parameter, Slider &slider, Label &label, String labelText, int x, int y)
{
    auto& params = processor.getParameters();

    slider.setBounds(x, y, 100, 100);
    slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    slider.setRange(parameter->range.start, parameter->range.end);
    slider.setValue(*parameter);
    addAndMakeVisible(slider);

    addAndMakeVisible(label);
    label.setText(labelText, dontSendNotification);
    label.setCentreRelative(0.5f, 0.5f);
    label.attachToComponent(&slider, true);

    slider.onValueChange = [this, parameter, &slider] { *parameter = slider.getValue(); };
    slider.onDragStart = [parameter] {parameter->beginChangeGesture();};
    slider.onDragEnd = [parameter] {parameter->endChangeGesture();};
}



KadenzaPluginDelayAudioProcessorEditor::~KadenzaPluginDelayAudioProcessorEditor()
{
}

//==============================================================================
void KadenzaPluginDelayAudioProcessorEditor::paint(Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));


    /*g.setColour(Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Hello World!", getLocalBounds(), Justification::centred, 1);*/
}

void KadenzaPluginDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
