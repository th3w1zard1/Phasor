#pragma once

#include "../../../Common/Types.h"
#include "../../../Common/Streams.h"
#include "../Addresses.h"
#include <vector>

enum e_command_result;

namespace halo { namespace server { namespace maploader 
{
	void Initialize(COutStream& out);

	//Non-default map loading
	// --------------------------------------------------------------------
#ifdef PHASOR_PC
	// Returns the address of the loading buffer Halo should use
	char* GetLoadingMapBuffer();

	// Generates the map list
	// todo: fix for ce
	void BuildMapList(COutStream& out);

	// This function returns the address of our map table
	DWORD GetMapTable();

	// Checks if a map exists
	bool IsValidMap(const std::string& map);

	// Called when a map is being loaded.
	void OnMapLoad(char* map);

	// Called to fix the loaded map name
	void OnNewGame();

	// Returns the base name for a map (ie bloodgulch1 -> bloodgulch)
	bool GetBaseMapName(const char* actual_map, const char** out);
#endif	

	// Script loading
	// --------------------------------------------------------------------
	// 
	#pragma pack(push, 1)
	struct s_script_list
	{
		DWORD count;
		char** script_names;
	};
	struct s_mapcycle_entry
	{
		char* map;
		char* gametype;
		s_script_list* scripts;
		BYTE gametype_data[GAMET_BUFFER_SIZE];
	};
	static_assert(sizeof(s_mapcycle_entry) == CONST_MENTRY_SIZE, 
		"sizeof(s_mapcycle_entry) != CONST_MENTRY_SIZE");

	struct s_mapcycle_header
	{
		s_mapcycle_entry* games;
		DWORD cur_count;
		DWORD allocated_count;
		DWORD current; // index of game being executed
	};
	#pragma pack(pop)

	// Get a pointer to the current map in the playlist
	s_mapcycle_entry* GetCurrentMapcycleEntry();
/*	s_mapcycle_entry* GetMapcycleStart();
	s_mapcycle_entry* GetCurrentMapcycleEntry();

	// Set the pointer to the server's mapcycle
	void SetMapcycleStart(s_mapcycle_entry* new_map);

	// Number of entries in the mapcycle
	DWORD GetMapcycleCount();

	// Set number of entries in the mapcycle
	void SetMapcycleCount(DWORD new_count);

	// Clears the current mapcycle
	void ClearMapcycle();

	// Loads a map into the current mapcycle
	bool AddMapToCycle(const std::string& map, const std::wstring&, 
		std::vector<std::string>& scripts,
		COutStream& stream);*/

	e_command_result sv_mapcycle_begin(void*, 
		std::vector<std::string>& tokens, COutStream& out);
	e_command_result sv_mapcycle_add(void*, 
		std::vector<std::string>& tokens, COutStream& out);
	e_command_result sv_mapcycle_del(void* exec_player, 
		std::vector<std::string>& tokens, COutStream& out);
	e_command_result sv_mapcycle(void*, 
		std::vector<std::string>& tokens, COutStream& out);
	e_command_result sv_map(void*, 
		std::vector<std::string>& tokens, COutStream& out);
	e_command_result sv_end_game(void*,
		std::vector<std::string>&, COutStream&);
}}}