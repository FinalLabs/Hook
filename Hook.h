#include <Windows.h>
#include <iostream>

class hook
{
private:
    static BYTE* hook_storage;
    static DWORD old;
public:
    class utils
    {
    public:
        template<typename T1>
       static const std::uintptr_t aslr(const T1 address)
        {
            return (address - 0x400000 + reinterpret_cast<std::uintptr_t>(GetModuleHandleA(0)));
        }
    };
private:
    static int add_jmp(BYTE* adr, const std::uint32_t func, std::size_t size);
    static int remove_jmp(BYTE* adr, const std::uint32_t func, std::size_t size);
public:
    enum class mode : std::uint32_t
    {
        create = 1,
        remove = 0
    };
public:
    static void store_bytes(BYTE* adr, int size);
    static void detour_function(BYTE* adr, const std::uint32_t func, std::size_t size, hook::mode m);
};
