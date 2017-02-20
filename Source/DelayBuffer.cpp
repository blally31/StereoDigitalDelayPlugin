/*
  ==============================================================================

    DelayBuffer.cpp
    Created: 8 Feb 2017 6:32:18pm
    Author:  Brendan

  ==============================================================================
*/

#include "DelayBuffer.h"

DelayBuffer::DelayBuffer()
{
	buffer = NULL;
	readIndex = 0;
	writeIndex = 0;
	bufferSize = 0;
	//sampleRate = 0;

	feedback = 0;
	wetLevel = 0;
	delayInSamples = 0;
}

DelayBuffer::~DelayBuffer()
{
	delete[] buffer;
}


//---------------------------------------------------------------------------------
//Function to set the size of the buffer based on the current sample rate
//---------------------------------------------------------------------------------
void DelayBuffer::setBufferSize(double sampleRate)
{
	// maximum delay size is 2ms (2 x fs)
	bufferSize = 2 * sampleRate;
}

//---------------------------------------------------------------------------------
//Function to reset the delay by setting the buffer values to 0 and resetting the
//read and write indexes
//---------------------------------------------------------------------------------
void DelayBuffer::resetDelay()
{
	if (buffer != NULL)
	{
		memset(buffer, 0, bufferSize * sizeof(float));
	}
	writeIndex = 0; // reset the write index to the top
	readIndex = 0; // reset the read index to the top
}


//---------------------------------------------------------------------------------
//Function to create a new buffer
//---------------------------------------------------------------------------------
void DelayBuffer::newBuffer()
{
	if (buffer == NULL)
	{
		delete [] buffer;
	}
	
	buffer = new float[bufferSize];

	resetDelay();
}


//---------------------------------------------------------------------------------
//Function to calculate the required delay values from the user controlled GUI 
//parameters. Sets the read index based on the delay value (samples)
//---------------------------------------------------------------------------------
void DelayBuffer::calculateValues(float delay, float fb, float wet, double sr)
{
	//sampleRate = sr;
	delayInSamples = (int)(delay * sr/1000.0);
	feedback = fb / 100;
	wetLevel = wet / 100;

	// determine read index
	readIndex = writeIndex - (int)delayInSamples;

	// check and wrap backwards if the index is negative
	if (readIndex < 0)
	{
		readIndex += bufferSize;
	}
}

void DelayBuffer::updateDelay(float delay, double sampleRate)
{
	delayInSamples = (int)(delay * sampleRate/1000.0);

	// determine read index
	readIndex = writeIndex - (int)delayInSamples;

	// check and wrap backwards if the index is negative
	if (readIndex < 0)
	{
		readIndex += bufferSize;
	}
}

void DelayBuffer::updateFeedback(float fb)
{
	feedback = fb / 100;
}

void DelayBuffer::updateWetDry(float wet)
{
	wetLevel = wet / 100;
}


//---------------------------------------------------------------------------------
//Function to process each incoming sample and calculate the delayed sample to output
//---------------------------------------------------------------------------------
float DelayBuffer::process(float xn)
{
	// get the current delay sample from the read index
	float yn = buffer[readIndex];

	// if the delay is less than one sample set y(n) = x(n)
	if (readIndex == writeIndex && delayInSamples < 1.00)
	{
		yn = xn;
	}
	// the read index at the previous sample y(n - 1)
	int readIndex_1 = readIndex - 1;
	
	if (readIndex_1 < 0)
	{
		readIndex_1 = bufferSize - 1;
	}

	// get y(n - 1)
	float yn_1 = buffer[readIndex_1];

	// calculate the fractional component of the delay
	// eg. 0.345 = 1.345 - 1
	float fracDelay = delayInSamples - (int)delayInSamples;

	float interpolation = linInterp(0, 1, yn, yn_1, fracDelay);

	// if there is zero delay, then y(n) = x(n)
	if (delayInSamples == 0)
	{
		yn = xn;
	}
	else
	{
		yn = interpolation;
	}

	buffer[writeIndex] = xn + feedback * yn;

	// y(n) = wet * y(n) + (1 - wet) * x(n)
	float output = wetLevel * yn + (1 - wetLevel) * xn;

	writeIndex++;
	if (writeIndex >= bufferSize)
	{
		writeIndex = 0;
	}
	
	readIndex++;
	if (readIndex >= bufferSize)
	{
		readIndex = 0;
	}

	return output;
}


//---------------------------------------------------------------------------------
//Function that uses linear interpolation
//---------------------------------------------------------------------------------
float DelayBuffer::linInterp(float x1, float x2, float y1, float y2, float x)
{
	float denom = x2 - x1;
	if (denom == 0)
	{
		return y1;
	}
	// calculate decimal position of x
	float dx = (x - x1) / (x2 - x1);

	// use weighted sum method of interpolating
	float result = dx*y2 + (1 - dx)*y1;

	return result;
}
