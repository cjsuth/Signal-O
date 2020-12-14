/*
  ==============================================================================

    Oscillator.cpp
    Created: 23 May 2020 8:05:11pm
    Author:  Chad Sutherland

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(BasicSynthAudioProcessor& p) :
    processor(p), oscModel(1)
{
    setOpaque(true);
    setSize(240, 160);

    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Triangle", 2);
    oscMenu.addItem("Saw", 3);
    oscMenu.addItem("Square", 4);

    oscMenu.setJustificationType(Justification::centred);
    oscMenu.setSelectedId(1);
    oscMenu.addListener(this);

    oscLabel.setText ("waveform", dontSendNotification);
    oscLabel.setFont(Font(16));
    oscLabel.setJustificationType(Justification::left);
    oscLabel.attachToComponent(&oscMenu, true);

    //Add to editor
    addAndMakeVisible(&oscMenu);
    oscMenuAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.tree, "wavetype", oscMenu);

    oscModel.updateWave(oscMenu.getSelectedId());
    addAndMakeVisible(&oscModel);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
    g.fillAll (Colours::darkgrey);
    g.setColour(getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillRoundedRectangle(getLocalBounds().reduced(2).toFloat(), 5.0f);
    g.setColour(Colours::white);
    g.drawRoundedRectangle(getLocalBounds().reduced(2).toFloat(), 5.0f, 3.0f);
}

void Oscillator::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    Rectangle<int> area = getLocalBounds().reduced(border);
    oscMenu.setBounds(area.removeFromTop(25).removeFromRight(150));
    area.removeFromTop(10);
    oscModel.setBounds(area);
}

void Oscillator::comboBoxChanged(ComboBox* combo)
{
    oscModel.updateWave(combo->getSelectedId());
}