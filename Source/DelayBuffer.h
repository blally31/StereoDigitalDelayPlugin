/*
  ==============================================================================

    DelayBuffer.h
    Created: 8 Feb 2017 6:32:18pm
    Author:  Brendan

  ==============================================================================
*/

#ifndef DELAYBUFFER_H_INCLUDED
#define DELAYBUFFER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <string.h>

class DelayBuffer
{
public:
	DelayBuffer();
	~DelayBuffer();

	void setBufferSize(double sampleRate); // set the buffer size
	void resetDelay(); // Initialize all delay elements with 0.0
	void newBuffer();
	void calculateValues(float delay, float fb, float wet, double sampleRate); // Take the input parameters 
																			   // and calclate the delay values
	void DelayBuffer::updateDelay(float delay, double sampleRate);
	void DelayBuffer::updateFeedback(float delay);
	void DelayBuffer::updateWetDry(float wet);
	float process(float xn); // Applies the actual delay processing
	float linInterp(float x1, float x2, float y1, float y2, float x);

	#define NULL 0

private:
	// Delay parameters
	float feedback;
	float wetLevel;
	float delayInSamples;

	// DDL parameters (Circular buffer)
	float* buffer;
	int bufferSize;
	int readIndex;
	int writeIndex;
};

#endif  // DELAYBUFFER_H_INCLUDED
