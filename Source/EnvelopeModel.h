/*
  ==============================================================================

    EnvelopeModel.h
    Created: 27 May 2020 10:34:25am
    Author:  Chad Sutherland

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
//#include "Envelope.h"

class EnvelopeModel : public Component
{
public:
    EnvelopeModel(float, float, float, float);
    ~EnvelopeModel();

    void updateNodes(float attack, float decay, float sustain, float release);
    float getSkewedPosition(float value, float min, float midpoint, float max);
    
    void paint (Graphics&) override;
    void resized() override;
    void drawLines();

private:
    int border = 4;
    
    Point<float> attackNode;
    Point<float> decayNode;
    Point<float> sustainNode;
    Point<float> releaseNode;
    
    Line<float> attackLine;
    Path decayPath;
    Line<float> sustainLine;
    Path releasePath;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeModel)
};

