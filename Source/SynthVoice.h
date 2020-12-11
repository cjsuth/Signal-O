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
    
    void getFilterParams (std::atomic<float>* filter, std::atomic<float>* c, std::atomic<float>* r)
    {
        filtertype = (int)*filter;
        cutoff = (int)*c;
        res = (int)*r;
    }
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();
    }
    
    // like processBlock, DSP stuff here
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave;
            double filteredSound;
            
            switch (wavetype) {
                case 1: theWave = osc1.sinewave(frequency) * level; break;
                case 2: theWave = osc1.triangle(frequency) * level; break;
                case 3: theWave = osc1.saw(frequency) * level; break;
                case 4: theWave = osc1.square(frequency) * level; break;
                default: theWave = osc1.sinewave(frequency) * level;
            }
            
            double theSound = env1.adsr(theWave, env1.trigger) * level;
            
            switch (filtertype) {
                case 1: filteredSound = filter1.lores(theSound, cutoff, res); break;
                case 2: filteredSound = filter1.hires(theSound, cutoff, res); break;
                case 3: filteredSound = filter1.bandpass(theSound, cutoff, res); break;
                default: filteredSound = filter1.lores(theSound, cutoff, res);
            }
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, filteredSound);
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
    int filtertype;
    float cutoff;
    float res;
    
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
};
