/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : error.h                                   *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : February 15, 2022                         *
 *                                                                            *
 *                    Last Update :                                           *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   To log error info during the game.                                       *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#include <cstdio>
#include <Windows.h>

#include "error.h"

static bool isFirstError = true;

/******************************************************************************
 * report -- Report the error.                                                *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   description -- The detail of the error.                           *
 *          category    -- The category can be omitted.                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
void report(const char* description, const char* category)
{
	FILE* fp;

#ifdef _DEBUG
	fp = stdout;
#else
	fopen_s(&fp, ERROR_FILE, "a");
#endif

	if (isFirstError)
	{
		isFirstError = false;
		SYSTEMTIME sysTime;

		GetLocalTime(&sysTime);
		fprintf(fp, "%hu/%hu/%hu ", sysTime.wYear, sysTime.wMonth, sysTime.wDay);
		fprintf(fp, "%hu:%hu\n", sysTime.wHour, sysTime.wMinute);
	}
	fprintf(fp, "%-20s : ", category ? category : "UNKNOWN");
	fprintf(fp, "%s\n", description ? description : "UNKNOWN");

#ifndef _DEBUG
	fclose(fp);
#endif
}

void wreport(const wchar_t* description, const wchar_t* category)
{
	FILE* fp;

#ifdef _DEBUG
	fp = stdout;
#else
	_wfopen_s(&fp, ERROR_FILE_W, L"a, ccs=UNICODE");
#endif

	if (isFirstError)
	{
		isFirstError = false;
		SYSTEMTIME sysTime;

		GetLocalTime(&sysTime);
		fwprintf(fp, L"%hu/%hu/%hu ", sysTime.wYear, sysTime.wMonth, sysTime.wDay);
		fwprintf(fp, L"%hu:%hu\n", sysTime.wHour, sysTime.wMinute);
	}
	fwprintf(fp, L"%-20s : ", category ? category : L"UNKNOWN");
	fwprintf(fp, L"%s\n", description ? description : L"UNKNOWN");

#ifndef _DEBUG
	fclose(fp);
#endif

}


/******************************************************************************
 * reportf -- Report the error with given format.                             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   format   -- The format to use in fprintf.                         *
 *          arg      -- The argument.                                         *
 *          category -- The category can be omitted.                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
void reportf(const char* format, const char* arg, const char* category)
{

	if ((!format) || (!arg))
		return;

	FILE* fp;

#ifdef _DEBUG
	fp = stdout;
#else
	fopen_s(&fp, ERROR_FILE, "a");
#endif

	if (isFirstError)
	{
		isFirstError = false;
		SYSTEMTIME sysTime;

		GetLocalTime(&sysTime);
		fprintf(fp, "%hu/%hu/%hu ", sysTime.wYear, sysTime.wMonth, sysTime.wDay);
		fprintf(fp, "%hu:%hu\n", sysTime.wHour, sysTime.wMinute);
	}
	fprintf(fp, "%-20s : ", category ? category : "UNKNOWN");
	fprintf(fp, format, arg);
	fprintf(fp, "\n");

#ifndef _DEBUG
	fclose(fp);
#endif
}

void wreportf(const wchar_t* format, const wchar_t* arg, const wchar_t* category)
{
	if ((!format) || (!arg))
		return;

	FILE* fp;

#ifdef _DEBUG
	fp = stdout;
#else
	_wfopen_s(&fp, ERROR_FILE_W, L"a, ccs=UNICODE");
#endif

	if (isFirstError)
	{
		isFirstError = false;
		SYSTEMTIME sysTime;

		GetLocalTime(&sysTime);
		fwprintf(fp, L"%hu/%hu/%hu ", sysTime.wYear, sysTime.wMonth, sysTime.wDay);
		fwprintf(fp, L"%hu:%hu\n", sysTime.wHour, sysTime.wMinute);
	}
	fwprintf(fp, L"%-20s : ", category ? category : L"UNKNOWN");
	fwprintf(fp, format, arg);
	fwprintf(fp, L"\n");

#ifndef _DEBUG
	fclose(fp);
#endif
}