//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#include "dependencies.h"
#include "Note.h"

namespace DevnetZone
{
    template<>
    inline bool NoteCompare::operator()(Note const& left, Note const& right) const
    {
        return false;
    }

}