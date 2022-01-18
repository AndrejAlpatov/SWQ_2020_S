//============================================================================
/// \file
/// \ingroup    g_applib
/// \brief      The interface definition of class Todomat.
/// \copyright  GNU General Public License (GPL) Version 3
//============================================================================
#if !defined(TODOMAT_H)
#define TODOMAT_H

#include "UI.h"

/// Todomat is the "controller" of the todo list.
/// If you compare our classes with the Model-View-Controller pattern, Todomat
/// has the controller role, but also parts of the model, as it holds all todos
/// in a simple list, and the User Interface ("View") talks to Todomat to get
/// updated todo list entries, while in the MVI pattern, the View is informed
/// directly by the Model to update.
class Todomat {
    public:
        Todomat(UI & ui);
        void run();             ///< start reading and executing commands

    private:
        UI & ui;
};

#endif
