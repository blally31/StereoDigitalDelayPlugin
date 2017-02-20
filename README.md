# StereoDigitalDelayPlugin

A stereo digital delay VST3 plugin designed using the JUCE framework and algorithms and ideas from:

Will Pirkle (2012), Designing Audio Effect Plug-Ins in C++: With Digital Audio Signal Processing Theory. 1 Edition. Focal Press.

The delay has three variable parameters:
1. The amount of delay in ms
2. The amount of feedback as a %
3. The wet/dry ratio as a %

The project was designed to familiarise myself with the JUCE Cross-Platform C++ Framework as well as to practise theoretical DSP aspects learnt over the last few months.

The delay line is implemented using a circular buffer and could form the basis of many other more detailed delay-based effects such as cross-feedback delay, analog modelled delays and tap delays etc
