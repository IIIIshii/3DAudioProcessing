/*
  ==============================================================================

    SeparationThread.cpp
    Created: 16 Aug 2025 11:42:17pm
    Author:  iiiishii

  ==============================================================================
*/

#include "SeparationThread.h"

SeparationThread::SeparationThread(const juce::File& inputFile, int separationType, int numSources, Listener& listener)
    : Thread("SeparationThread"), inputFile(inputFile), numComponents(numSources), separationType(separationType), listener(listener)
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
      //monoralize
      bufferOriginalData.applyGain(0.5f);
      bufferOriginalData.addFrom(0, 0, bufferOriginalData, 1, 0, bufferOriginalData.getNumSamples());
      bufferOriginalData.setSize(1, bufferOriginalData.getNumSamples(), true);

      //STFT

      //IS-NMF

      //ISTFT
    } else {
      //Fast-ICA
    }

    //Finish
    juce::OwnedArray<juce::AudioBuffer<float>> resultBuffers;
    resultBuffers.add(new juce::AudioBuffer<float>(bufferOriginalData));
    listener.separationFinished(resultBuffers);
}