#include "BitOps.hpp"
#include <bits/stdint-uintn.h>
#include <cstdint>

using namespace std;

Byte::Byte(uint8_t number)
{
    bit0 = number & 1;
    bit1 = (number >> 1) & 1;
    bit2 = (number >> 2) & 1;
    bit3 = (number >> 3) & 1;
    bit4 = (number >> 4) & 1;
    bit5 = (number >> 5) & 1;
    bit6 = (number >> 6) & 1;
    bit7 = (number >> 7) & 1;            
};

string Byte::to_string() const noexcept 
{
    string str = "";
    str.append(std::to_string(bit7));
    str.append(std::to_string(bit6));
    str.append(std::to_string(bit5));
    str.append(std::to_string(bit4)); 
    str.append(std::to_string(bit3));
    str.append(std::to_string(bit2)); 
    str.append(std::to_string(bit1));
    str.append(std::to_string(bit0));
    return str;             
}

uint8_t Byte::restore() const noexcept
{
    uint8_t result = bit0;
    result |= bit1 << 1;
    result |= bit2 << 2;
    result |= bit3 << 3;
    result |= bit4 << 4;
    result |= bit5 << 5;
    result |= bit6 << 6;
    result |= bit7 << 7;
    return result;
}

uint8_t Byte::bits_size() const noexcept 
{
    return 8;
}

void Byte::flip(const ByteIndex index)
{
    switch (index.value) {
        case 0:
            bit0 = ~bit0;
            break;
        case 1:
            bit1 = ~bit1;
            break;
        case 2:
            bit2 = ~bit2;
            break;
        case 3: 
            bit3 = ~bit3;
            break;
        case 4:
            bit4 = ~bit4;
            break;
        case 5:
            bit5 = ~bit5;
            break;
        case 6:
            bit6 = ~bit6;
            break;
        case 7:
            bit7 = ~bit7;
            break;
    }
}

bool Byte::operator[](const ByteIndex index) const noexcept
{
    switch (index.value) {
        case 0:
          return bit0;
        case 1:
          return bit1;
        case 2:
          return bit2;
        case 3: 
          return bit3;
        case 4:
          return bit4;
        case 5:
          return bit5;
        case 6:
          return bit6;
    }    
    return bit7;
}

Word::Word(uint16_t number): byte0((uint8_t) number), byte1((uint8_t) (number>>8))
{}

string Word::to_string() const noexcept
{
    string str = "";
    str.append(byte1.to_string());
    str.append(byte0.to_string());
    return str;
}

uint16_t Word::restore() const noexcept
{
    uint16_t byte0 = this->byte0.restore();
    uint16_t byte1 = this->byte1.restore();
    return ( byte1 << 8 ) | byte0;   
}

uint8_t Word::bits_size() const noexcept 
{
    return 16;
}

void Word::flip(const WordIndex index)
{
    if (index.value < 8) 
    {
        byte0.flip(ByteIndex{.value = index.value});
    }
    else
    {
        byte1.flip(ByteIndex{.value = static_cast<uint8_t>(index.value - 8)});
    }
}

bool Word::operator[](const WordIndex index) const noexcept 
{
    if (index.value < 8)
    {        
        return byte0[{.value = static_cast<uint8_t>(index.value)}];
    }
    return byte1[{.value = static_cast<uint8_t>(index.value - 8)}];    
}

Dword::Dword(uint32_t number): word0((uint16_t) number), word1((uint16_t) (number >> 16))
{}

string Dword::to_string() const noexcept
{
    string str = "";
    str.append(word1.to_string());
    str.append(word0.to_string());    
    return str;
}

uint32_t Dword::restore() const noexcept
{
    uint32_t word0 = this->word0.restore();
    uint32_t word1 = this->word1.restore();
    return ( word1 << 16 ) | word0;   
}

uint8_t Dword::bits_size() const noexcept 
{
    return 32;
}

void Dword::flip(const DwordIndex index)
{
    if (index.value < 16)
    {
        word0.flip(WordIndex{.value = index.value});
    } 
    else 
    {
        word1.flip(WordIndex{.value = static_cast<uint8_t>(index.value - 16)});
    }   
}

bool Dword::operator[](const DwordIndex index) const noexcept
{
    if (index.value < 16)
    {
        return word0[{.value = static_cast<uint8_t>(index.value)}];
    }
    return word1[{.value = static_cast<uint8_t>(index.value - 16)}];
}

Qword::Qword(uint64_t number): dword0((uint32_t) number), dword1((uint32_t) (number >> 32))
{}

string Qword::to_string() const noexcept
{
    string str = "";
    str.append(dword1.to_string());
    str.append(dword0.to_string());    
    return str;
}

uint64_t Qword::restore() const noexcept
{
    uint64_t word0 = this->dword0.restore();
    uint64_t word1 = this->dword1.restore();
    return ( word1 << 32 ) | word0;   
}

uint8_t Qword::bits_size() const noexcept 
{
    return 64;
}

void Qword::flip(const QwordIndex index)
{
    if (index.value < 32)
    {
        dword0.flip(DwordIndex{.value = index.value});
    } 
    else 
    {
        dword1.flip(DwordIndex{.value = static_cast<uint8_t>(index.value - 32)});
    }   
}

bool Qword::operator[](const QwordIndex index) const noexcept
{
    if (index.value < 32)
    {
        return dword0[{.value = static_cast<uint8_t>(index.value)}];
    }
    return dword1[{.value = static_cast<uint8_t>(index.value - 32)}];
}



