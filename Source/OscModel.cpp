/*
  ==============================================================================

    OscModel.cpp
    Created: 27 May 2020 10:34:25am
    Author:  Chad Sutherland

  ==============================================================================
*/

#include "OscModel.h"
#include <JuceHeader.h>

//==============================================================================
OscModel::OscModel(int wavetype)
{
    setOpaque (true);
    setSize(240, 80);
    updateWave(wavetype);
}

OscModel::~OscModel()
{
}

void OscModel::updateWave(int wavetype)
{
    wave = wavetype;
    repaint();
}

void OscModel::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour(Colours::darkslategrey);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 5.0f);

    switch (wave) {
        case 1: drawSine(g); break;
        case 2: drawTriangle(g); break;
        case 3: drawSaw(g); break;
        case 4: drawSquare(g); break;
    }
}

void OscModel::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

void OscModel::drawSine(Graphics &g) {
    int width = getWidth();
    int height = getHeight();
    Point<float> start = Point<float>(border, height / 2);
    Point<float> end = Point<float>(width - border, height / 2);
    Point<float> mid = Point<float>((width/2), height / 2);
    Point<float> mid1((end.getX() + (3 * start.getX())) / 4, 
                      end.getY() - 70);
    Point<float> mid2(((3 * end.getX()) + start.getX()) / 4, end.getY() + 70);
    Path sinePath = Path();
    sinePath.startNewSubPath(start);
    sinePath.quadraticTo(mid1, mid);
    sinePath.quadraticTo(mid2, end);

    g.setColour(Colours::orange);
    g.strokePath( sinePath, PathStrokeType(2) );
}

void OscModel::drawTriangle(Graphics &g) {
    int width = getWidth();
    int height = getHeight();
    Point<float> start = Point<float>(border, height - border);
    Point<float> end = Point<float>(width - border, border);
    Point<float> end_floor(end.getX(), height - border);

    Point<float> mid1((end.getX() + (3 * start.getX())) / 4, border);
    Point<float> mid2_floor = Point<float>(width / 2, height - border);
    Point<float> mid3(((3 * end.getX()) + start.getX()) / 4, border);   

    
    Path sinePath = Path();
    sinePath.startNewSubPath(start);
    sinePath.lineTo(mid1);
    sinePath.lineTo(mid2_floor);
    sinePath.lineTo(mid3);
    sinePath.lineTo(end_floor);

    g.setColour(Colours::orange);
    g.strokePath( sinePath, PathStrokeType(2) );
}

void OscModel::drawSaw(Graphics &g) {
    int width = getWidth();
    int height = getHeight();
    Point<float> start = Point<float>(border, height - border);
    Point<float> end = Point<float>(width - border, border);
    Point<float> end_floor(end.getX(), height - border);
    Point<float> mid = Point<float>(width / 2, border);
    Point<float> mid_floor = Point<float>(mid.getX(), height - border);
    
    Path sinePath = Path();
    sinePath.startNewSubPath(start);
    sinePath.lineTo(mid);
    sinePath.lineTo(mid_floor);
    sinePath.lineTo(end);
    sinePath.lineTo(end_floor);

    g.setColour(Colours::orange);
    g.strokePath( sinePath, PathStrokeType(2) );
}

void OscModel::drawSquare(Graphics &g) {
    int width = getWidth();
    int height = getHeight();
    Point<float> start = Point<float>(border, height - border);
    Point<float> start_ceil = Point<float>(border, border);

    Point<float> end = Point<float>(width - border, border);
    Point<float> end_floor(end.getX(), height - border);

    Point<float> mid1((end.getX() + (3 * start.getX())) / 4, border);
    Point<float> mid1_floor(mid1.getX(), height - border);

    Point<float> mid2 = Point<float>((width/2), border);
    Point<float> mid2_floor = Point<float>(mid2.getX(), height - border);

    Point<float> mid3(((3 * end.getX()) + start.getX()) / 4, border);
    Point<float> mid3_floor = Point<float>(mid3.getX(), height - border);    

    Path sinePath = Path();
    sinePath.startNewSubPath(start);
    sinePath.lineTo(start_ceil);
    sinePath.lineTo(mid1);
    sinePath.lineTo(mid1_floor);
    sinePath.lineTo(mid2_floor);
    sinePath.lineTo(mid2);
    sinePath.lineTo(mid3);
    sinePath.lineTo(mid3_floor);
    sinePath.lineTo(end_floor);

    g.setColour(Colours::orange);
    g.strokePath( sinePath, PathStrokeType(2) );
}