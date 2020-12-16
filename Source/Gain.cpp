/*
  ==============================================================================

    Gain.cpp
    Created: 16 Dec 2020 12:25:05am
    Author:  Chad Sutherland

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Gain.h"

//==============================================================================
Gain::Gain(BasicSynthAudioProcessor& p) :
    processor(p)
{
    setOpaque(true);
    setSize(240, 200);

    //gainKnob config
    gainKnob.setLookAndFeel(&customLookAndFeel);
    gainKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    gainKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(&gainKnob);
    gainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "gain", gainKnob);
    gainKnob.setNumDecimalPlacesToDisplay(2);
    gainLabel.setText ("Gain", dontSendNotification);
    gainLabel.setFont(Font(10));
    gainLabel.setJustificationType(Justification::centred);
    gainLabel.attachToComponent(&gainKnob, false);
}

Gain::~Gain()
{
}


void Gain::paint (Graphics& g)
{
    g.fillAll (Colours::darkgrey);
    g.setColour(getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillRoundedRectangle(getLocalBounds().reduced(2).toFloat(), 5.0f);
    g.setColour(Colours::white);
    g.drawRoundedRectangle(getLocalBounds().reduced(2).toFloat(), 5.0f, 3.0f);
}

void Gain::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(border);
    gainKnob.setBounds(area.reduced(4));
}