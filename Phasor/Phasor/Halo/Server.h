#pragma once

#include "../../Common/Types.h"

namespace halo { namespace server
{
	
	// Called for console events (exit etc)
	void __stdcall ConsoleHandler(DWORD fdwCtrlType);

	// Called periodically by Halo to check for console input, I use for timers
	void __stdcall OnConsoleProcessing();

	// Called when a console command is to be executed
	bool __stdcall ProcessCommand(char* command);

	// Called when a map is being loaded
	bool __stdcall OnMapLoad(LPBYTE mapData);

	// Called when the server (not Phasor) wants to print a message.
	void __stdcall OnHaloPrint(char* msg);

	// Called when halo checks a player's hash
	bool __stdcall OnHaloBanCheck(char* hash);

	// Called when the server info is about to be broadcast
	bool __stdcall OnVersionBroadcast(DWORD arg1, DWORD arg2);

} }