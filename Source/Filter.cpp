/*
  ==============================================================================

    Filter.cpp
    Created: 28 May 2020 10:21:16am
    Author:  Chad Sutherland

  ==============================================================================
*/

#include "Filter.h"
#include <JuceHeader.h>

//==============================================================================
Filter::Filter(BasicSynthAudioProcessor& p) :
    processor(p)//, envModel(0,0,0,0)
{
    setOpaque (true);
    setSize(240, 130);
    
    //filtermenu config
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.addItem("Band Pass", 3);
    filterMenu.setJustificationType(Justification::centred);
    filterMenu.setSelectedId(1);
    filterLabel.setText ("Filter", dontSendNotification);
    filterLabel.setFont(Font(16));
    filterLabel.setJustificationType(Justification::left);
    filterLabel.attachToComponent(&filterMenu, true);
    addAndMakeVisible(&filterMenu);
    filterMenuAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.tree, "filterType", filterMenu);
    
    //cutoffKnob config
    cutoffKnob.setLookAndFeel(&customLookAndFeel);
    cutoffKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    cutoffKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    cutoffLabel.setText ("Cutoff", dontSendNotification);
    cutoffLabel.setFont(Font(10));
    cutoffLabel.setJustificationType(Justification::centred);
    cutoffLabel.attachToComponent(&cutoffKnob, false);
    addAndMakeVisible(&cutoffKnob);
    cutoffKnob.addListener(this);
    cutoffAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "filterCutoff", cutoffKnob);
    cutoffKnob.setNumDecimalPlacesToDisplay(2);

    //resKnob config
    resKnob.setLookAndFeel(&customLookAndFeel);
    resKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    resKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    resLabel.setText ("Res", dontSendNotification);
    resLabel.setFont(Font(10));
    resLabel.setJustificationType(Justification::centred);
    resLabel.attachToComponent(&resKnob, false);
    addAndMakeVisible(&resKnob);
    resKnob.addListener(this);
    resAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "filterRes", resKnob);
    resKnob.setNumDecimalPlacesToDisplay(2);
}

Filter::~Filter()
{
}


float Filter::getFilterType()
{
    return filterMenu.getSelectedIdAsValue().getValue();
}

float Filter::getCutoff()
{
    return cutoffKnob.getValue();
}

float Filter::getRes()
{
    return resKnob.getValue();
}

void Filter::paint (Graphics& g)
{
    g.fillAll (Colours::darkgrey);
    g.setColour(getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillRoundedRectangle(getLocalBounds().reduced(2).toFloat(), 5.0f);
    g.setColour(Colours::white);
    g.drawRoundedRectangle(getLocalBounds().reduced(2).toFloat(), 5.0f, 3.0f);
}

void Filter::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(border);
    filterMenu.setBounds(area.removeFromTop(30).removeFromRight(180));

    auto knobWidth = area.getWidth() / 3;
    area.removeFromTop(15);
    cutoffKnob.setBounds(area.removeFromLeft(knobWidth).reduced(4));
    resKnob.setBounds(area.removeFromLeft(knobWidth).reduced(4));
}

void Filter::sliderValueChanged(Slider* slider)
{
}
