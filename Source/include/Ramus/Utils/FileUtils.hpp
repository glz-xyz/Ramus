#pragma once

#include <filesystem>
#include <string>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <limits.h>
#endif

namespace ramus 
{
    inline std::filesystem::path GetExecutableDirectory() 
    {
        #ifdef _WIN32
            char buffer[MAX_PATH];
            GetModuleFileNameA(NULL, buffer, MAX_PATH);
            return std::filesystem::path(buffer).parent_path();
        #else
            char buffer[PATH_MAX];
            ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);
            if (count != -1) 
            {
                return std::filesystem::path(std::string(buffer, count)).parent_path();
            }
        #endif
        return std::filesystem::current_path(); // Fallback
    }

    inline std::string ExtractFileName(const std::string& filePath) 
    {
        return std::filesystem::path(filePath).filename().string();
    }

    inline std::string ResolvePath(const std::string& filePath) 
    {
        const std::string trigger = "Assets";
        size_t pos = filePath.find(trigger);
        
        if (pos != std::string::npos) 
        {
            return filePath.substr(pos);
        }

        return filePath;
    }
}