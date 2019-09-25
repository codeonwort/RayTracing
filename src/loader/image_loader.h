#pragma once

#include "../image.h"
#include "../template/noncopyable.h"

#include "FreeImage.h"

class ImageLoader : public Noncopyable
{

public:
	static void Initialize();
	static void Destroy();

	// Simple load. Create an ImageLoader instance for advanced functionality.
	static bool SyncLoad(const char* filepath, Image2D& outImage);

public:
	explicit ImageLoader();
	~ImageLoader();

	bool LoadSynchronous(const char* filepath, Image2D& outImage);

	/*
	 * #todo: async load
	 * ThreadHandle LoadAsync(std::vector<const char*> filepathArray);
	 * AsyncLoadProgress GetProgress();
	 */
	
};
