# About
Simple x86 hooking library (not finished)
# Documentation
## Usage
Storing bytes of a function
```cpp
Hook::storeBytes(address, size);
```
## How to use
```cpp
int main()
{
    std::uintptr_t memoryAddress = Hook::utils::aslr(0xDEADBEEF);
    std::size_t memoryAddressSize = 5;

    Hook::storeBytes(reinterpret_cast<BYTE*>(memoryAddress), memoryAddressSize);
    
    return 0;
}
```
## Usage
To detour a function is simple, but to restore the jmp you have to store bytes first as addressed above
```cpp
Hook::detourFunction(address, detour_function, size, mode);
```
## How to use
```cpp
int myDetour()
{
    std::printf("Detour :)\n");
    
    return 0;
}

int main()
{
    std::uintptr_t memoryAddress = Hook::utils::aslr(0xDEADBEEF);
    std::size_t memoryAddressSize = 5;

    Hook::storeBytes(reinterpret_cast<BYTE*>(memoryAddress), memoryAddressSize);
    
    /* To create a detour */
    Hook::detourFunction(reinterpret_cast<BYTE*>(memoryAddress), reinterpret_cast<std::uint32_t>(myDetour), memoryAddressSize, true); 
    
    /* Remove the detour (just change true to false at the end) */
    Hook::detourFunction(reinterpret_cast<BYTE*>(memoryAddress), reinterpret_cast<std::uint32_t>(myDetour), memoryAddressSize, false); 
    
    return 0;
}
```
