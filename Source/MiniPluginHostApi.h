/*
  ==============================================================================

    MiniPluginHostAPI
	by Daniel Rothmann

	A native API exposing static plugin host methods for interop

  ==============================================================================
*/

#pragma once
#include "PluginsManager.h"
#include "PluginHost.h"

#define HOST_API __declspec(dllexport)

extern "C" {
	// Exposed methods related to plugins manager
	HOST_API PluginsManager* CreatePluginsManager();
	HOST_API void DeletePluginsManager(PluginsManager* manager);
	HOST_API void ScanAndAdd(PluginsManager* manager, char* filePath, bool dontRescanIfAlreadyInList);
	HOST_API void RescanAll(PluginsManager* manager);
	HOST_API void AddToBlacklist(PluginsManager* manager, char* pluginId);
	HOST_API void RemoveFromBlacklist(PluginsManager* manager, char* pluginId);
	HOST_API void ClearBlacklist(PluginsManager* manager);
	HOST_API void CreateListFromXml(PluginsManager* manager, char* xmlKnownPluginsList);
	HOST_API const char* CreateXmlFromList(PluginsManager* manager);
	HOST_API const char* GetXmlPluginDescriptionForFile(PluginsManager* manager, char* filePath);
	HOST_API const char* GetXmlPluginDescriptionForId(PluginsManager* manager, char* pluginId);

	// Exposed methods related to plugin host
	HOST_API PluginHost* CreatePluginHost();
	HOST_API void DeletePluginHost(PluginHost* host);
	HOST_API bool InstantiatePlugin(PluginHost* host, char* xmlPluginDescription, double sampleRate, int bufferSize);
	HOST_API bool SuspendPlugin(PluginHost* host, bool shouldBeSuspended);
	HOST_API bool ReleasePlugin(PluginHost* host);
	HOST_API void ProcessBlock(PluginHost* host, float* buffer, int bufferSize, int numChannels);
	HOST_API int GetNumInputs(PluginHost* host);
	HOST_API int GetNumOutputs(PluginHost* host);
	HOST_API int GetNumParameters(PluginHost* host);
	HOST_API const char* GetParameterName(PluginHost* host, int index);
	HOST_API float GetValueByName(PluginHost* host, char* name);
	HOST_API bool SetValueByName(PluginHost* host, char* name, float value);
	HOST_API float GetValueByIndex(PluginHost* host, int index);
	HOST_API bool SetValueByIndex(PluginHost* host, int index, float value);
}

String tempString;