#pragma once
#include <Windows.h>
#include <cstdint>
uint64_t idx;

namespace syscall {
    auto getIndex(const char* name) -> uint64_t {
        HMODULE hMod = GetModuleHandleA("ntdll.dll");
        if (!hMod) {
            hMod = LoadLibraryA("ntdll.dll");
            if (!hMod)
                return 0;
        }
        auto func_ptr = reinterpret_cast<uintptr_t>(GetProcAddress(hMod, name));
        if (!func_ptr)
            return 0;
        auto ptr = reinterpret_cast<uintptr_t*>(func_ptr + 4);
        return *ptr;
    }

    template< typename ReturnType = void, typename... Args >
    ReturnType __declspec(naked) _syscall(Args... Arguments) {
        __asm {
            mov r10, rcx
            mov eax, idx
            syscall
            ret
        }
    }
    template< typename ReturnType = void, typename... Args >
    ReturnType Call(const char* name, Args... Arguments) {
        idx = getIndex(name);
        return _syscall<ReturnType>(Arguments...);
    }
};