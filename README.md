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
# License
MIT License

Copyright (c) 2021 FinalLabs

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
