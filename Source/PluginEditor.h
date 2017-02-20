/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class DdlmoduleAudioProcessorEditor  :	public AudioProcessorEditor,
										public SliderListener
{
public:
    DdlmoduleAudioProcessorEditor (DdlmoduleAudioProcessor& p);
    ~DdlmoduleAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
	void sliderValueChanged(Slider* sliderThatWasMoved) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DdlmoduleAudioProcessor& processor;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dlyAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> fdbkAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> wetAttachment;

	ScopedPointer<Slider> delayCtrlSld;
	ScopedPointer<Slider> fdbkCtrlSld;
	ScopedPointer<Slider> wetCtrlSld;
	
	ScopedPointer<Label> titleLbl;
	ScopedPointer<Label> delayLbl;
	ScopedPointer<Label> fdbkLbl;
	ScopedPointer<Label> wetLbl;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DdlmoduleAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
