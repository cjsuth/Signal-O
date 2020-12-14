/*
  ==============================================================================

    Envelope.cpp
    Created: 26 May 2020 11:20:39am
    Author:  Chad Sutherland

  ==============================================================================
*/

#include "Envelope.h"
#include <JuceHeader.h>

//==============================================================================
Envelope::Envelope(BasicSynthAudioProcessor& p) :
    processor(p), envModel(0,0,0,0)
{
    setOpaque (true);
    setSize(240, 180);
    
    //attackKnob config
    attackKnob.setLookAndFeel(&customLookAndFeel);
    attackKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    attackKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    //attackKnob.setSize(knobWidth, ctrlBoxHeight);
    attackLabel.setText("Attack", dontSendNotification);
    attackLabel.setFont(Font(10));
    attackLabel.setJustificationType(Justification::centred);
    attackLabel.attachToComponent(&attackKnob, false);
    addAndMakeVisible(&attackKnob);
    attackKnob.addListener(this);
    attackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "attack", attackKnob);
    attackKnob.setNumDecimalPlacesToDisplay(2);
    
    //decayKnob config
    decayKnob.setLookAndFeel(&customLookAndFeel);
    decayKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    decayKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    //decayKnob.setSize(knobWidth, ctrlBoxHeight);
    decayLabel.setText ("Decay", dontSendNotification);
    decayLabel.setFont(Font(10));
    decayLabel.setJustificationType(Justification::centred);
    decayLabel.attachToComponent(&decayKnob, false);
    addAndMakeVisible(&decayKnob);
    decayKnob.addListener(this);
    decayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "decay", decayKnob);
    decayKnob.setNumDecimalPlacesToDisplay(2);

    //sustainKnob config
    sustainKnob.setLookAndFeel(&customLookAndFeel);
    sustainKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    sustainKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    //sustainKnob.setSize(knobWidth, ctrlBoxHeight);
    sustainLabel.setText ("Sustain", dontSendNotification);
    sustainLabel.setFont(Font(10));
    sustainLabel.setJustificationType(Justification::centred);
    sustainLabel.attachToComponent(&sustainKnob, false);
    addAndMakeVisible(&sustainKnob);
    sustainKnob.addListener(this);
    sustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "sustain", sustainKnob);
    sustainKnob.setNumDecimalPlacesToDisplay(2);
    
    //releaseKnob config
    releaseKnob.setLookAndFeel(&customLookAndFeel);
    releaseKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    releaseKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    //releaseKnob.setSize(knobWidth, ctrlBoxHeight);
    releaseLabel.setText ("Release", dontSendNotification);
    releaseLabel.setFont(Font(10));
    releaseLabel.setJustificationType(Justification::centred);
    releaseLabel.attachToComponent(&releaseKnob, false);
    addAndMakeVisible(&releaseKnob);
    releaseKnob.addListener(this);
    releaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "release", releaseKnob);
    releaseKnob.setNumDecimalPlacesToDisplay(2);

    envModel.updateNodes(getAttack(), getDecay(), getSustain(), getRelease());
    addAndMakeVisible(&envModel);
    
}

Envelope::~Envelope()
{
}


float Envelope::getAttack()
{
    return attackKnob.getValue();
}

float Envelope::getDecay()
{
    return decayKnob.getValue();
}

float Envelope::getSustain()
{
    return sustainKnob.getValue();
}

float Envelope::getRelease()
{
    return releaseKnob.getValue();
}

void Envelope::paint (Graphics& g)
{
    g.fillAll (Colours::darkgrey);
    g.setColour(getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillRoundedRectangle(getLocalBounds().reduced(2).toFloat(), 5.0f);
    g.setColour(Colours::white);
    g.drawRoundedRectangle(getLocalBounds().reduced(2).toFloat(), 5.0f, 3.0f);
}

void Envelope::resized()
{

    Rectangle<int> area = getLocalBounds().reduced(border);

    envModel.setBounds(area.removeFromTop(envModel.getHeight()));
    area.removeFromTop(16);
    area.reduce(5,5);
    int knobWidth = area.getWidth() / 4;
    attackKnob.setBounds(area.removeFromLeft(knobWidth));
    decayKnob.setBounds(area.removeFromLeft(knobWidth));
    sustainKnob.setBounds(area.removeFromLeft(knobWidth));
    releaseKnob.setBounds(area.removeFromLeft(knobWidth));
}

void Envelope::sliderValueChanged(Slider* slider)
{
    envModel.updateNodes(getAttack(), getDecay(), getSustain(), getRelease());
}
