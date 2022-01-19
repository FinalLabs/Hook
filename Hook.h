#include <Windows.h>
#include <iostream>

class Hook
{
private:
    static unsigned char* hookStorage;
    static unsigned long old;
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
    static void placeJMP(BYTE* adr, std::uint32_t func, std::size_t size);
    static void removeJMP(BYTE* adr, std::uint32_t func, std::size_t size);
public:
    static void storeBytes(BYTE* adr, std::size_t size);
    static void detourFunction(BYTE* adr, std::uint32_t func, std::size_t size, bool mode);
};
