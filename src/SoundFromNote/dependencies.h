//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#ifndef SOUNDFROMNOTE_DEPENDENCIES_H
#define SOUNDFROMNOTE_DEPENDENCIES_H

#pragma once

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

// Windows Header Files
#include <windows.h>

#ifdef _WIN32
#ifdef SOUNDFROMNOTE_EXPORTS
#define SOUNDFROMNOTE_API __declspec(dllexport)
#else
#if SOUNDFROMNOTE_IMPORTS
#define SOUNDFROMNOTE_API __declspec(dllimport)
#else /* Unix */
#define SOUNDFROMNOTE_API
#endif
#endif
#endif // _WIN32

#endif // SOUNDFROMNOTE_DEPENDENCIES_H