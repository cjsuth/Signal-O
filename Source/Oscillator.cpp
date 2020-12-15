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
    processor(p), osc1Model(1), osc2Model(1)
{
    setOpaque(true);
    setSize(480, 160);

    osc1Menu.addItem("Sine", 1);
    osc1Menu.addItem("Triangle", 2);
    osc1Menu.addItem("Saw", 3);
    osc1Menu.addItem("Square", 4);

    osc1Menu.setComponentID("osc1");
    osc1Menu.setJustificationType(Justification::centred);
    osc1Menu.setSelectedId(1);
    osc1Menu.addListener(this);

    // osc1Label.setText ("waveform", dontSendNotification);
    // osc1Label.setFont(Font(16));
    // osc1Label.setJustificationType(Justification::left);
    // osc1Label.attachToComponent(&osc1Menu, true);

    //Add to editor
    addAndMakeVisible(&osc1Menu);
    osc1MenuAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.tree, "wavetype1", osc1Menu);

    osc1Model.updateWave(osc1Menu.getSelectedId());
    addAndMakeVisible(&osc1Model);

    osc2Menu.addItem("Sine", 1);
    osc2Menu.addItem("Triangle", 2);
    osc2Menu.addItem("Saw", 3);
    osc2Menu.addItem("Square", 4);

    osc2Menu.setComponentID("osc2");
    osc2Menu.setJustificationType(Justification::centred);
    osc2Menu.setSelectedId(1);
    osc2Menu.addListener(this);

    //Add to editor
    addAndMakeVisible(&osc2Menu);
    osc2MenuAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.tree, "wavetype2", osc2Menu);

    osc2Model.updateWave(osc2Menu.getSelectedId());
    addAndMakeVisible(&osc2Model);

    oscLabel.setText ("Oscillators", dontSendNotification);
    oscLabel.setFont(Font(16));
    oscLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&oscLabel);

    //blendKnob config
    blendKnob.setLookAndFeel(&customLookAndFeel);
    blendKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    blendKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    blendKnob.setSize(getWidth()/4,72);
    blendLabel.setText ("Blend", dontSendNotification);
    blendLabel.setFont(Font(10));
    blendLabel.setJustificationType(Justification::centred);
    blendLabel.attachToComponent(&blendKnob, false);
    addAndMakeVisible(&blendKnob);
    blendKnob.addListener(this);
    blendAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "blend", blendKnob);
    blendKnob.setNumDecimalPlacesToDisplay(2);
}

Oscillator::~Oscillator()
{
}

float Oscillator::getBlend()
{
    return blendKnob.getValue();
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
    Rectangle<int> menus = area.removeFromTop(25);
    osc1Menu.setBounds(menus.removeFromLeft(160));
    oscLabel.setBounds(menus.removeFromLeft(144));
    osc2Menu.setBounds(menus.removeFromLeft(160));
    area.removeFromTop(10);
    osc1Model.setBounds(area.removeFromLeft(160));
    blendKnob.setBounds(area.removeFromLeft(144));
    osc2Model.setBounds(area);
}

void Oscillator::comboBoxChanged(ComboBox* combo)
{
    String id = combo->getComponentID();
    if (id == "osc1") {
        osc1Model.updateWave(combo->getSelectedId());
    } else {
        osc2Model.updateWave(combo->getSelectedId());
    }
}

void Oscillator::sliderValueChanged(Slider* slider)
{

}