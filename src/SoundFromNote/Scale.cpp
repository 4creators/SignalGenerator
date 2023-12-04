//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#include "dependencies.h"
#include "Scale.h"

namespace DevnetZone
{
    template<>
    inline bool NoteNameCompare::operator()(std::string const& left, std::string const& right) const
    {
        int32_t leftScore = 0;
        int32_t leftOctave = 0;

        NoteNameScore(left, leftScore, leftOctave);

        int32_t rightScore = 0;
        int32_t rightOctave = 0;

        NoteNameScore(right, rightScore, rightOctave);

    modular_compare:

        if (leftOctave == rightOctave)
        {
            if (leftScore < rightScore)
                return true;
            else return false;
        }

        if (leftOctave < rightOctave)
        {
            if (leftScore >= 24)
            {
                leftOctave++;
                leftScore %= 24;
                goto modular_compare;
            }
            else return true;
        }

        if (leftOctave > rightOctave)
        {
            if (rightScore >= 24)
            {
                rightOctave++;
                rightScore %= 24;
                goto modular_compare;
            }
            else return false;
        }
    }

    void NoteNameCompare::NoteNameScore(const std::string& noteName, int32_t& scaleScore, int32_t& octave) const
    {
        switch (noteName[0])
        {
        case 'C':
            scaleScore += 0;
            break;
        case 'D':
            scaleScore += 4;
            break;
        case 'E':
            scaleScore += 8;
            break;
        case 'F':
            scaleScore += 10;
            break;
        case 'G':
            scaleScore += 14;
            break;
        case 'A':
            scaleScore += 18;
            break;
        case 'B':
            scaleScore += 22;
            break;
        }

        if (noteName.ends_with('#'))
            scaleScore+=2;
        else if (noteName.ends_with('b'))
            scaleScore--;

        std::string octaveStr;
        for (int i = 1; ; i++)
        {
            if (isdigit(noteName[i]) || noteName[i] == '-')
                octaveStr.append(1, noteName[i]);
            else break;
        }

        octave = std::stoi(octaveStr);
    }


    void Scale::GenerateNoteFreaquencyMap()
    {

        if (m_noteFrequencyMap != nullptr)
        {
            map<std::string, double, NoteNameCompare>& result = *m_noteFrequencyMap;

            // Set capacity to be at least sufficient for 19 octaves
            // encompassing all 17 notes including dual named basic enharmonics
            //result.reserve(((uint64_t) - m_lowestOctave + m_highestOctave + 1) * 17);

            // TODO Implement enharmonics with all possible note/accidental 
            // combinations including double sharp and double flat accidentals

            // TODO Investigate Microtonal Tuning Scale implementation -> derive from Scale?

            // First octave here starts at C-7 ~ 0.1277 Hz and proceeds 1st MIDI 
            // octave which starts at C-1 ~ 8.17 Hz with C0 being at ~ 16.35 Hz
            // Last octave ends at B12 ~ 126434.1 Hz and requires double Nyquist
            // sampling frequncy to be usable during digital processing

            // Basic tuning frequency is always set for A4 - correct octave span
            float128 aFreq = m_tuningFrequency / pow(float128{ 2.0 }, (-m_lowestOctave + 5));
            float128 cFreq = aFreq * (pow(Constants::HalfToneRatio, 3));

            for (int indexOctave = m_lowestOctave; indexOctave <= m_highestOctave; indexOctave++)
            {
                for (int indexNote = 0; indexNote < 12; indexNote++)
                {
                    std::vector<std::string> notePosition = noteNames[indexNote];
                    std::string noteNameProtX = notePosition[0];

                    std::string noteNameX;
                    noteNameX.append(&noteNameProtX[0], 1);

                    AddOctaveNumber(indexOctave, noteNameX);

                    if (indexNote > 0)
                        cFreq *= Constants::HalfToneRatio;

                    if (notePosition.size() == 2)
                    {
                        noteNameX.append(&noteNameProtX[1], 1);

                        // Create enharmonic
                        std::string noteNameProtY = notePosition[1];
                        std::string noteNameY;
                        noteNameY.append(&noteNameProtY[0], 1);

                        AddOctaveNumber(indexOctave, noteNameY); 

                        noteNameY.append(&noteNameProtY[1], 1);
                        result.emplace(noteNameY, cFreq.convert_to<double>());
                    }

                    result.emplace(noteNameX, cFreq.convert_to<double>());

                } // for (int indexNote = 0; indexNote < 12; indexNote++)

                aFreq *= 2;
                cFreq = aFreq * (pow(Constants::HalfToneRatio, 3));

            } // for (int indexOctave = 0; indexOctave < 12; indexOctave++)
        }
    }


    void Scale::AddOctaveNumber(int indexOctave, std::string& noteName)
    {
        std::string octaveString = std::to_string(indexOctave);
        noteName.append(octaveString, 0, octaveString.length());
    }
}