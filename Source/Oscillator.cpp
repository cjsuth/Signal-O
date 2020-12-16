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
Oscillator::Oscillator(BasicSynthAudioProcessor& p, String name) :
    processor(p), oscModel(1)
{
    String varname = name.removeCharacters(" ").toLowerCase();
    setOpaque(true);
    setSize(240, 200);

    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Triangle", 2);
    oscMenu.addItem("Saw", 3);
    oscMenu.addItem("Square", 4);
    addAndMakeVisible(&oscMenu);
    // oscMenu.setComponentID(name);
    oscMenu.setJustificationType(Justification::centred);
    oscMenu.setSelectedId(1);
    oscMenu.addListener(this);
    menuAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.tree, varname + "wavetype", oscMenu);
    oscLabel.setText (name, dontSendNotification);
    oscLabel.setFont(Font(16));
    oscLabel.setJustificationType(Justification::left);
    oscLabel.attachToComponent(&oscMenu, true);

    //levelKnob config
    levelKnob.setLookAndFeel(&customLookAndFeel);
    levelKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    levelKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    // levelKnob.setSize(getWidth()/4,72);
    addAndMakeVisible(&levelKnob);
    levelKnob.addListener(this);
    levelAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, varname + "level", levelKnob);
    levelKnob.setNumDecimalPlacesToDisplay(2);
    levelLabel.setText ("Level", dontSendNotification);
    levelLabel.setFont(Font(10));
    levelLabel.setJustificationType(Justification::centred);
    levelLabel.attachToComponent(&levelKnob, false);


    //octaveKnob config
    octaveKnob.setLookAndFeel(&customLookAndFeel);
    octaveKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    octaveKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    // octaveKnob.setSize(getWidth()/4,72);
    addAndMakeVisible(&octaveKnob);
    octaveKnob.addListener(this);
    octaveAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, varname + "octave", octaveKnob);
    octaveKnob.setNumDecimalPlacesToDisplay(1);
    octaveLabel.setText ("Octave", dontSendNotification);
    octaveLabel.setFont(Font(10));
    octaveLabel.setJustificationType(Justification::centred);
    octaveLabel.attachToComponent(&octaveKnob, false);

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
    Rectangle<int> area = getLocalBounds().reduced(border);
    auto top = area.removeFromTop(100);
    oscMenu.setBounds(top.removeFromTop(30).removeFromRight(170));
    top.removeFromTop(border);
    oscModel.setBounds(top);

    auto knobWidth = area.getWidth() / 3;
    area.removeFromTop(15);
    levelKnob.setBounds(area.removeFromLeft(knobWidth).reduced(4));
    octaveKnob.setBounds(area.removeFromLeft(knobWidth).reduced(4));
}

void Oscillator::comboBoxChanged(ComboBox* combo)
{
    oscModel.updateWave(combo->getSelectedId());
}

void Oscillator::sliderValueChanged(Slider* slider)
{

}