# About
Simple x86 hooking library (not finished)
# Usage
To store bytes of a function is simple
```cpp
int main()
{
    std::uintptr_t memoryAddress = Hook::utils::aslr(0xDEADBEEF);
    std::size_t memoryAddressSize = 5;

    Hook::storeBytes(reinterpret_cast<BYTE*>(memoryAddress), memoryAddressSize);
    
    return false;
}
```
