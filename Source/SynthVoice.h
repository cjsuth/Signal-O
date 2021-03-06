/*
  ==============================================================================

    SynthVoice.h
    Created: 22 May 2020 10:13:09am
    Author:  Chad Sutherland

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound *sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    void getEnvelopeParams (std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release)
    {
        env1.setAttack(*attack);
        env1.setDecay(*decay);
        env1.setSustain(*sustain);
        env1.setRelease(*release);
        
    }
    
    void getWavetypeParams(std::atomic<float>* wave1, 
                            std::atomic<float>* wave2, 
                            std::atomic<float>* l1, 
                            std::atomic<float>* l2,
                            std::atomic<float>* o1,
                            std::atomic<float>* o2)
    {
        wavetype1 = (int)*wave1;
        wavetype2 = (int)*wave2;
        level1 = *l1;
        level2 = *l2;
        octave1 = *o1;
        octave2 = *o2;
    }
    
    void getFilterParams (std::atomic<float>* filterType, std::atomic<float>* filterCutoff, std::atomic<float>* filterRes)
    {
        filterChoice = (int)*filterType;
        cutoff = (int)*filterCutoff;
        res = (int)*filterRes;
    }
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override
    {
        env1.trigger = 1;
        level = velocity * .8;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    
    void stopNote (float velocity, bool allowTailOff) override
    {
        env1.trigger = 0;
        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();
    }

    double setOscType()
    {
        double sample1, sample2;

        double shiftedFreq1 = frequency * pow(2, octave1);
        double shiftedFreq2 = frequency * pow(2, octave2);
        
        switch (wavetype1)
        {
            case 1: sample1 = osc1.sinewave(shiftedFreq1); break;
            case 2: sample1 = osc1.triangle(shiftedFreq1); break;
            case 3: sample1 = osc1.saw(shiftedFreq1); break;
            case 4: sample1 = osc1.square(shiftedFreq1); break;
            default: sample1 = osc1.sinewave(shiftedFreq1);
        }
        
        switch (wavetype2)
        {
            case 1: sample2 = osc2.sinewave(shiftedFreq2); break;
            case 2: sample2 = osc2.triangle(shiftedFreq2); break;
            case 3: sample2 = osc2.saw(shiftedFreq2); break;
            case 4: sample2 = osc2.square(shiftedFreq2); break;
            default: sample2 = osc2.sinewave(shiftedFreq2);
        }
        
        return (sample1 * level1) + (sample2 * level2);
    }

    double setEnvelope()
    {
        return env1.adsr(setOscType(), env1.trigger);
    }
    
    // like processBlock, DSP stuff here
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {  
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, setEnvelope() * level); // change to gain
            }
            ++startSample;
        }
    }
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
private:
    double level, frequency;

    int wavetype1, wavetype2;
    float level1, level2, octave1, octave2;

    int filterChoice;
    float cutoff, res;

    maxiOsc osc1, osc2;
    maxiEnv env1;
    maxiFilter filter1;
};
