/*
  ==============================================================================

    OscModel.h
    Created: 27 May 2020 10:34:25am
    Author:  Chad Sutherland

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscModel : public Component
{
public:
    OscModel(int);
    ~OscModel();

    // void updateNodes(float attack, float decay, float sustain, float release);
    // float getSkewedPosition(float value, float min, float midpoint, float max);

    void updateWave(int);

    void paint (Graphics&) override;
    void resized() override;
    // void drawLines();

private:
    int border = 10;
    int wave;

    void drawSine(Graphics &);
    void drawTriangle(Graphics &);
    void drawSaw(Graphics &);
    void drawSquare(Graphics &);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscModel)
};

