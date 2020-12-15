/*
  ==============================================================================

    Oscillator.h
    Created: 23 May 2020 8:05:11pm
    Author:  Chad Sutherland

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OscModel.h"
#include "CustomLookAndFeel.h"
#include "Knobs.h"

//==============================================================================
/*
*/
class Oscillator    : public Component, ComboBox::Listener, Slider::Listener
{
public:
    Oscillator(BasicSynthAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox *) override;
    void sliderValueChanged(Slider *slider) override;

  private:
    const int border = 8;
    BasicSynthAudioProcessor& processor;
    CustomLookAndFeel customLookAndFeel;

    ComboBox osc1Menu;
    OscModel osc1Model;

    ComboBox osc2Menu;
    OscModel osc2Model;

    Label oscLabel;

    DBKnob level1Knob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> level1Attachment;
    
    DBKnob level2Knob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> level2Attachment;
    
    Slider freq1Knob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> freq1Attachment;
    
    Slider freq2Knob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> freq2Attachment;
    
    Label levelLabel;
    Label freqLabel;


    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> osc1MenuAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> osc2MenuAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
