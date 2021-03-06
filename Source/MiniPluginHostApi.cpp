/*
	==============================================================================

	MiniPluginHostAPI
	by Daniel Rothmann

	A native API exposing static plugin host methods for interop

	==============================================================================
*/

#include "MiniPluginHostApi.h"

extern "C" {
	PluginsManager* CreatePluginsManager()
	{
		return new PluginsManager();
	}

	void DeletePluginsManager(PluginsManager* manager)
	{
		delete manager;
	}

	bool ScanAndAdd(PluginsManager* manager, char* filePath, bool dontRescanIfAlreadyInList)
	{
		return manager->scanAndAdd(filePath, dontRescanIfAlreadyInList);
	}

	bool ScanDirectory(PluginsManager* manager, char* path, bool dontRescanIfAlreadyInList, bool searchRecursive)
	{
		return manager->scanDirectory(path, dontRescanIfAlreadyInList, searchRecursive);
	}

	void RescanAll(PluginsManager* manager)
	{
		manager->rescanAll();
	}

	void AddToBlacklist(PluginsManager* manager, char* pluginId)
	{
		manager->addToBlacklist(pluginId);
	}

	void RemoveFromBlacklist(PluginsManager* manager, char* pluginId)
	{
		manager->removeFromBlacklist(pluginId);
	}

	void ClearBlacklist(PluginsManager* manager)
	{
		manager->clearBlacklist();
	}

	void CreateListFromXml(PluginsManager* manager, char* xmlKnownPluginsList)
	{
		manager->createListFromXml(xmlKnownPluginsList);
	}

	const char* CreateXmlFromList(PluginsManager* manager)
	{
		// Allocate new memory for string and return pointer.
		tempString = String(manager->createXmlFromList());
		auto* pointer = static_cast<const char*>(tempString.toUTF8());
		return pointer;
	}

	const char* GetXmlPluginDescriptionForFile(PluginsManager* manager, char* filePath)
	{
		tempString = String(manager->getXmlPluginDescriptionForFile(filePath));
		auto* pointer = static_cast<const char*>(tempString.toUTF8());
		return pointer;
	}

	const char* GetXmlPluginDescriptionForId(PluginsManager* manager, char* pluginId)
	{
		tempString = String(manager->getXmlPluginDescriptionForId(pluginId));
		auto* pointer = static_cast<const char*>(tempString.toUTF8());
		return pointer;
	}

	PluginHost* CreatePluginHost()
	{
		return new PluginHost();
	}

	void DeletePluginHost(PluginHost* host)
	{
		delete host;
	}

	bool InstantiatePlugin(PluginHost* host, char* xmlPluginDescription, double sampleRate, int bufferSize)
	{
		return host->instantiatePlugin(xmlPluginDescription, sampleRate, bufferSize);
	}

	void PrepareToPlay(PluginHost* host, double sampleRate, int expectedSamplesPerBlock)
	{
		host->prepareToPlay(sampleRate, expectedSamplesPerBlock);
	}

	bool SuspendPlugin(PluginHost* host, bool shouldBeSuspended)
	{
		return host->suspendPlugin(shouldBeSuspended);
	}

	bool ReleasePlugin(PluginHost* host)
	{
		return host->releasePlugin();
	}

	void ProcessBlock(PluginHost* host, float* buffer, int bufferSize, int numChannels)
	{
		host->processBlock(buffer, bufferSize, numChannels);
	}

	int GetNumInputs(PluginHost* host)
	{
		return host->getNumInputs();
	}

	int GetNumOutputs(PluginHost* host)
	{
		return host->getNumOutputs();
	}

	int GetNumParameters(PluginHost* host)
	{
		return host->getNumParameters();
	}

	int GetNumNamedParameters(PluginHost* host)
	{
		return host->getNumNamedParameters();
	}

	const char* GetParameterName(PluginHost* host, int index)
	{
		tempString = String(host->getParameterName(index));
		auto* pointer = static_cast<const char*>(tempString.toUTF8());
		return pointer;
	}

	float GetValueByName(PluginHost* host, char* name)
	{
		return host->getValueByName(name);
	}

	bool SetValueByName(PluginHost* host, char* name, float value)
	{
		return host->setValueByName(name, value);
	}

	float GetValueByIndex(PluginHost* host, int index)
	{
		return host->getValueByIndex(index);
	}

	bool SetValueByIndex(PluginHost* host, int index, float value)
	{
		return host->setValueByIndex(index, value);
	}

}