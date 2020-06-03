#pragma once

#ifndef NDEBUG

	#define REFUREKU_DEBUG		1
	#define REFUREKU_RELEASE	0

#else	//RELEASE

	#define REFUREKU_DEBUG		0
	#define REFUREKU_RELEASE	1

#endif

#define REFUREKU_VERSION_MAJOR 1
#define REFUREKU_VERSION_MINOR 1
#define REFUREKU_VERSION_PATCH 1