// ============================================================================
// ==         Copyright (c) 2016, Samsonov Andrey and Smirnov Denis          ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef WorldWorker_h_
#define WorldWorker_h_
#include <boost\noncopyable.hpp>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <glm/glm.hpp>
#include "tools\CoordSystem.h"
#include <mutex>

class Sector;

class WorldWorker : public boost::noncopyable
{
public:
	WorldWorker();

	static WorldWorker &instance()
	{
    static auto lw = std::make_unique<WorldWorker>();
		return *lw;
	}

	std::shared_ptr<Sector> GetSector(const SPos &v);
	void Process();

private:
  std::shared_ptr<Sector> Generate(const SPos &spos);
  SPos mLast; //replace with queue
  
  std::mutex mQueueMutex;
	std::unordered_map<SPos, std::shared_ptr<Sector>> mReady;
	std::unordered_set<SPos> mRequested;
};
#endif //WorldWorker_h_
