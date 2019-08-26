// Program to demonstrate the use of a plugin system.

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <exception>
#include <windows.h>
#include "plugin_export_interface.h"
#include "object_model.h"

std::vector<std::unique_ptr<InterfaceExport>> getPlugins(std::vector<HINSTANCE>& modules)
{
    std::vector<std::unique_ptr<InterfaceExport>> ret;

    // Find the files contained in the 'plugins' folder
    WIN32_FIND_DATA fileData;
    HANDLE fileHandle = FindFirstFile("../Debug/plugins/*.dll", &fileData);

    if (fileHandle == INVALID_HANDLE_VALUE)
	{
        // If we couldn't find any plugins, quit gracefully,
        // returning an empty structure.
        return std::vector<std::unique_ptr<InterfaceExport>>();
    }

    do
	{
        typedef InterfaceExport*(__cdecl *iExport)(void);
        HINSTANCE mod = LoadLibrary(("../Debug/plugins/" + std::string(fileData.cFileName)).c_str());

        if (!mod)
		{
            // Couldn't load the library, cleaning module list and quitting.
			for (HINSTANCE hInst : modules)
			{
				FreeLibrary(hInst);
			}
            throw std::runtime_error("Library " + std::string(fileData.cFileName) + " wasn't loaded successfully!");
        }

		iExport exportFunc = reinterpret_cast<iExport> (GetProcAddress(mod, "getInterface"));

		if (!exportFunc)
		{
			std::cerr << GetLastError() << '\n';
			throw std::runtime_error("Invalid Plugin DLL: 'getInterface' must be defined.");
		}

        ret.push_back(std::unique_ptr<InterfaceExport>(exportFunc()));
        modules.push_back(mod);
    }
	while (FindNextFile(fileHandle, &fileData));

    FindClose(fileHandle);

    return ret;
}

int main()
{
    std::vector<HINSTANCE> modules;

    // Enter a block, to prevent the Base objects being
    // deallocated after the modules are freed (which will
    // cause program to crash)
    {
        std::vector<std::unique_ptr<InterfaceExport>> objs;
		std::unique_ptr<ObjectModel> pObjectModel;

        try
		{
            objs = getPlugins(modules);
        }
		catch (const std::exception& e)
		{
            std::cerr << "Exception caught: " << e.what() << std::endl;
            return 1;
        }

        for (auto &iExporter: objs)
		{
			pObjectModel = std::make_unique<ObjectModel>(iExporter->getObject());
            std::cout << pObjectModel->getHumanReadableName() << ' ' << pObjectModel->getId() << '\n';
			std::cout << pObjectModel->calculate(1, 2, 3);
        }
    }

    // Program finishing, time to clean up
	for (HINSTANCE hInst : modules)
	{
		FreeLibrary(hInst);
	}

    return 0;
}
