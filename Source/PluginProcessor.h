/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "DelayBuffer.h"


//==============================================================================
/**
*/
class DdlmoduleAudioProcessor  :	public AudioProcessor,
									public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    DdlmoduleAudioProcessor();
    ~DdlmoduleAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	//==============================================================================
	//Parameters and accessors
	#define PARAM_SETNAME "DelayParams"	
	#define PARAM_DELAY "DelayMS"
	#define PARAM_FEEDBACK "Feedback"
	#define PARAM_WETDRY "Wet/Dry"
	#define PI 3.1415926535897932384626433832795

	AudioProcessorValueTreeState& getState() { return *parameters; };
	void parameterChanged(const String& parameterID, float newValue) override;

private:
	//Used to control the value tree state for storing and using parameters
	bool delayParamChange;
	bool fdbkParamChange;
	bool wetParamChange;

	DelayBuffer delay;

	ScopedPointer<AudioProcessorValueTreeState> parameters;
	ScopedPointer<UndoManager> undoManager;

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DdlmoduleAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
