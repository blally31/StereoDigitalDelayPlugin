/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DdlmoduleAudioProcessorEditor::DdlmoduleAudioProcessorEditor (DdlmoduleAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	// Delay_MS slider
	addAndMakeVisible(delayCtrlSld = new Slider("Delay MS"));
	delayCtrlSld->setRange(0, 2000, 0);
	delayCtrlSld->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	delayCtrlSld->setRotaryParameters(degreesToRadians(270.0), degreesToRadians(450.0), true);
	delayCtrlSld->setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);

	// Feedback slider
	addAndMakeVisible(fdbkCtrlSld = new Slider("Feedback"));
	fdbkCtrlSld->setRange(-100, 100, 0);
	fdbkCtrlSld->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	fdbkCtrlSld->setRotaryParameters(degreesToRadians(270.0), degreesToRadians(450.0), true);
	fdbkCtrlSld->setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);

	// Wet/Dry mix slider
	addAndMakeVisible(wetCtrlSld = new Slider("Wet/Dry"));
	wetCtrlSld->setRange(0, 100, 0);
	wetCtrlSld->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	wetCtrlSld->setRotaryParameters(degreesToRadians(270.0), degreesToRadians(450.0), true);
	wetCtrlSld->setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);

	// Plugin labels
	addAndMakeVisible(titleLbl = new Label("Label1", TRANS("Digital Delay Line Module\n")));
	titleLbl->setFont(Font(18.0f, Font::plain));
	titleLbl->setColour(Label::textColourId, Colours::white);
	
	addAndMakeVisible(delayLbl = new Label("Label1", TRANS("Delay - mSec\n")));
	delayLbl->setFont(Font(18.0f, Font::plain));
	delayLbl->setColour(Label::textColourId, Colours::white);
	
	addAndMakeVisible(fdbkLbl = new Label("Label1", TRANS("Feedback - %\n")));
	fdbkLbl->setFont(Font(18.0f, Font::plain));
	fdbkLbl->setColour(Label::textColourId, Colours::white);

	addAndMakeVisible(wetLbl = new Label("Label1", TRANS("Wet/Dry Mix - %\n")));
	wetLbl->setFont(Font(18.0f, Font::plain));
	wetLbl->setColour(Label::textColourId, Colours::white);

    // editor dimensions
	setSize (600, 300);

	// attach the sliders to the value tree
	dlyAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_DELAY, *delayCtrlSld);
	fdbkAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_FEEDBACK, *fdbkCtrlSld);
	wetAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_WETDRY, *wetCtrlSld);
}

DdlmoduleAudioProcessorEditor::~DdlmoduleAudioProcessorEditor()
{
	dlyAttachment = nullptr;
	fdbkAttachment = nullptr;
	wetAttachment = nullptr;

	delayCtrlSld = nullptr;
	fdbkCtrlSld = nullptr;
	wetCtrlSld = nullptr;

	titleLbl = nullptr;
	delayLbl = nullptr;
	fdbkLbl = nullptr;
	wetLbl = nullptr;
}

//==============================================================================
void DdlmoduleAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void DdlmoduleAudioProcessorEditor::resized()
{
	// Component positions
	delayCtrlSld->setBounds(75, 100, 150, 75);
	fdbkCtrlSld->setBounds(225, 100, 150, 75);
	wetCtrlSld->setBounds(375, 100, 150, 75);

	titleLbl->setBounds(185, 20, 250, 50);
	delayLbl->setBounds(85, 120, 250, 50);
	fdbkLbl->setBounds(235, 120, 250, 50);
	wetLbl->setBounds(385, 120, 250, 50);
}

void DdlmoduleAudioProcessorEditor::sliderValueChanged(Slider* sliderThatWasMoved)
{

}