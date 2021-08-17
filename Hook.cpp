#include "Hook.h"

void hook::store_bytes(BYTE* adr, int size)
{
    int sz = size - 1;
    BYTE* storage = new BYTE[sz];
    for (int i = 0; i <= sz; i++)
    {
        storage[i] = *reinterpret_cast<BYTE*>(adr + i);
    }

    hook_storage = storage;
}

void hook::detour_function(BYTE* adr, const std::uint32_t func, std::size_t size, hook::mode m)
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

BYTE* hook::hook_storage;
DWORD hook::old;
