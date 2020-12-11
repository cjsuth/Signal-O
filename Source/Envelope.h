/*
  ==============================================================================

    Envelope.h
    Created: 26 May 2020 11:20:39am
    Author:  Chad Sutherland

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "EnvelopeModel.h"
#include "CustomLookAndFeel.h"
#include "Knobs.h"

class Envelope : public Component, Slider::Listener
{
public:
    Envelope(BasicSynthAudioProcessor&);
    ~Envelope();
    
    float getAttack();
    float getDecay();
    float getSustain();
    float getRelease();

    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider*) override;

private:
    //const int ctrlBoxHeight = 80;
    const int border = 8;
    
    float knobWidth;
    
    BasicSynthAudioProcessor& processor;
    CustomLookAndFeel customLookAndFeel;
    
    EnvelopeModel envModel;
    
    TimeKnob attackKnob;
    Label attackLabel;
    TimeKnob decayKnob;
    Label decayLabel;
    DBKnob sustainKnob;
    Label sustainLabel;
    TimeKnob releaseKnob;
    Label releaseLabel;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};

