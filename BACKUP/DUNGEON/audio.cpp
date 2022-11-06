/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : audio.cpp                                 *
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

#include <cstdlib>

#include "error.h"
#include "audio.h"
#include "config.h"
#include "tinyxml.h"
#include "auxilliary.h"


extern Setting setting;

static FMOD::System* audioSystem;


MusicManager musicPanel;

/******************************************************************************
 * MusicList::MusicList -- Constructor of the object.                         *
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
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
MusicList::MusicList()
{
	curMusic = playList.end();
	isPaused = false;
	isRandom = false;
}


/******************************************************************************
 * MusicList::~MusicList -- Deconstructor of the object.                      *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember to clear the sounds.                                   *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
MusicList::~MusicList()
{
	for (auto it = playList.begin(); it != playList.end(); it++)
		it->sound->release();
}


/******************************************************************************
 * MusicList::add -- Add sounds to the list.                                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   audio -- The new audio.                                           *
 *                                                                            *
 * OUTPUT:  Return itself.                                                    *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
MusicList* MusicList::add(Sound audio)
{
	playList.push_back(audio);
	if (isRandom)
		curMusic = playList.begin() + random(0, (int)(playList.size() - 1));
	else
		curMusic = playList.end() - 1;
	
	return this;
}


/******************************************************************************
 * MusicList::play -- Start to play.                                          *
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
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
void MusicList::play()
{
	audioSystem->playSound(curMusic->sound, nullptr, false, &(curMusic->channel));
	curMusic->channel->setVolume((float)setting.musicVolume);
}


/******************************************************************************
 * MusicList::stop -- Stop playing.                                           *
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
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
void MusicList::stop()
{
	if (curMusic != playList.end())
		curMusic->channel->stop();
}


/******************************************************************************
 * MusicList::setPaused -- Set the play list to pause or continue.            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   pause -- If true, then pause.                                     *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
void MusicList::setPaused(bool pause)
{
	isPaused = pause;
	if (curMusic != playList.end())
		(*curMusic).channel->setPaused(pause);
}


/******************************************************************************
 * MusicList::playNext -- Play next sound.                                    *
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
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
void MusicList::playNext()
{
	if (curMusic == playList.end())
		return;

	if (isRandom)
		curMusic = playList.begin() + random(0, (int)(playList.size() - 1));
	else
	{
		curMusic++;
		if (curMusic == playList.end())
			curMusic = playList.begin();
	}

	play();
}


/******************************************************************************
 * MusicList::playPrev -- Play previous sound.                                *
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
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
void MusicList::playPrev()
{
	if (curMusic == playList.end())
		return;

	if (isRandom)
		curMusic = playList.begin() + random(0, (int)(playList.size() - 1));
	else
	{
		if (curMusic == playList.begin())
			curMusic = playList.end() - 1;
		else
			curMusic--;
	}

	play();
}


/******************************************************************************
 * MusicList::update -- Update play list.                                     *
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
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
void MusicList::update()
{
	if (curMusic == playList.end())
		return;

	bool isPlay;
	curMusic->channel->isPlaying(&isPlay);
	if (!isPlay)
		playNext();

	curMusic->channel->setVolume((float)setting.musicVolume);
}


/******************************************************************************
 * MusicList::clear -- Clear the play list.                                   *
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
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
void MusicList::clear()
{
	for (auto it = playList.begin(); it != playList.end(); it++)
		it->sound->release();
	playList.clear();
}


/******************************************************************************
 * MusicList::load -- Load a xml node.                                        *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   parent -- xml node.                                               *
 *                                                                            *
 * OUTPUT:  Return whether succeeded or not.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
bool MusicList::load(XMLElement* parent)
{
	XMLElement* child = parent->FirstChildElement();
	const char* soundName;
	Sound snd;

	parseXMLAttribute(&isRandom, parent->Attribute("random"));

	while (child != NULL)
	{
		soundName = child->GetText();
		if (isAccessible(soundName))
		{
			if (getStream(soundName, &snd))
				add(snd);
			else
			{
				reportf(FAILED_TO_LOAD_F, soundName, LOAD_SOUND);
				return false;
			}
		}
		else
		{
			reportf(FAILED_TO_LOAD_F, soundName, LOAD_SOUND);
			return false;
		}

		child = child->NextSiblingElement();
	}

	return true;
}


/******************************************************************************
 * MusicList::size -- Get the size of the list.                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the size of the list.                                      *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
size_t MusicList::size()
{
	return playList.size();
}



/******************************************************************************
 * MusicManager::MusicManager -- Constructor of the object.                   *
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
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
MusicManager::MusicManager()
{
	curList = nullptr;
}


/******************************************************************************
 * MusicManager::~MusicManager -- Deconstructor of the object.                *
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
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
MusicManager::~MusicManager() {}


/******************************************************************************
 * MusicManager::push -- Push a play list to the manager.                     *
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
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
void MusicManager::push(MusicList* newList)
{
	if (curList)
		curList->setPaused(true);

	curList = newList;
	playStack.push(newList);
}


/******************************************************************************
 * MusicManager::pop -- Pop the latest list.                                  *
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
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
void MusicManager::pop()
{
	if (!curList)
		return;

	curList->stop();
	playStack.pop();

	if (playStack.empty())
	{
		curList = nullptr;
		return;
	}

	curList = playStack.top();

	curList->setPaused(false);
}


/******************************************************************************
* MusicManager::update -- Update the current list.                           *
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
*   2022/02/22 Tony : Created.                                               *
*============================================================================*/
void MusicManager::update()
{
	if (curList)
		curList->update();
}


/******************************************************************************
* MusicManager::getList -- Get current music list.                           *
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
*   2022/02/22 Tony : Created.                                               *
*============================================================================*/
MusicList* MusicManager::getList()
{
	return curList;
}



/******************************************************************************
 * initAudio -- Initialize the audio.                                         *
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
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
bool initAudio()
{
	FMOD::System_Create(&audioSystem);
	return (audioSystem->init(32, FMOD_INIT_NORMAL, 0) == FMOD_OK);
}

bool closeAudio()
{
	if (audioSystem->close() != FMOD_OK)
		return false;
	if (audioSystem->release() != FMOD_OK)
		return false;

	return true;
}


/******************************************************************************
 * getStream -- Get a stream from the resource.                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   name -- The name of the sound.                                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/22 Tony : Created.                                               *
 *============================================================================*/
Sound getStream(const char* name)
{
	Sound snd;

	audioSystem->createStream(name, FMOD_DEFAULT, 0, &(snd.sound));

	return snd;
}

bool getStream(const char* name, Sound* snd)
{
	return (audioSystem->createStream(name, FMOD_DEFAULT, 0, &(snd->sound)) == FMOD_OK);
}