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
 *                    Last Update : February 16, 2022                         *
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

#include <cstring>
#include <Windows.h>

#include "straw.h"
#include "auxilliary.h"


/******************************************************************************
 * Straw::Straw -- Constructor of the object.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   file    -- Default file name.                                     *
 *          section -- Default section name.                                  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/05 Tony : Created.                                               *
 *============================================================================*/
Straw::Straw(const std::wstring& file, const std::wstring& section)
{
	m_file = file;
	m_section = section;

	m_flag = true;
}


/******************************************************************************
 * Straw::~Straw -- Deconstructor of the object.                              *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/05 Tony : Created.                                               *
 *============================================================================*/
Straw::~Straw() {}


/******************************************************************************
 * Straw::setFile -- Set the defult file of the straw.                        *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   file -- New defult file.                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/05 Tony : Created.                                               *
 *============================================================================*/
void Straw::setFile(const std::wstring& file)
{
	m_file = file;
}


/******************************************************************************
 * Straw::setSection -- Set the default section of the straw.                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   section -- New default section.                                   *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/05 Tony : Created.                                               *
 *============================================================================*/
void Straw::setSection(const std::wstring& section)
{
	m_section = section;
}


/******************************************************************************
 * Straw::suckInt -- Suck an integer from custom file and section.            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   key     -- The key.                                               *
 *          def     -- The default value.                                     *
 *                                                                            *
 * OUTPUT:  Return the value.                                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/07 Tony : Created.                                               *
 *============================================================================*/
int Straw::suckInt(const std::wstring& key, const int def)
{
	return suckInt(m_file, m_section, key, def);
}


/******************************************************************************
 * Straw::suckInt -- Suck an integer from custom file and section.            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   file    -- The ini file name.                                     *
 *          section -- The section of the value.                              *
 *          key     -- The key.                                               *
 *          def     -- The default value.                                     *
 *                                                                            *
 * OUTPUT:  Return the value of the key.                                      *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/07 Tony : Created.                                               *
 *============================================================================*/
int Straw::suckInt(const std::wstring& file, const std::wstring& section, const std::wstring& key, const int def)
{
	if (suck(file, section, key))
		return parseInt(m_buffer);
	else
		return def;
}


/******************************************************************************
 * Straw::suckString -- Suck a string from default file and section.          *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   key -- The key.                                                   *
 *          def -- The default value.                                         *
 *                                                                            *
 * OUTPUT:  Return the value.                                                 *
 *                                                                            *
 * WARNINGS:  Return the value.                                               *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/07 Tony : Created.                                               *
 *============================================================================*/
std::wstring Straw::suckString(const std::wstring& key, const std::wstring& def)
{
	return suckString(m_file, m_section, key, def);
}


/******************************************************************************
 * Straw::suckString -- Get a string from custom file and section.            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   file    -- The ini file name.                                     *
 *          section -- The section of the value.                              *
 *          key     -- The key.                                               *
 *          def     -- The default value.                                     *
 *                                                                            *
 * OUTPUT:  Return the value.                                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/05 Tony : Created.                                               *
 *============================================================================*/
std::wstring Straw::suckString(const std::wstring& file, const std::wstring& section, const std::wstring& key, const std::wstring& def)
{
	if (suck(file, section, key))
		return m_buffer;
	else
		return def;
}


