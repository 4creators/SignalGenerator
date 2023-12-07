//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#ifndef SIGNALANALYZER_DEPENDENCIES_H
#define SIGNALANALYZER_DEPENDENCIES_H

#pragma once

#include <SDKDDKVer.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#ifdef _WIN32
#ifdef SIGNALANALYZER_EXPORTS
#define SIGNALANALYZER_API __declspec(dllexport)
#else
#if SIGNALANALYZER_IMPORTS
#define SIGNALANALYZER_API __declspec(dllimport)
#else /* Unix */
#define SIGNALANALYZER_API
#endif
#endif
#endif // _WIN32


#endif // SIGNALANALYZER_DEPENDENCIES_H
