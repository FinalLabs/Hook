#include "Hook.h"

unsigned char* Hook::hookStorage;
unsigned long Hook::old;

void Hook::placeJMP(unsigned char* adr, std::uint32_t func, std::size_t size)
{
    VirtualProtect(reinterpret_cast<void*>(adr), size, PAGE_EXECUTE_READWRITE, &old);
    *adr = 0xE9;
    *reinterpret_cast<std::uintptr_t*>((reinterpret_cast<std::uintptr_t>(adr + 1))) = (static_cast<std::uint32_t>(func) - reinterpret_cast<std::uint32_t>(adr)) - size;
    VirtualProtect(reinterpret_cast<void*>(adr), size, old, &old);
}

void Hook::removeJMP(unsigned char* adr, std::uint32_t func, std::size_t size)
{
    VirtualProtect(reinterpret_cast<void*>(adr), size, PAGE_EXECUTE_READWRITE, &old);
    std::memcpy(reinterpret_cast<void*>(adr), hookStorage, size);
    VirtualProtect(reinterpret_cast<void*>(adr), size, old, &old);
}

void Hook::storeBytes(unsigned char* adr, std::size_t size)
{
    unsigned char* storage = new unsigned char[size - 1];
    for (int i = 0; i <= size - 1; i++)
        storage[i] = *reinterpret_cast<unsigned char*>(adr + i);
    hookStorage = storage;
}

void Hook::detourFunction(unsigned char* adr, std::uint32_t func, std::size_t size, Mode mode)
{
    switch (mode)
    {
    case Mode::CREATE_DETOUR:
    {
        Hook::placeJMP(adr, func, size);
        break;
    }
    case Mode::REMOVE_DETOUR:
    {
        Hook::removeJMP(adr, func, size);
        break;
    }
    }
}

/* Adding more soon :-) */
