#include "Hook.h"

BYTE* Hook::hookStorage;
DWORD Hook::old;

void Hook::placeJMP(BYTE* adr, std::uint32_t func, std::size_t size)
{
    VirtualProtect(reinterpret_cast<void*>(adr), size, PAGE_EXECUTE_READWRITE, &old);
    *adr = 0xE9;
    *reinterpret_cast<std::uintptr_t*>((reinterpret_cast<std::uintptr_t>(adr + 1))) = (static_cast<std::uint32_t>(func) - reinterpret_cast<std::uint32_t>(adr)) - 5;
    VirtualProtect(reinterpret_cast<void*>(adr), size, old, &old);
}

void Hook::removeJMP(BYTE* adr, std::uint32_t func, std::size_t size)
{
    VirtualProtect(reinterpret_cast<void*>(adr), size, PAGE_EXECUTE_READWRITE, &old);
    std::memcpy(reinterpret_cast<void*>(adr), hookStorage, 5);
    VirtualProtect(reinterpret_cast<void*>(adr), size, old, &old);
}

void Hook::storeBytes(BYTE* adr, std::size_t size)
{
    BYTE* storage = new BYTE[size - 1];
    for (int i = 0; i <= size - 1; i++)
        storage[i] = *reinterpret_cast<BYTE*>(adr + i);
    hookStorage = storage;
}

void Hook::detourFunction(BYTE* adr, std::uint32_t func, std::size_t size, bool mode)
{
    switch (mode)
    {
    case true:
    {
        Hook::placeJMP(adr, func, size);
        break;
    }
    case false:
    {
        Hook::removeJMP(adr, func, size);
        break;
    }
    }
}

/* Adding more soon :-) */
