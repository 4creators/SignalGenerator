//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#include "dependencies.h"
#include "MidiScale.h"

namespace DevnetZone
{
    void MidiScale::GenerateMidiNoteMap()
    {
        if (m_midiNoteMap)
        {
            std::map<int, std::vector<std::string>>& result = *m_midiNoteMap;
            for (int i = 0, octave = -1; i < 128; i++)
            {
                if (i != 0 && i % 12 == 0)
                    octave++;

                result.emplace(i, std::vector<std::string>{ "" });
            }
        }
    }

    void MidiScale::GenerateMidiFrequencyMap()
    {
        if (m_midiFrequencyMap)
        {
            std::map<int, double>& result = *m_midiFrequencyMap;
            for (int i = 0, octave = -1; i < 128; i++)
            {
                if (i != 0 && i % 12 == 0)
                {
                    octave++;
                }

                result.emplace(i, 0.0);
            }
        }
    }

    void MidiScale::GenerateNoteMidiMap()
    {
        if (m_noteMidiMap)
        {
            boost::unordered_map<std::string, int>& result = *m_noteMidiMap;
            for (auto& [key, value] : *m_midiNoteMap)
            {
                for (auto& note : value)
                {
                    result.emplace(note, key);
                }
            }
        }
    }

    void MidiScale::AddOctaveNumber(int indexOctave, int& indexBuffer, char buffer[4])
    {
    }
}