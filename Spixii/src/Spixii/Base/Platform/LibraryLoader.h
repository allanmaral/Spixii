#pragma once

#include "Spixii/Core.h"
#include "spxpch.h"

namespace Spixii
{
    typedef int64(__cdecl *Procedure)();

    class LibraryLoader
    {
    public:
        static void *    LoadSharedLibrary(const wchar_t* libraryName);
        static void      ReleaseLibrary(void *library);
        static Procedure GetProcedure(void *library, const char *procedureName);
    };

}  // namespace Spixii