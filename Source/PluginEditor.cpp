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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 200);

    auto& params = processor.getParameters();
    ///////////////////////////////////////////////////////////////////////////////////
    AudioParameterFloat* dryWetParameter = (AudioParameterFloat*)params.getUnchecked(0);

    

    mDryWetSlider.setBounds(100, 0, 100, 100);
    mDryWetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDryWetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDryWetSlider.setRange(dryWetParameter->range.start, dryWetParameter->range.end);
    mDryWetSlider.setValue(*dryWetParameter);
    addAndMakeVisible(mDryWetSlider);

    addAndMakeVisible(mDryWetLabel);
    mDryWetLabel.setText("Dry/Wet", dontSendNotification);
    mDryWetLabel.setCentreRelative(0.5f, 0.5f);
    mDryWetLabel.attachToComponent(&mDryWetSlider, true);

    mDryWetSlider.onValueChange = [this, dryWetParameter] { *dryWetParameter = mDryWetSlider.getValue(); };
    mDryWetSlider.onDragStart = [dryWetParameter] {dryWetParameter->beginChangeGesture();};
    mDryWetSlider.onDragEnd = [dryWetParameter] {dryWetParameter->endChangeGesture();};

    ///////////////////////////////////////////////////////////////////////////////////
    AudioParameterFloat* mPhaseOffsetParameter = (AudioParameterFloat*)params.getUnchecked(3);


    mPhaseOffsetSlider.setBounds(300, 0, 100, 100);
    mPhaseOffsetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mPhaseOffsetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mPhaseOffsetSlider.setRange(dryWetParameter->range.start, dryWetParameter->range.end);
    mPhaseOffsetSlider.setValue(*dryWetParameter);
    addAndMakeVisible(mPhaseOffsetSlider);

    addAndMakeVisible(mPhaseOffsetLabel);
    mPhaseOffsetLabel.setText("Phase offset", dontSendNotification);
    mPhaseOffsetLabel.setCentreRelative(0.5f, 0.5f);
    mPhaseOffsetLabel.attachToComponent(&mPhaseOffsetSlider, true);

    mPhaseOffsetSlider.onValueChange = [this, mPhaseOffsetParameter] { *mPhaseOffsetParameter = mPhaseOffsetSlider.getValue(); };
    mPhaseOffsetSlider.onDragStart = [mPhaseOffsetParameter] {mPhaseOffsetParameter->beginChangeGesture();};
    mPhaseOffsetSlider.onDragEnd = [mPhaseOffsetParameter] {mPhaseOffsetParameter->endChangeGesture();};


    ///////////////////////////////////////////////////////////////////////////////////
    AudioParameterFloat* mDepthParameter = (AudioParameterFloat*)params.getUnchecked(1);


    mDepthSlider.setBounds(100, 100, 100, 100);
    mDepthSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDepthSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDepthSlider.setRange(mDepthParameter->range.start, mDepthParameter->range.end);
    mDepthSlider.setValue(*mDepthParameter);
    addAndMakeVisible(mDepthSlider);

    addAndMakeVisible(mDepthLabel);
    mDepthLabel.setText("Depth", dontSendNotification);
    mDepthLabel.setCentreRelative(0.5f, 0.5f);
    mDepthLabel.attachToComponent(&mDepthSlider, true);

    mDepthSlider.onValueChange = [this, mDepthParameter] { *mDepthParameter = mDepthSlider.getValue(); };
    mDepthSlider.onDragStart = [mDepthParameter] {mDepthParameter->beginChangeGesture();};
    mDepthSlider.onDragEnd = [mDepthParameter] {mDepthParameter->endChangeGesture();};

    ///////////////////////////////////////////////////////////////////////////////////
    AudioParameterFloat* mRateParameter = (AudioParameterFloat*)params.getUnchecked(2);


    mRateSlider.setBounds(300, 100, 100, 100);
    mRateSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mRateSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mRateSlider.setRange(mRateParameter->range.start, mRateParameter->range.end);
    mRateSlider.setValue(*mRateParameter);
    addAndMakeVisible(mRateSlider);


    addAndMakeVisible(mRateLabel);
    mRateLabel.setText("Rate", dontSendNotification);
    mRateLabel.setCentreRelative(0.5f, 0.5f);
    mRateLabel.attachToComponent(&mRateSlider, true);

    mRateSlider.onValueChange = [this, mRateParameter] { *mRateParameter = mRateSlider.getValue(); };
    mRateSlider.onDragStart = [mRateParameter] {mRateParameter->beginChangeGesture();};
    mRateSlider.onDragEnd = [mRateParameter] {mRateParameter->endChangeGesture();};

   


   

    //////////////////////////////////////////////////////////////////////////////////////
    AudioParameterFloat* feedbackParameter = (AudioParameterFloat*)params.getUnchecked(4);

    mFeedbackSlider.setBounds(500, 100, 100, 100);
    mFeedbackSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mFeedbackSlider.setRange(feedbackParameter->range.start, feedbackParameter->range.end);
    mFeedbackSlider.setValue(*feedbackParameter);
    addAndMakeVisible(mFeedbackSlider);

    addAndMakeVisible(mFeedbackLabel);
    mFeedbackLabel.setText("Feedback", dontSendNotification);
    mFeedbackLabel.setCentreRelative(0.5f, 0.5f);
    mFeedbackLabel.attachToComponent(&mFeedbackSlider, true);

    mFeedbackSlider.onValueChange = [this, feedbackParameter] { *feedbackParameter = mFeedbackSlider.getValue(); };
    mFeedbackSlider.onDragStart = [feedbackParameter] {feedbackParameter->beginChangeGesture();};
    mFeedbackSlider.onDragEnd = [feedbackParameter] {feedbackParameter->endChangeGesture();};

    

    //////////////////////////////////////////////////////////////////////////////////////
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

    /*AudioParameterFloat* delayTimeParameter = (AudioParameterFloat*)params.getUnchecked(2);

    mDelayTimeSlider.setBounds(200, 0, 100, 100);
    mDelayTimeSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTimeSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDelayTimeSlider.setRange(delayTimeParameter->range.start, delayTimeParameter->range.end);
    mDelayTimeSlider.setValue(*delayTimeParameter);
    addAndMakeVisible(mDelayTimeSlider);

    mDelayTimeSlider.onValueChange = [this, delayTimeParameter] { *delayTimeParameter = mDelayTimeSlider.getValue(); };
    mDelayTimeSlider.onDragStart = [delayTimeParameter] {delayTimeParameter->beginChangeGesture();};
    mDelayTimeSlider.onDragEnd = [delayTimeParameter] {delayTimeParameter->endChangeGesture();};*/

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
