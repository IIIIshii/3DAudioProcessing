/*
  ==============================================================================

    SeparationThread.cpp
    Created: 16 Aug 2025 11:42:17pm
    Author:  iiiishii

  ==============================================================================
*/

#include "SeparationThread.h"

SeparationThread::SeparationThread(const juce::File& inputFile, int separationType, int numSources, Listener& listener)
    : Thread("SeparationThread"), inputFile(inputFile), separationType(separationType), numSources(numSources), listener(listener)
{
    formatManager.registerBasicFormats();
    reader.reset(formatManager.createReaderFor(inputFile));
    
    if (reader == nullptr)
    {
        DBG("Failed to create a format of : " << inputFile.getFullPathName());
    }
}

SeparationThread::~SeparationThread()
{
    // Ensure the thread is stopped before destruction
    stopThread(5000);
}

void SeparationThread::run()
{
    if (reader == nullptr)
    {
        DBG("Nothing to run");
        return;
    }

    // Read the original data into the buffer
    //as a stereo data
    juce::AudioBuffer<float> bufferOriginalData(static_cast<int>(reader->numChannels), static_cast<int>(reader->lengthInSamples));
    reader->read(&bufferOriginalData, 0, reader->lengthInSamples, 0, true, true);

    if(separationType == 1)
    {
      //IS-NMF
      ISNMF nmf(numSources);
      nmf.processNMF(bufferOriginalData);
    } else {
      //Fast-ICA
    }

    //Finish
    juce::OwnedArray<juce::AudioBuffer<float>> resultBuffers;
    resultBuffers.add(new juce::AudioBuffer<float>(bufferOriginalData));
    listener.separationFinished(resultBuffers);
}