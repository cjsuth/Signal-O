/*
  ==============================================================================

    Gain.h
    Created: 16 Dec 2020 12:25:05am
    Author:  Chad Sutherland

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"
#include "Knobs.h"

class Gain : public Component
{
public:
    Gain(BasicSynthAudioProcessor&);
    ~Gain();

    void paint (Graphics&) override;
    void resized() override;

private:
    const int border = 8;
    
    BasicSynthAudioProcessor& processor;
    CustomLookAndFeel customLookAndFeel;
    
    DBKnob gainKnob;
    Label gainLabel;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Gain)
};
