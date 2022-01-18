//============================================================================
/// \file
/// \ingroup    g_applib
/// \brief      Implementation parts of pure virtual class UI.
/// \details    We need this file with the (default!) virtual destructor so
///             that GCC places the virtual table into this compilation unit.
///             If we'd place the destructor (pseudo-inline) into the header
///             file, we'd get a linker error regarding a missing vtable.
/// \copyright  GNU General Public License (GPL) Version 3
//============================================================================

#include "UI.h"

UI::~UI()
{
    /* empty, but necessary as virtual destructor */
}
