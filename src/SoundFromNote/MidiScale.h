//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#ifndef MIDISCALE_H
#define MIDISCALE_H

#pragma once


#include <string>
#include <map>
#include <boost/unordered_map.hpp>
#include "dependencies.h"
#include "types.h"

namespace DevnetZone
{
    SOUNDFROMNOTE_API class MidiScale
    {
    public:

        MidiScale() : MidiScale((double)Constants::A4TuningFrequency)
        {
        };

        MidiScale(double tuningFrequency) : m_tuningFrequency{tuningFrequency}
        {
            m_midiNoteMap = new std::map<int, std::vector<std::string>>();
            m_midiFrequencyMap = new std::map<int, double>();
            m_noteMidiMap = new boost::unordered_map<std::string, int>();
            GenerateMidiNoteMap();
            GenerateMidiFrequencyMap(); 
            GenerateNoteMidiMap();
        }

        ~MidiScale() 
        { 
            delete m_midiNoteMap;
            delete m_midiFrequencyMap;
            delete m_noteMidiMap;
        };

        SOUNDFROMNOTE_API const std::map<int, std::vector<std::string>>& MidiNoteMap() const
        {
            return const_cast<const std::map<int, std::vector<std::string>>&>(*m_midiNoteMap);
        }

        SOUNDFROMNOTE_API const std::map<int, double>& MidiFrequencyMap() const
        {
            return const_cast<const std::map<int, double>&>(*m_midiFrequencyMap);
        }

        SOUNDFROMNOTE_API const boost::unordered_map<std::string, int>& NoteMidiMap() const
        {
            return const_cast<const boost::unordered_map<std::string, int>&>(*m_noteMidiMap);
        }

    private:
        std::map<int, std::vector<std::string>>* m_midiNoteMap;
        std::map<int, double>* m_midiFrequencyMap;
        boost::unordered_map<std::string, int>* m_noteMidiMap;
        const double m_tuningFrequency;


        void GenerateMidiNoteMap();
        void GenerateMidiFrequencyMap();
        void GenerateNoteMidiMap();
        void AddOctaveNumber(int indexOctave, int& indexBuffer, char  buffer[4]);

    } midiScale;

}

#endif MIDISCALE_H