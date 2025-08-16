#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    openButton = std::make_unique<juce::TextButton>("Open File");
    separationSelector = std::make_unique<juce::ComboBox>("Separation Method");
    separationSlider = std::make_unique<juce::Slider>("Separation Amount");
    separateButton = std::make_unique<juce::TextButton>("Start separation!");

    openButton->setBounds (10, 10, 100, 30);
    separationSelector->setBounds (120, 10, 200, 30);
    separationSlider->setBounds (10, 50, 300, 30);
    separateButton->setBounds (10, 90, 300, 30);

    addAndMakeVisible (*openButton);
    addAndMakeVisible (*separationSelector);
    addAndMakeVisible (*separationSlider);
    addAndMakeVisible (*separateButton);

    openButton->addListener (this);
    separationSelector->addListener (this);
    separationSlider->addListener (this);
    separateButton->addListener (this);

    openButton->setEnabled(true);
    //Cannot select a separation method until a file is opened

    separationSelector->setEnabled(false);
    separationSelector->addItem("IS-NMF", 1);
    separationSelector->addItem("Fast-ICA", 2);
    separationSelector->setSelectedId(1);   //Set IS-NMF as default

    separationSlider->setEnabled(false);
    separationSlider->setRange(2, 8, 1);
    separationSlider->setValue(4);

    separateButton->setEnabled(false);

    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    openButton->setBounds (10, 10, 100, 30);
    separationSelector->setBounds (120, 10, 200, 30);
    separationSlider->setBounds (10, 50, 300, 30);
}

void MainComponent::buttonClicked (juce::Button* button)
{
    if (button == openButton.get())
    {
        openButton->setEnabled(false);
        // Open file dialog
        fileChooser = std::make_unique<juce::FileChooser>("Select a Sound Source File",
                                                          juce::File::getSpecialLocation(juce::File::userDocumentsDirectory),
                                                          "*.wav;*.flac;*.mp3");

        fileChooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
                                  [this](const juce::FileChooser& chooser)
                                  {
                                      juce::File sourceFile = chooser.getResult();
                                      DBG("Loaded file is " + sourceFile.getFullPathName());
                                      separationSelector->setEnabled(true);
                                      separationSlider->setEnabled(true);
                                      separateButton->setEnabled(true);
                                  });
    } else if (button == separateButton.get())
    {
        // Start the separation process
        DBG("Starting separation...");
        separateButton->setEnabled(false);
    }
}

void MainComponent::comboBoxChanged (juce::ComboBox* selector)
{
    if (selector == separationSelector.get())
    {
        // Handle separation method selection change
        DBG("Selected separation method: " + separationSelector->getText());
    }
}

void MainComponent::sliderValueChanged (juce::Slider* slider)
{
    if (slider == separationSlider.get())
    {
        // Handle separation amount slider value change
        DBG("Separation amount: " + juce::String(slider->getValue()));
    }
}
