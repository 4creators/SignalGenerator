//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#ifndef SCALE_H
#define SCALE_H

#pragma once

#include <string>
#include <vector>
#include <boost/unordered_map.hpp>
#include <boost/container/map.hpp>
#include "dependencies.h"
#include "types.h"

using namespace boost::container;

namespace DevnetZone
{

    struct NoteNameCompare 
    {
        NoteNameCompare() = default;

        template<class T>
        bool operator()(T const& lhs, T const& rhs) const {
            return lhs < rhs;
        }

        template<>
        bool operator() < std::string > (std::string const& left, std::string const& right) const;

    private:
        void NoteNameScore(const std::string& left, int32_t& leftScore, int32_t& octave) const;
    };

    class Scale
    {
    public:

        SOUNDFROMNOTE_API Scale() : 
            Scale((double)Constants::A4TuningFrequency)
        {
        }

        SOUNDFROMNOTE_API Scale(double tuningFrequency, int lowestOctave = -7, int highestOctave = 12) : 
            m_tuningFrequency{tuningFrequency},
            m_lowestOctave{lowestOctave},
            m_highestOctave{highestOctave}           
        {
            m_noteFrequencyMap = new map<std::string, double, NoteNameCompare>{ NoteNameCompare{} };

            GenerateNoteFreaquencyMap();
        }

        SOUNDFROMNOTE_API ~Scale() { delete m_noteFrequencyMap; };

        SOUNDFROMNOTE_API const map<std::string, double, NoteNameCompare>& NoteFrequencyMap()
        {
            return *m_noteFrequencyMap;
        }

        SOUNDFROMNOTE_API bool NoteIsHigher(std::string left, std::string right)
        {
            return std::isgreater(m_noteFrequencyMap->at(left), m_noteFrequencyMap->at(right));
        }

    private:
        map<std::string, double, NoteNameCompare>* m_noteFrequencyMap;
        double m_tuningFrequency;
        int m_lowestOctave;
        int m_highestOctave;

        // Full octave with basic enharmonics
        std::vector<std::vector<std::string>> noteNames =
        {
            {"C"},
            {"C#", "Db"},
            {"D"},
            {"D#", "Eb"},
            {"E"},
            {"F"},
            {"F#", "Gb"},
            {"G"},
            {"G#", "Ab"},
            {"A"},
            {"A#", "Bb"},
            {"B"},
        };

        void GenerateNoteFreaquencyMap();
        void AddOctaveNumber(int indexOctave, std::string& noteName);
    };

}

#endif // SCALE_H