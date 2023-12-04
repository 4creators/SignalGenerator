//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#ifndef NOTE_H
#define NOTE_H

#pragma once

#include <string>

#include "types.h"

namespace DevnetZone
{
    class Scale;
    class Note;

    struct NoteCompare
    {
        NoteCompare() = default;

        template<class T>
        bool operator()(T const& lhs, T const& rhs) const 
        {
            return lhs < rhs;
        }

        template<>
        bool operator() < Note > (Note const& left, Note const& right) const;

        template<>
        bool operator() < std::string > (std::string const& left, std::string const& right) const 
        {
            return left < right;
        }
    };

    class Note
    {
    public:

        Note() = default;
        ~Note() = default;



    }; // class Note

} // namespace DevnetZone

#endif // NOTE_H