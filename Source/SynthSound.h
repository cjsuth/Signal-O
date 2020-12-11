/*
  ==============================================================================

    SynthSound.h
    Created: 22 May 2020 10:12:42am
    Author:  Chad Sutherland

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) {
        return true;
    }
    
    bool appliesToChannel (int midiChannel) {
        return true;
    }
};
