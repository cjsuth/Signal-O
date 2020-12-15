/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicSynthAudioProcessorEditor::BasicSynthAudioProcessorEditor (BasicSynthAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p), envGUI(p), oscGUI(p), filterGUI(p)
{
    setOpaque (true);
    setSize (488, 512);

    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGUI);
}

BasicSynthAudioProcessorEditor::~BasicSynthAudioProcessorEditor()
{
}

//==============================================================================
void BasicSynthAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::darkgrey);
}

void BasicSynthAudioProcessorEditor::resized()
{
    auto border = 4;
    auto area = getLocalBounds().reduced(border);

    oscGUI.setBounds(area.removeFromTop(oscGUI.getHeight()).removeFromLeft(oscGUI.getWidth()));
    area.removeFromTop(border);
    envGUI.setBounds(area.removeFromTop(envGUI.getHeight()).removeFromLeft(envGUI.getWidth()));
    area.removeFromTop(border);
    filterGUI.setBounds(area.removeFromTop(filterGUI.getHeight()).removeFromLeft(filterGUI.getWidth()));
}
