#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
                        public juce::Button::Listener,
                        public juce::ComboBox::Listener,
                        public juce::Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

    void buttonClicked (juce::Button* button) override;
    void comboBoxChanged (juce::ComboBox* comboBox) override;
    void sliderValueChanged (juce::Slider* slider) override;

private:
    //==============================================================================
    // Your private member variables go here...
    std::unique_ptr<juce::TextButton> openButton;
    std::unique_ptr<juce::FileChooser> fileChooser;
    std::unique_ptr<juce::ComboBox> separationSelector;
    std::unique_ptr<juce::Slider> separationSlider;
    std::unique_ptr<juce::TextButton> separateButton;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
