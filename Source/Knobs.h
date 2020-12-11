/*
  ==============================================================================

    Knobs.h
    Created: 28 May 2020 10:40:53am
    Author:  Chad Sutherland

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class TimeKnob : public Slider
{
public:
    String getTextFromValue(double val) {
        String suffix = " ms";
        
        if (val > 1000.0) {
            val = (val / 1000.0);
            suffix = " s";
        }
    
        if (getNumDecimalPlacesToDisplay() > 0)
            return String (val, getNumDecimalPlacesToDisplay()) + suffix;

        return String (roundToInt (val)) + suffix;
    }
};

class DBKnob : public Slider
{
public:
    String getTextFromValue(double val) {
        String suffix = " dB";
        
    
        if (getNumDecimalPlacesToDisplay() > 0)
            return String (Decibels::gainToDecibels(val), getNumDecimalPlacesToDisplay()) + suffix;

        return String (roundToInt (Decibels::gainToDecibels(val))) + suffix;
    }
};

class HZKnob : public Slider
{
public:
    String getTextFromValue(double val) {
        String suffix = " Hz";
        
        if (val > 1000.0) {
            val = (val / 1000.0);
            suffix = " KHz";
        }
    
        if (getNumDecimalPlacesToDisplay() > 0)
            return String (val, getNumDecimalPlacesToDisplay()) + suffix;

        return String (roundToInt (val)) + suffix;
    }
};
