/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : straw.h                                   *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : February 8, 2022                          *
 *                                                                            *
 *                    Last Update :                                           *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For .ini file reading and writing.                                       *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _STRAW_H_
#define _STRAW_H_

#include <string>

#include "define.h"


// String value can't exceed this size.
const int STRAW_BUFFER_SIZE = 60;
const wchar_t DEFAULT_BUFFER[STRAW_BUFFER_SIZE] = L"NULL";


class Straw
{
public:
	Straw(const std::wstring& file = L"", const std::wstring& section = L"");
	~Straw();

	void setFile(const std::wstring& file);
	void setSection(const std::wstring& section);

	// Read value from .ini file.
	int suckInt(const std::wstring& key, const int def = 0);
	int suckInt(const std::wstring& file, const std::wstring& section, const std::wstring& key, const int def = 0);

	std::wstring suckString(const std::wstring& key, const std::wstring& def = L"");
	std::wstring suckString(const std::wstring& file, const std::wstring& section, const std::wstring& key, const std::wstring& def = L"");

	double suckDouble(const std::wstring& key, const double def = 0.0);
	double suckDouble(const std::wstring& file, const std::wstring& section, const std::wstring& key, const double def = 0.0);

	Coord suckCoord(const std::wstring& key, const Coord& def = ZERO_COORD);
	Coord suckCoord(const std::wstring& file, const std::wstring& section, const std::wstring& key, const Coord& def = ZERO_COORD);

	// Write value to .ini file.
	bool exhale(const int val, const std::wstring& key);
	bool exhale(const int val, const std::wstring& file, const std::wstring& section, const std::wstring& key);

	bool exhale(const std::wstring& val, const std::wstring& key);
	bool exhale(const std::wstring& val, const std::wstring& file, const std::wstring& section, const std::wstring& key);

	bool exhale(const double val, const std::wstring& key);
	bool exhale(const double val, const std::wstring& file, const std::wstring& section, const std::wstring& key);

	bool exhale(const Coord& val, const std::wstring& key);
	bool exhale(const Coord& val, const std::wstring& file, const std::wstring& section, const std::wstring& key);

	bool good() const;
	void clear();

private:
	bool suck(const std::wstring& file, const std::wstring& section, const std::wstring& key);

	std::wstring m_file;
	std::wstring m_section;

	wchar_t m_buffer[STRAW_BUFFER_SIZE];

	bool m_flag;
};

#endif