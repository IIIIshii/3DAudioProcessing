/*
  ==============================================================================

    NMF.cpp
    Created: 16 Aug 2025 9:24:33pm
    Author:  iiiishii

  ==============================================================================
*/

//ソースファイル(juce::File)と分離数が与えられるだけ
//ファイルはjuce::AudioBuffer<float>　で与えられることになる
//モノラル化はICAと共通しないのでこっちでやりたい

#include "NMF.h"

ISNMF::ISNMF(int numSources)
   : numSources(numSources)
{
}

ISNMF::~ISNMF(){

}
void ISNMF::monoralize(juce::AudioBuffer<float>& buffer){
  buffer.applyGain(0.5f);
  buffer.addFrom(0, 0, buffer, 1, 0, buffer.getNumSamples());
  buffer.setSize(1, buffer.getNumSamples(), true);
}


void STFT(juce::AudioBuffer<float> originalBuffer, int fftSize, int hopSize){

}

void NMF(const Eigen::MatrixXf& targetMatrix, int numIterations){

}

void ISTFT(Eigen::MatrixXf separatedMagSpec){

}

void restore(juce::AudioBuffer<float>& returnData){

}

void ISNMF::processNMF(juce::AudioBuffer<float>& buffer){
  monoralize(buffer);
}