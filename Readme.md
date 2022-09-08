# Summary

- [Introduction](#Introduction)
- [Indexes classes](#Indexes-classes)
- [Conversions](#Conversions)
    + [Decimal to bits](#Decimal-to-bits)
    + [Bits to decimal](#Bits-to-decimal)
- [Endians](#Endians)

# Introduction

This project is just for educational purposes. I like computer architeture and C++, so, with this project I have found something nice to play with .

# Indexes classes

I created this classes to be used as an index to access individual bits of the structures ...   
With this, I do not need to check for index out of bounds, since the compiler does this for me.

So, for example:  
```c++
struct ByteIndex 
{
    // The range is: 0-7
    const std::uint8_t value:3;
};

struct WordIndex
{
    // The range is: 0-15
    const std::uint8_t value:4;
};

struct DwordIndex
{
    // The range is 0-31
    const std::uint8_t value:5;
};

struct QwordIndex
{
    // The range is 0-63
    const std::uint8_t value:6;
};
```

If I overflow, the compiler will throw an warning:  
Example: 
```c++
void test(ByteIndex index) 
{
    ...
}

test({.value = 7}); // ok
test({.value = 8}); // nok. If it runs, will overlflow back to 0! Note that the compiler will warn you about it.
```

With this strategy, there are no check for bounds cost!

# Conversions

The conversions are done in a naive & simple way!

- ## Decimal to bits

    By default, we receive the decimal value in the class constructor. 

    + ### The Byte class

        In the **Byte** class, we have the following source code:  

        **Obs:** Note that: `number & 1` is the same as `number & 000000001`
        ```c++
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
        ```
        So, for example, the number: 2(00000010 in binary), will be set as:  
        | Field | Shift By | After shift | &(AND bitwise operator) 1 | 
        | :-:   | :-:      | :-:         | :-: |
        | bit0  | 0        | 00000010    | 0 & 1 = 0 |
        | bit1  | 1        | 00000001    | 1 & 1 = 1 |
        | bit2  | 2        | 00000000    | 0 & 1 = 0 |
        | bit3  | 3        | 00000000    | 0 & 1 = 0 |
        | bit4  | 4        | 00000000    | 0 & 1 = 0 |
        | bit5  | 5        | 00000000    | 0 & 1 = 0 |
        | bit6  | 6        | 00000000    | 0 & 1 = 0 |
        | bit7  | 7        | 00000000    | 0 & 1 = 0 |

        The number 15(00001111), will become:    
        | Field | Shift By | After shift | &(AND bitwise operator) 1 | 
        | :-:   | :-:      | :-:         | :-: |
        | bit0  | 0        | 00001111    | 1 & 1 = 1 |
        | bit1  | 1        | 00000111    | 1 & 1 = 1 |
        | bit2  | 2        | 00000011    | 1 & 1 = 1 |
        | bit3  | 3        | 00000001    | 1 & 1 = 1 |
        | bit4  | 4        | 00000000    | 0 & 1 = 0 |
        | bit5  | 5        | 00000000    | 0 & 1 = 0 |
        | bit6  | 6        | 00000000    | 0 & 1 = 0 |
        | bit7  | 7        | 00000000    | 0 & 1 = 0 |    

    + ### The Word class

        In the word class, we have the following:
        ```c++
        Word::Word(uint16_t number): byte0((uint8_t) number), byte1((uint8_t) (number>>8))
        {}
        ```
        This class is backed by two instances of the **Byte** class.
        The byte0 represents the lsb(*least significant part*) part of the word. And, the byte1 represents the msg(*most significant part*) part of the word.   
        Note that we do:  
        ```c++
        byte0((uint8_t) number), byte1((uint8_t) (number>>8))   
        ```
        Since, we receive a value of 2 bytes(uint16) for byte0, we just cast to uint8(this will drop the msb part and not overflow the value), and for byte1, we shift/drop the lsb part. 

        Example: The number 300(0000000100101100 in binary)
        | Field | Shift | After Shift | Use leftmost 8 bits |
        | :-:   | :-:   | :-:         | :-: |
        | byte0 | 0     | 0000000100101100 | 00101100 | 
        | byte1 | 8     | 0000000000000001 |  00000001 |      

        Then, we create a byte by calling the *Byte* constructor.

    Other classes(**Dword**) do basically the same.    

- ## Bits to decimal

# Endians

Nowadays, I just support little endians ...   
But, work in progress for Big Endians too!