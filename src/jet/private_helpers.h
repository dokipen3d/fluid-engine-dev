// Copyright (c) 2016 Doyub Kim

#ifndef SRC_JET_PRIVATE_HELPERS_H_
#define SRC_JET_PRIVATE_HELPERS_H_

#include <jet/macros.h>

#ifndef UNUSED_VARIABLE
#   define UNUSED_VARIABLE(x) ((void)x)
#endif

#ifdef JET_WINDOWS

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
#define NOMINMAX
#include <Windows.h>
#include <exception>
#include <string>

inline void throwIfFailed(HRESULT hr) {
    if (FAILED(hr)) {
        throw std::exception(std::to_string(hr).c_str());
    }
}

#ifndef IF_FAILED_CLEANUP
#   define IF_FAILED_CLEANUP(_hr) if (FAILED(_hr)) { hr = _hr; goto Cleanup; }
#endif

#ifndef FAIL_AND_CLEANUP
#   define FAIL_AND_CLEANUP(_hr) { hr = _hr; goto Cleanup; }
#endif

#endif  // JET_WINDOWS

#endif  // SRC_JET_PRIVATE_HELPERS_H_