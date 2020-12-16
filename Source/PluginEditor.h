/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Envelope.h"
#include "Oscillator.h"
#include "Filter.h"
#include "Gain.h"
//==============================================================================
/**
*/
class BasicSynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    BasicSynthAudioProcessorEditor (BasicSynthAudioProcessor&);
    ~BasicSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    BasicSynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicSynthAudioProcessorEditor);

    Envelope envGUI;
    Oscillator osc1GUI;
    Oscillator osc2GUI;
    Filter filterGUI;
    Gain gainGUI;
};
