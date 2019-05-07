#include "spxpch.h"

#ifdef SPX_PLATFORM_WINDOWS
#include "Spixii/Base/Platform/LibraryLoader.h"
#include "Spixii/Log.h"

namespace Spixii
{
    void *LibraryLoader::LoadSharedLibrary(const wchar_t* libraryName)
    {
        HINSTANCE library = LoadLibrary(libraryName);
        SPX_ASSERT_CORE(library, "Could not load shared library");
        return (void *) library;
    }

    void LibraryLoader::ReleaseLibrary(void *library)
    {
        FreeLibrary((HMODULE) library);
    }

    Procedure LibraryLoader::GetProcedure(void *library, const char *procedureName)
    {
        Procedure proc = (Procedure) GetProcAddress((HMODULE)library, procedureName);
        SPX_ASSERT_CORE(proc, "Could not load precedure from static library");
        return proc;
    }
}  // namespace Spixii

#endif  // SPX_PLATFORM_WINDOWS