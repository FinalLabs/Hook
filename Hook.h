#include <cstdint>
#include <memoryapi.h>
#include <Windows.h>
#include <iostream>
#include <cstring>
#include <cstddef>

class hook
{
private:
    static BYTE* hook_storage;
    static DWORD old;
public:
    template<typename T1>
    static std::uintptr_t aslr(const T1 address)
    {
        return (address - 0x400000 + reinterpret_cast<std::uintptr_t>(GetModuleHandleA(0)));
    }
private:
    static int add_jmp(BYTE* adr, const std::uint32_t func, std::size_t size)
    {
        if (size < 5)
            return 0;

        VirtualProtect(reinterpret_cast<void*>(adr), size, PAGE_EXECUTE_READWRITE, &old);
        std::uint32_t rel = (static_cast<std::uint32_t>(func) - reinterpret_cast<std::uint32_t>(adr)) - 5;

        *adr = 0xE9;

        *reinterpret_cast<std::uintptr_t*>((reinterpret_cast<std::uintptr_t>(adr + 1))) = rel;
        VirtualProtect(reinterpret_cast<void*>(adr), size, old, &old);

        return 1;
    }

    static int remove_jmp(BYTE* adr, const std::uint32_t func, std::size_t size)
    {
        if (size < 5)
            return 0;

        VirtualProtect(reinterpret_cast<void*>(adr), size, PAGE_EXECUTE_READWRITE, &old);
        std::memcpy(reinterpret_cast<void*>(adr), hook_storage, 5);
        VirtualProtect(reinterpret_cast<void*>(adr), size, old, &old);

        return 1;
    }
public:
    enum class mode : std::uint32_t
    {
        create = 1,
        remove = 0
    };
public:
    static void store_bytes(BYTE* adr, int size)
    {
        int sz = size - 1;
        BYTE* storage = new BYTE[sz];
        for (int i = 0; i <= sz; i++)
        {
            storage[i] = *reinterpret_cast<BYTE*>(adr + i);
            //printf("%x ", storage[i]);
        }

        hook_storage = storage;
    }

    static void detour_function(BYTE* adr, const std::uint32_t func, std::size_t size, hook::mode m)
    {
        switch (m)
        {
        case hook::mode::create:
        {
            hook::add_jmp(adr, func, size);
            break;
        }
        case hook::mode::remove:
        {
            hook::remove_jmp(adr, func, size);
            break;
        }
        }
    }
};

BYTE* hook::hook_storage;
DWORD hook::old;