/******************************************************************************
 * Straw::suckDouble -- Suck a double from default file and section.          *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   key -- The key.                                                   *
 *          def -- The default value.                                         *
 *                                                                            *
 * OUTPUT:  Return the value.                                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
double Straw::suckDouble(const std::wstring& key, const double def)
{
	return suckDouble(m_file, m_section, key, def);
}


/******************************************************************************
 * Straw::suckDouble -- Get a double from custom file and section.            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   file    -- The ini file name.                                     *
 *          section -- The section of the value.                              *
 *          key     -- The key.                                               *
 *          def     -- The default value.                                     *
 *                                                                            *
 * OUTPUT:  Return the value.                                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
double Straw::suckDouble(const std::wstring& file, const std::wstring& section, const std::wstring& key, const double def)
{
	if (suck(file, section, key))
		return std::stod(m_buffer);
	else
		return def;
}


/******************************************************************************
 * Straw::suckCoord -- Suck a coordinate from default file and section.       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   key -- The key.                                                   *
 *          def -- The default value.                                         *
 *                                                                            *
 * OUTPUT:  Return the value.                                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
Coord Straw::suckCoord(const std::wstring& key, const Coord& def)
{
	return suckCoord(m_file, m_section, key, def);
}


/******************************************************************************
 * Straw::suckCoord -- Get a Coord from custom file and section.              *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   file    -- The ini file name.                                     *
 *          section -- The section of the value.                              *
 *          key     -- The key.                                               *
 *          def     -- The default value.                                     *
 *                                                                            *
 * OUTPUT:  Return the value.                                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
Coord Straw::suckCoord(const std::wstring& file, const std::wstring& section, const std::wstring& key, const Coord& def)
{
	if (suck(file, section, key))
		return parseCoord(m_buffer);
	else
		return def;
}



/******************************************************************************
 * Straw::exhale -- Write value to .ini file.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   val -- The value to write.                                        *
 *          key -- The key of the value.                                      *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
bool Straw::exhale(const int val, const std::wstring& key)
{
	return exhale(val, m_file, m_section, key);
}


/******************************************************************************
 * Straw::exhale -- Write value to .ini file.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   val     -- The value to write.                                    *
 *          file    -- The file of the value.                                 *
 *          section -- The section of the value.                              *
 *          key     -- The key of the value.                                  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
bool Straw::exhale(const int val, const std::wstring& file, const std::wstring& section, const std::wstring& key)
{
	return WritePrivateProfileString(
		section.c_str(),
		key.c_str(),
		std::to_wstring(val).c_str(),
		file.c_str());
}


/******************************************************************************
 * Straw::exhale -- Write value to .ini file.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   val -- The value to write.                                        *
 *          key -- The key of the value.                                      *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
bool Straw::exhale(const std::wstring& val, const std::wstring& key)
{
	return exhale(val, m_file, m_section, key);
}


/******************************************************************************
 * Straw::exhale -- Write value to .ini file.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   val     -- The value to write.                                    *
 *          file    -- The file of the value.                                 *
 *          section -- The section of the value.                              *
 *          key     -- The key of the value.                                  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
bool Straw::exhale(const std::wstring& val, const std::wstring& file, const std::wstring& section, const std::wstring& key)
{
	return WritePrivateProfileString(
		section.c_str(),
		key.c_str(),
		val.c_str(),
		file.c_str());
}


/******************************************************************************
 * Straw::exhale -- Write value to .ini file.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   val -- The value to write.                                        *
 *          key -- The key of the value.                                      *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
bool Straw::exhale(const double val, const std::wstring& key)
{
	return exhale(val, m_file, m_section, key);
}


/******************************************************************************
 * Straw::exhale -- Write value to .ini file.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   val     -- The value to write.                                    *
 *          file    -- The file of the value.                                 *
 *          section -- The section of the value.                              *
 *          key     -- The key of the value.                                  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
bool Straw::exhale(const double val, const std::wstring& file, const std::wstring& section, const std::wstring& key)
{
	return WritePrivateProfileString(
		section.c_str(),
		key.c_str(),
		std::to_wstring(val).c_str(),
		file.c_str());
}


/******************************************************************************
 * Straw::exhale -- Write value to .ini file.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   val -- The value to write.                                        *
 *          key -- The key of the value.                                      *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
bool Straw::exhale(const Coord& val, const std::wstring& key)
{
	return exhale(val, m_file, m_section, key);
}


/******************************************************************************
 * Straw::exhale -- Write value to .ini file.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   val     -- The value to write.                                    *
 *          file    -- The file of the value.                                 *
 *          section -- The section of the value.                              *
 *          key     -- The key of the value.                                  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
bool Straw::exhale(const Coord& val, const std::wstring& file, const std::wstring& section, const std::wstring& key)
{
	std::wstring value;

	value = std::to_wstring(val.x) + L" " + std::to_wstring(val.y);

	return WritePrivateProfileString(
		section.c_str(),
		key.c_str(),
		value.c_str(),
		file.c_str());
}


/******************************************************************************
 * Straw::gool -- Get the state of the straw.                                 *
 *                                                                            *
 *    If straw cannot find certain key, it will set its flag to false and     *
 *    continue.                                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/16 Tony : Created.                                               *
 *============================================================================*/
bool Straw::good() const
{
	return m_flag;
}


/******************************************************************************
 * Straw::clear -- Clear the flag.                                            *
 *                                                                            *
 *    This will set the flag to true, to check next error.                    *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/16 Tony : Created.                                               *
 *============================================================================*/
void Straw::clear()
{
	m_flag = true;
}


/******************************************************************************
 * Straw::suck -- Suck value to buffer.                                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/16 Tony : Created.                                               *
 *============================================================================*/
bool Straw::suck(const std::wstring& file, const std::wstring& section, const std::wstring& key)
{
	GetPrivateProfileString(
		section.c_str(),
		key.c_str(),
		DEFAULT_BUFFER,
		m_buffer,
		STRAW_BUFFER_SIZE,
		file.c_str());

	if (wcscmp(m_buffer, DEFAULT_BUFFER) == 0)
	{
		m_flag = false;
		return false;
	}

	return true;
}