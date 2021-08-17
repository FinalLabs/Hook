# FHook
Simple x86 hooking library (not finished)
# Usage
```cpp
std::uint32_t Detour()
{
    return 1;
}

int main()
{
    std::uintptr_t address = hook::aslr(0x6342B0);
    hook::store_bytes(reinterpret_cast<BYTE*>(address), 5); //store the bytes so you can restore original bytes correctly if you please

    hook::detour_function(reinterpret_cast<BYTE*>(address), reinterpret_cast<std::uint32_t>(Detour), 5, hook::mode::create);
    Sleep(3);
    hook::detour_function(reinterpret_cast<BYTE*>(address), reinterpret_cast<std::uint32_t>(Detour), 5, hook::mode::remove);
}
```
