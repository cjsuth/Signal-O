/*
  ==============================================================================

    EnvelopeModel.cpp
    Created: 27 May 2020 10:34:25am
    Author:  Chad Sutherland

  ==============================================================================
*/

#include "EnvelopeModel.h"
#include <JuceHeader.h>

//==============================================================================
EnvelopeModel::EnvelopeModel(float attack, float decay, float sustain, float release)
{
    setOpaque (true);
    setSize(240, 80);
    
    updateNodes(attack, decay, sustain, release);
}

EnvelopeModel::~EnvelopeModel()
{
}

void EnvelopeModel::updateNodes(float attack, float decay, float sustain, float release)
{
    //        auto clampedValue = jlimit (static_cast<ValueType> (0), static_cast<ValueType> (1), value);
    //        auto proportion = clampTo0To1 ((v - start) / (end - start));
    // skew = std::log (static_cast<ValueType> (0.5)) / std::log ((centrePointValue - start) / (end - start));
    //            return std::pow (proportion, skew);
    

    
    
    auto maxWidth = (getWidth() - border) / 3;
    auto maxHeight = getHeight() - (border * 2);

    attackNode.setX((getSkewedPosition(attack, 0.0f, 1000.0f, 20000.0f) * maxWidth) + border);
    attackNode.setY(border);
    sustainNode.setX((maxWidth * 2) + border);
    sustainNode.setY(maxHeight - (sustain * maxHeight) + border);
    decayNode.setX(attackNode.getX() + (getSkewedPosition(decay, 0.0f, 1000.0f, 60000.0f) * maxWidth));
    decayNode.setY(sustainNode.getY());
    releaseNode.setX((maxWidth * 2) + (getSkewedPosition(release, 0.0f, 1000.0f, 60000.0f) * maxWidth) + border);
    releaseNode.setY(getHeight() - border);
    
    drawLines();
    repaint();
    //triggerAsyncUpdate();
}

float EnvelopeModel::getSkewedPosition(float value, float min, float midpoint, float max)
{
    auto proportion = (value - min) / (max - min);
    auto clampedProportion = jlimit (0.0f, 1.0f, proportion);
    auto skew = std::log (.5) / std::log ((midpoint - min) / (max - min));
    return std::pow (clampedProportion, skew);
}

void EnvelopeModel::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour(Colours::darkslategrey);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 5.0f);
    
    g.setColour(Colours::orange);
    g.drawLine(attackLine, 2.0f);
    g.strokePath( decayPath, PathStrokeType(2) );
    g.drawLine(sustainLine, 2.0f);
    g.strokePath( releasePath, PathStrokeType(2) );
    
    g.setColour(Colours::yellow);
    g.fillRect(attackNode.getX()-2, attackNode.getY()-2, 4.0f, 4.0f);
    g.fillRect(decayNode.getX()-2, decayNode.getY()-2, 4.0f, 4.0f);
    //g.fillRect(sustainNode.getX()-2, sustainNode.getY()-2, 4.0f, 4.0f);
    g.fillRect(releaseNode.getX()-2, releaseNode.getY()-2, 4.0f, 4.0f);

}

void EnvelopeModel::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

void EnvelopeModel::drawLines()
{
    attackLine = Line<float>(Point<float>(border,getHeight() - border), attackNode);
    
    Point<float> mid1(attackNode.getX(), decayNode.getY());
    decayPath = Path();
    decayPath.startNewSubPath(attackNode);
    decayPath.quadraticTo(mid1, decayNode);
    
    sustainLine = Line<float>(decayNode, sustainNode);
    
    Point<float> mid2(sustainNode.getX(), releaseNode.getY());
    releasePath = Path();
    releasePath.startNewSubPath(sustainNode);
    releasePath.quadraticTo(mid2, releaseNode);
}
