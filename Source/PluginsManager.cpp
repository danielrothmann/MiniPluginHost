/*
  ==============================================================================

    Plugins Manager
	by Daniel Rothmann

	A wrapper class for the JUCE KnownPluginList for C# interop

  ==============================================================================
*/

#include "PluginsManager.h"

/**
*Constructs a plugins manager which keeps track of VST plugins and provides plugin descriptions.
*/
PluginsManager::PluginsManager()
{
	pluginList = new KnownPluginList();
	pluginFormat = new VST3PluginFormat();
	descriptions = OwnedArray<PluginDescription>();
}

PluginsManager::~PluginsManager()
{
}

/**
*Scans a VST plugin and adds it to the list of known plugins.
*@param filePath The path to the plugin file.
*@param dontRescanIfAlreadyInList Wether the plugin should be rescanned if it is already in the list of known plugins.
*/
bool PluginsManager::scanAndAdd(char* filePath, bool dontRescanIfAlreadyInList)
{
	return pluginList->scanAndAddFile(filePath, dontRescanIfAlreadyInList, descriptions, *pluginFormat);
}

bool PluginsManager::scanDirectory(char* path, bool dontRescanIfAlreadyInList, bool searchRecursive)
{
	int numPluginsScanned = 0;
	FileSearchPath searchPath = FileSearchPath(path);

	PluginDirectoryScanner* scanner = new PluginDirectoryScanner(	*pluginList, 
																	*pluginFormat, 
																	searchPath, 
																	searchRecursive, 
																	File());
	bool shouldSearch = true;
	String scannedPluginName = "";

	while(shouldSearch)
	{
		shouldSearch = scanner->scanNextFile(dontRescanIfAlreadyInList, scannedPluginName);

		if (shouldSearch)
			numPluginsScanned++;
	}

	delete scanner;
	return numPluginsScanned >= 1; // TODO: This returns false when one correct vst was scanned
}

/**
*Rescans all plugins the list of known plugins and blacklists them if issues arise.
*/
void PluginsManager::rescanAll()
{
	// TODO: Loop through all plugins in list and scan them, blacklist if there are problems.
}

/**
*Adds a plugin to the blacklist.
*@param pluginID The identifier string of the plugin to be added.
*/
void PluginsManager::addToBlacklist(char* pluginID)
{
	pluginList->addToBlacklist(String(pluginID));
}

/**
*Removes a plugin from the blacklist.
*@param pluginID The identifier string of the plugin to be removed.
*/
void PluginsManager::removeFromBlacklist(char* pluginID)
{
	pluginList->removeFromBlacklist(String(pluginID));
}

/**
*Removes all entries in the blacklist.
*/
void PluginsManager::clearBlacklist()
{
	pluginList->clearBlacklistedFiles();
}

/**
*Parses string as XML element and recreates known plugin list from XML.
*/
void PluginsManager::createListFromXml(char* xmlKnownPluginList)
{
	pluginList->recreateFromXml(*convertStringToXmlElement(xmlKnownPluginList));
}

/**
*Formats known plugin list as XML and returns it.
*@return A string containing list formatted as XML.
*/
String PluginsManager::createXmlFromList()
{
	return convertXmlElementToString(pluginList->createXml());
}

/**
*Formats plugin at file path as XML and returns it.
*@param filePath The file path from which to get plugin.
*@return A string containing plugin description formatted as XML. If plugin wasn't found, nullptr is returned.
*/
String PluginsManager::getXmlPluginDescriptionForFile(char* filePath)
{
	auto description = pluginList->getTypeForFile(filePath);

	if (description)
	{
		return convertXmlElementToString(description->createXml());
	}

	return "";
}

/**
*Formats plugin with ID as XML and returns it.
*@param pluginID The identifier string of the plugin.
*@return A string containing plugin description formatted as XML. If plugin wasn't found, nullptr is returned.
*/
String PluginsManager::getXmlPluginDescriptionForId(char* pluginID)
{
	auto description = pluginList->getTypeForIdentifierString(pluginID);

	if (description)
	{
		return convertXmlElementToString(description->createXml());
	}

	return "";
}

/**
*Parses a string as an XML element.
*@param data The string to be parsed.
*@return An XMLElement parsed from string.
*/
XmlElement* PluginsManager::convertStringToXmlElement(char* data)
{
	auto text = String(data);
	return XmlDocument::parse(text);
}

/**
*Formats an XML element as a string.
*@param element The element to be formatted.
*@return An string representing the XML element.
*/
String PluginsManager::convertXmlElementToString(XmlElement* element)
{
	return element->createDocument("");
}
