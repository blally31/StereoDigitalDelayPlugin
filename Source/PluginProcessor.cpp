/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DdlmoduleAudioProcessor::DdlmoduleAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	undoManager = new UndoManager();
	parameters = new AudioProcessorValueTreeState(*this, undoManager);

	//add the delay, feedback and wet/dry levels to the state tree
	parameters->createAndAddParameter(PARAM_DELAY, "Delay", String(),
		NormalisableRange<float>(0, 2000),
		0,	/*default value*/
		nullptr,
		nullptr);

	parameters->createAndAddParameter(PARAM_FEEDBACK, "Feedback", String(),
		NormalisableRange<float>(-100, 100),
		0, /*default value*/
		nullptr,
		nullptr);

	parameters->createAndAddParameter(PARAM_WETDRY, "Wet/Dry", String(),
		NormalisableRange<float>(0, 100),
		50, /*default value*/
		nullptr,
		nullptr);

		parameters->addParameterListener(PARAM_DELAY, this);
		parameters->addParameterListener(PARAM_FEEDBACK, this);
		parameters->addParameterListener(PARAM_WETDRY, this);

	//create the actual value tree with the PARAM_SETNAME identifier
	parameters->state = ValueTree(PARAM_SETNAME);

}

DdlmoduleAudioProcessor::~DdlmoduleAudioProcessor()
{
	
}

//==============================================================================
const String DdlmoduleAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DdlmoduleAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DdlmoduleAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double DdlmoduleAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DdlmoduleAudioProcessor::getNumPrograms()
{
    return 1;   
}

int DdlmoduleAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DdlmoduleAudioProcessor::setCurrentProgram (int index)
{

}

const String DdlmoduleAudioProcessor::getProgramName (int index)
{
    return String();
}

void DdlmoduleAudioProcessor::changeProgramName (int index, const String& newName)
{

}

//==============================================================================
void DdlmoduleAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	delay.setBufferSize(sampleRate);
	delay.newBuffer();
	
	float delay_ms = *parameters->getRawParameterValue(PARAM_DELAY);
	float fb = *parameters->getRawParameterValue(PARAM_FEEDBACK);
	float wet = *parameters->getRawParameterValue(PARAM_WETDRY);

	// Calculate the initial delay values
	delay.calculateValues(delay_ms, fb, wet, sampleRate);	
}

void DdlmoduleAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DdlmoduleAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DdlmoduleAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	float* leftData = buffer.getWritePointer(0);
	float* rightData = buffer.getWritePointer(1);

	for (int sample = 0; sample < buffer.getNumSamples(); sample++)
	{
		leftData[sample] = delay.process(leftData[sample]);
		rightData[sample] = delay.process(rightData[sample]);
	}
}

//==============================================================================
bool DdlmoduleAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DdlmoduleAudioProcessor::createEditor()
{
    return new DdlmoduleAudioProcessorEditor (*this);
}

//==============================================================================
void DdlmoduleAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	//Save user data and parameters to file
	MemoryOutputStream stream(destData, false);
	parameters->state.writeToStream(stream);
}

void DdlmoduleAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	//Load user data and parameters from file
	ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
	if (tree.isValid())
	{
		if (tree.hasType(PARAM_SETNAME))
		{
			parameters->state = tree;
		}
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DdlmoduleAudioProcessor();
}

void DdlmoduleAudioProcessor::parameterChanged(const String& parameterID, float newValue)
{
	if (parameterID.compare(PARAM_DELAY) == 0)
	{
		delay.updateDelay(newValue, getSampleRate());
	}
	else if (parameterID.compare(PARAM_FEEDBACK) == 0)
	{
		delay.updateFeedback(newValue);
	}
	else if (parameterID.compare(PARAM_WETDRY) == 0)
	{
		delay.updateWetDry(newValue);
	}
}
