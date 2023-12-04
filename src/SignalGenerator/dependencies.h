//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#ifndef SIGNALGENERATOR_DEPENDENCIES_H
#define SIGNALGENERATOR_DEPENDENCIES_H

#pragma once

#include <SDKDDKVer.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#ifdef _WIN32
#ifdef SIGNALGENERATOR_EXPORTS
#define SIGNALGENERATOR_API __declspec(dllexport)
#else
#if SIGNALGENERATOR_IMPORTS
#define SIGNALGENERATOR_API __declspec(dllimport)
#else /* Unix */
#define SIGNALGENERATOR_API
#endif
#endif
#endif // _WIN32

#endif // SIGNALGENERATOR_DEPENDENCIES_H