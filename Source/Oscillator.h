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

//==============================================================================
/*
*/
class Oscillator    : public Component, ComboBox::Listener
{
public:
    Oscillator(BasicSynthAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox *) override;

  private:
    const int border = 8;
    BasicSynthAudioProcessor& processor;

    ComboBox oscMenu;
    OscModel oscModel;
    Label oscLabel;

    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> oscMenuAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
