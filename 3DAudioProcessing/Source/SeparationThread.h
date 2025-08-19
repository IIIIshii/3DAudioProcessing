/*
  ==============================================================================

    SeparationThread.h
    Created: 16 Aug 2025 11:42:31pm
    Author:  iiiishii

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "NMF.h"

// background thread
class SeparationThread : public juce::Thread
{
public:
    class Listener
    {
    public:
      virtual void separationFinished(const juce::OwnedArray<juce::AudioBuffer<float>>& resultBuffers) = 0;
      virtual ~Listener() = default;
    };

    SeparationThread(const juce::File& inputFile, int separationType, int numSources, Listener& listener);

    ~SeparationThread() override;
    void run() override;

private:
    juce::File inputFile;
    int separationType;
    int numSources;
    Listener& listener;

    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReader> reader;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SeparationThread)
};
