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
    oscLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&oscLabel);

    //level1Knob config
    level1Knob.setLookAndFeel(&customLookAndFeel);
    level1Knob.setSliderStyle(Slider::RotaryVerticalDrag);
    level1Knob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    // level1Knob.setSize(getWidth()/4,72);
    addAndMakeVisible(&level1Knob);
    level1Knob.addListener(this);
    level1Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "level1", level1Knob);
    level1Knob.setNumDecimalPlacesToDisplay(2);

    //level2Knob config
    level2Knob.setLookAndFeel(&customLookAndFeel);
    level2Knob.setSliderStyle(Slider::RotaryVerticalDrag);
    level2Knob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    // level2Knob.setSize(getWidth()/4,72);
    addAndMakeVisible(&level2Knob);
    level2Knob.addListener(this);
    level2Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "level2", level2Knob);
    level2Knob.setNumDecimalPlacesToDisplay(2);

    //freq2Knob config
    freq1Knob.setLookAndFeel(&customLookAndFeel);
    freq1Knob.setSliderStyle(Slider::RotaryVerticalDrag);
    freq1Knob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    // freq1Knob.setSize(getWidth()/4,72);
    addAndMakeVisible(&freq1Knob);
    freq1Knob.addListener(this);
    freq1Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "freq1", freq1Knob);
    freq1Knob.setNumDecimalPlacesToDisplay(1);

    //freq2Knob config
    freq2Knob.setLookAndFeel(&customLookAndFeel);
    freq2Knob.setSliderStyle(Slider::RotaryVerticalDrag);
    freq2Knob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    // freq2Knob.setSize(getWidth()/4,72);
    addAndMakeVisible(&freq2Knob);
    freq2Knob.addListener(this);
    freq2Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "freq2", freq2Knob);
    freq2Knob.setNumDecimalPlacesToDisplay(1);



    freqLabel.setText ("Freq", dontSendNotification);
    freqLabel.setFont(Font(10));
    freqLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&freqLabel);

    levelLabel.setText ("Level", dontSendNotification);
    levelLabel.setFont(Font(10));
    levelLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&levelLabel);
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
    Rectangle<int> menus = area.removeFromTop(25);
    osc1Menu.setBounds(menus.removeFromLeft(160));
    oscLabel.setBounds(menus.removeFromLeft(144));
    osc2Menu.setBounds(menus.removeFromLeft(160));
    area.removeFromTop(10);
    osc1Model.setBounds(area.removeFromLeft(160));
    osc2Model.setBounds(area.removeFromRight(160));

    Rectangle<int> top = area.removeFromTop(area.getHeight() / 2);
    freq1Knob.setBounds(top.removeFromLeft((top.getWidth()-30) / 2));
    freqLabel.setBounds(top.removeFromLeft(30));
    freq2Knob.setBounds(top);

    level1Knob.setBounds(area.removeFromLeft((area.getWidth()-30) / 2));
    levelLabel.setBounds(area.removeFromLeft(30));
    level2Knob.setBounds(area);
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