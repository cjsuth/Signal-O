/*
  ==============================================================================

    Filter.h
    Created: 28 May 2020 10:21:16am
    Author:  Chad Sutherland

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"
#include "Knobs.h"

class Filter : public Component, Slider::Listener
{
public:
    Filter(BasicSynthAudioProcessor&);
    ~Filter();
    
    float getFilterType();
    float getCutoff();
    float getRes();

    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider*) override;

private:
    const int ctrlBoxHeight = 80;
    const int border = 8;
    
    BasicSynthAudioProcessor& processor;
    CustomLookAndFeel customLookAndFeel;
    
    //EnvelopeModel envModel;
    
    ComboBox filterMenu;
    Label filterLabel;
    HZKnob cutoffKnob;
    Label cutoffLabel;
    Slider resKnob;
    Label resLabel;
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterMenuAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> resAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};

