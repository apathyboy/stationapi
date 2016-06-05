
#include "StreamUtils.hpp"

std::string FromWideString(const std::wstring& str) {
    return std::string{std::begin(str), std::end(str)};
}

std::wstring ToWideString(const std::string& str) {
    return std::wstring{std::begin(str), std::end(str)};
}
