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
    
    void getWavetypeParam (std::atomic<float>* wave)
    {
        wavetype = (int)*wave;
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
        double sample1;

        switch(wavetype) {
            case 1: sample1 = osc1.sinewave(frequency); break;
            case 2: sample1 = osc1.triangle(frequency); break;
            case 3: sample1 = osc1.saw(frequency); break;
            case 4: sample1 = osc1.square(frequency); break;
            default: sample1 = osc1.sinewave(frequency);
        }

        return sample1;
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
                outputBuffer.addSample(channel, startSample, setEnvelope() * level);
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
    double level;
    double frequency;
    int wavetype;
    int theWave;

    int filterChoice;
    float cutoff;
    float res;
    
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
};
