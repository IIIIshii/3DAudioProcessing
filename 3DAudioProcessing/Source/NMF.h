/*
  ==============================================================================

    NMF.h
    Created: 16 Aug 2025 9:24:56pm
    Author:  iiiishii

  ==============================================================================
*/

#pragma once

#include<iostream>
#include<stdlib.h>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <JuceHeader.h>

class ISNMF
{
  public:
    ISNMF(int numSources);

    ~ISNMF();

    void monoralize(juce::AudioBuffer<float>& buffer);

    void STFT(juce::AudioBuffer<float> originalBuffer, int fftSize, int hopSize);

    void processNMF(const Eigen::MatrixXf& targetMatrix, int numIterations);

    void ISTFT(Eigen::MatrixXf separatedMagSpec);

    void restore(juce::AudioBuffer<float>& returnData);

    void processNMF(juce::AudioBuffer<float>& buffer);

  private:
    const float epsilon_ = 1e-9f;
    int numSources;
};