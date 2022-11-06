/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : audio.h                                   *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : February 22, 2022                         *
 *                                                                            *
 *                    Last Update :                                           *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For the sound of the game.                                               *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/


#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <stack>
#include <vector>

#include "inc/fmod.hpp"
#include "inc/fmod_errors.h"

#ifdef _WIN64
#pragma comment(lib,"lib/x64/fmod_vc.lib") 
#else 
#pragma comment(lib,"lib/x86/fmod_vc.lib") 
#endif

#include "tinyxml.h"


/********************************************************************
** Basic sound.
*/
struct Sound
{
	FMOD::Sound* sound;
	FMOD::Channel* channel;

	Sound() : sound(nullptr), channel(nullptr) {}
};


/********************************************************************
** The play list to loop.
*/
class MusicList
{
public:
	MusicList();
	~MusicList();

	MusicList* add(Sound audio);

	void play();
	void stop();
	void setPaused(bool pause);
	void playNext();
	void playPrev();

	void update();

	void clear();

	bool load(XMLElement* parent);

	size_t size();

private:
	friend class MusicManager;

	std::vector<Sound> playList;
	std::vector<Sound>::iterator curMusic;
	bool isPaused;
	bool isRandom;
};


/********************************************************************
** It handles all.
*/
class MusicManager
{
public:
	MusicManager();
	~MusicManager();

	void push(MusicList* newList);
	void pop();

	void update();

	MusicList* getList();

private:
	std::stack<MusicList*> playStack;
	MusicList* curList;
};



/**********************************************************
** Initialize and close the audio system.
*/
bool initAudio();
bool closeAudio();


/**********************************************************
** This one... new a sound.
*/
Sound getStream(const char* name);
bool getStream(const char* name, Sound* snd);


#endif