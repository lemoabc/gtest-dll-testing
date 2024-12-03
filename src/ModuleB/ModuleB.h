#pragma once

#ifdef MODULEB_EXPORTS
#define MODULEB_API __declspec(dllexport)
#else
#define MODULEB_API __declspec(dllimport)
#endif

#include <string>
#include <vector>

namespace ModuleB {
    class MODULEB_API StringUtil {
    public:
        bool IsEmpty(const char* str);
        bool IsEmpty(const std::string& str);
        
        size_t Length(const char* str);
        size_t Length(const std::string& str);
        
        std::string ToUpper(const std::string& str);
        std::string ToLower(const std::string& str);
        
        bool StartsWith(const std::string& str, const std::string& prefix);
        bool EndsWith(const std::string& str, const std::string& suffix);
        
        std::string Trim(const std::string& str);
        std::string TrimLeft(const std::string& str);
        std::string TrimRight(const std::string& str);
        
        std::vector<std::string> Split(const std::string& str, char delimiter);
        std::string Join(const std::vector<std::string>& parts, const std::string& delimiter);
    };
}
