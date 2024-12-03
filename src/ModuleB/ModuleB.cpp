#include "ModuleB.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>

namespace ModuleB {
    bool StringUtil::IsEmpty(const char* str) {
        return str == nullptr || str[0] == '\0';
    }

    bool StringUtil::IsEmpty(const std::string& str) {
        return str.empty();
    }

    size_t StringUtil::Length(const char* str) {
        if (str == nullptr) return 0;
        return strlen(str);
    }

    size_t StringUtil::Length(const std::string& str) {
        return str.length();
    }

    std::string StringUtil::ToUpper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    std::string StringUtil::ToLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    bool StringUtil::StartsWith(const std::string& str, const std::string& prefix) {
        if (prefix.length() > str.length()) return false;
        return str.compare(0, prefix.length(), prefix) == 0;
    }

    bool StringUtil::EndsWith(const std::string& str, const std::string& suffix) {
        if (suffix.length() > str.length()) return false;
        return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
    }

    std::string StringUtil::Trim(const std::string& str) {
        return TrimRight(TrimLeft(str));
    }

    std::string StringUtil::TrimLeft(const std::string& str) {
        auto it = std::find_if(str.begin(), str.end(), [](char ch) {
            return !std::isspace(static_cast<unsigned char>(ch));
        });
        return std::string(it, str.end());
    }

    std::string StringUtil::TrimRight(const std::string& str) {
        auto it = std::find_if(str.rbegin(), str.rend(), [](char ch) {
            return !std::isspace(static_cast<unsigned char>(ch));
        }).base();
        return std::string(str.begin(), it);
    }

    std::vector<std::string> StringUtil::Split(const std::string& str, char delimiter) {
        std::vector<std::string> result;
        std::stringstream ss(str);
        std::string item;
        while (std::getline(ss, item, delimiter)) {
            if (!item.empty()) {
                result.push_back(item);
            }
        }
        return result;
    }

    std::string StringUtil::Join(const std::vector<std::string>& parts, const std::string& delimiter) {
        if (parts.empty()) return "";
        
        std::string result = parts[0];
        for (size_t i = 1; i < parts.size(); ++i) {
            result += delimiter + parts[i];
        }
        return result;
    }
}
