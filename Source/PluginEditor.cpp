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
: AudioProcessorEditor (&p), processor (p), envGUI(p), osc1GUI(p, "Osc 1"), osc2GUI(p, "Osc 2"), filterGUI(p), gainGUI(p)
{
    setOpaque (true);
    setSize (488, 524);

    addAndMakeVisible(&osc1GUI);
    addAndMakeVisible(&osc2GUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGUI);
    addAndMakeVisible(&gainGUI);
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
    auto top = area.removeFromTop(osc1GUI.getHeight());
    osc1GUI.setBounds(top.removeFromLeft(osc1GUI.getWidth()));
    top.removeFromLeft(border);
    osc2GUI.setBounds(top);
    area.removeFromTop(border);
    envGUI.setBounds(area.removeFromTop(envGUI.getHeight()).removeFromLeft(envGUI.getWidth()));
    area.removeFromTop(border);
    filterGUI.setBounds(area.removeFromLeft(filterGUI.getWidth()));
    area.removeFromLeft(border);
    gainGUI.setBounds(area);
}
