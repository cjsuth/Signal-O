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
    processor(p)
{
    setSize(100,30);
    
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Triangle", 2);
    oscMenu.addItem("Saw", 3);
    oscMenu.addItem("Square", 4);
    
    oscMenu.setJustificationType(Justification::centred);
    oscMenu.setSelectedId(1);

    //Add to editor
    addAndMakeVisible(&oscMenu);
    oscMenuAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.tree, "wavetype", oscMenu);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
}

void Oscillator::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    int border = 4;
    oscMenu.setBounds(getLocalBounds().reduced(border));
    
}
