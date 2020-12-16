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
    Oscillator(BasicSynthAudioProcessor&, String name);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox *) override;
    void sliderValueChanged(Slider *slider) override;

  private:
    const int border = 8;
    BasicSynthAudioProcessor& processor;
    CustomLookAndFeel customLookAndFeel;

    ComboBox oscMenu;
    Label oscLabel;
    OscModel oscModel;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> menuAttachment;

    DBKnob levelKnob;
    Label levelLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> levelAttachment;
    
    Slider octaveKnob;
    Label octaveLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> octaveAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
