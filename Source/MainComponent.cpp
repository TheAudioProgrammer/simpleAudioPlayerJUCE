/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent() : openButton("Open")
{
    setSize (200, 100);
    setAudioChannels (0, 2);
    
    openButton.onClick = [this] {  openButtonClicked(); };
    addAndMakeVisible(&openButton);
    
    formatManager.registerBasicFormats();
    
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

void MainComponent::openButtonClicked()
{
    //choose a file
    FileChooser chooser ("Choose a Wav or AIFF File", File::getSpecialLocation(File::userDesktopDirectory), "*.wav");
    
    //if the user chooses a file
    if (chooser.browseForFileToOpen())
    {
        File myFile;
        
        //what did the user choose?
        myFile = chooser.getResult();
        
        //read the file
        AudioFormatReader* reader = formatManager.createReaderFor(myFile);
        
        //get the file ready to play
        std::unique_ptr<AudioFormatReaderSource> tempSource (new AudioFormatReaderSource (reader, true));
        
        playSource.reset(tempSource.release());
        
        DBG(reader->getFormatName());
    }
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
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
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    openButton.setBounds(10, 10, getWidth() - 20, 30);
    
}
