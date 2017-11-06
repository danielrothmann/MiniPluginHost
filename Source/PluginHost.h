/*
  ==============================================================================

    PluginHost
	by Daniel Rothmann
	This is a tiny audio plugin host which can take care of plugin instantiation
	as well as processing blocks with plugin and setting parameters.

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

/**
* A tiny audio plugin host which can instantiate plugins, process audio and set parameters.
*/
class PluginHost
{
public:
	PluginHost();
	~PluginHost();

	bool instantiatePlugin(char* xmlPluginDescription, double sampleRate, int bufferSize);
	bool suspendPlugin(bool shouldBeSuspended);
	bool releasePlugin();

	void processBlock(float* buffer, int bufferLength, int numChannels);

	int getNumInputs();
	int getNumOutputs();

	int getNumParameters();
	const char* getParameterName(int index);
	float getValueByName(char* name);
	bool setValueByName(char* name, float value);
	float getValueByIndex(int index);
	bool setValueByIndex(int index, float value);

private:
	AudioProcessorParameter* getParameterByName(char* name);

	ScopedPointer<AudioPluginFormatManager> formatManager;
	ScopedPointer<AudioPluginInstance> pluginInstance;
	ScopedPointer<PluginDescription> pluginDescription;
	ScopedPointer<AudioProcessorEditor> pluginEditor;
	bool pluginInstantiated = false;

	ScopedPointer<AudioBuffer<float>> audioData;
	ScopedPointer<MidiBuffer> midiData;

	int maxNameLength = 50;
};
