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

	bool scanAndAdd(char* filePath, bool dontRescanIfAlreadyInList);
	bool scanDirectory(char* path, bool dontRescanIfAlreadyInList, bool searchRecursive);
	void rescanAll();
	void addToBlacklist(char* pluginID);
	void removeFromBlacklist(char* pluginID);
	void clearBlacklist();

	void createListFromXml(char* xmlKnownPluginList);
	String createXmlFromList();
	String getXmlPluginDescriptionForFile(char* filePath);
	String getXmlPluginDescriptionForId(char* pluginID);

private:
	ScopedPointer<KnownPluginList> pluginList;
	ScopedPointer<AudioPluginFormat> pluginFormat;
	OwnedArray<PluginDescription> descriptions;

	XmlElement* convertStringToXmlElement(char* data);
	String convertXmlElementToString(XmlElement* element);
};
