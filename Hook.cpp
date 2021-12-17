#include "Hook.h"

BYTE* hook::hook_storage;
DWORD hook::old;

int hook::add_jmp(BYTE* adr, const std::uint32_t func, std::size_t size)
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

int hook::remove_jmp(BYTE* adr, const std::uint32_t func, std::size_t size)
{
    if (size < 5)
        return 0;

    VirtualProtect(reinterpret_cast<void*>(adr), size, PAGE_EXECUTE_READWRITE, &old);
    std::memcpy(reinterpret_cast<void*>(adr), hook_storage, 5);
    VirtualProtect(reinterpret_cast<void*>(adr), size, old, &old);

    return 1;
}

void hook::store_bytes(BYTE* adr, int size)
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

void hook::detour_function(BYTE* adr, const std::uint32_t func, std::size_t size, bool mode) 
{
    switch (mode)
    {
    case 1:
    {
        hook::add_jmp(adr, func, size);
        break;
    }
    case 0:
    {
        hook::remove_jmp(adr, func, size);
        break;
    }
    }
}
