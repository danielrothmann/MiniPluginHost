/*
	==============================================================================

	Plugins Manager
	by Daniel Rothmann

	A wrapper class for the JUCE KnownPluginList for C# interop

	==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

/**
 * A wrapper class for the JUCE KnownPluginList for C# interop.
 */
class PluginsManager
{
public:
	PluginsManager();
	~PluginsManager();

	void scanAndAdd(char* filePath, bool dontRescanIfAlreadyInList);
	void rescanAll();
	void addToBlacklist(char* pluginID);
	void removeFromBlacklist(char* pluginID);
	void clearBlacklist();

	void createListFromXml(char* xmlKnownPluginList);
	const char* createXmlFromList();
	const char* getXmlPluginDescriptionForFile(char* filePath);
	const char* getXmlPluginDescriptionForId(char* pluginID);

private:
	ScopedPointer<KnownPluginList> pluginList;
	ScopedPointer<AudioPluginFormat> pluginFormat;
	OwnedArray<PluginDescription> descriptions;

	XmlElement* convertStringToXmlElement(char* data);
	const char* convertXmlElementToString(XmlElement* element);
};
