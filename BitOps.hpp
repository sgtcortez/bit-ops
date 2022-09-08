#include <bits/stdint-uintn.h>
#include <cstdint>
#include <cstdlib>
#include <string>

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

template <class type, class Index>
class BitOp
{
    public:
        virtual std::string to_string() const noexcept = 0;
        virtual type restore() const noexcept = 0;
        virtual std::uint8_t bits_size() const noexcept = 0;
        virtual void flip(const Index index) = 0;
        virtual bool operator[](const Index index) const noexcept = 0;
};

class Byte : public BitOp<std::uint8_t, ByteIndex>
{
    private:
        // Handle individual bits
        std::uint8_t bit0:1; 
        std::uint8_t bit1:1;
        std::uint8_t bit2:1;
        std::uint8_t bit3:1;
        std::uint8_t bit4:1;
        std::uint8_t bit5:1;
        std::uint8_t bit6:1;
        std::uint8_t bit7:1;
    public:
        Byte(std::uint8_t number);
  
        std::string to_string() const noexcept;
        std::uint8_t restore() const noexcept;
        std::uint8_t bits_size() const noexcept;
        void flip(const ByteIndex index);
        bool operator[](const ByteIndex index) const noexcept;
};

class Word : public BitOp<std::uint16_t, WordIndex>
{
    private:
        Byte byte0;
        Byte byte1;
    public:
        Word(std::uint16_t number);
        std::string to_string() const noexcept;
        std::uint16_t restore() const noexcept;
        std::uint8_t bits_size() const noexcept;
        void flip(const WordIndex index);
        bool operator[](const WordIndex index) const noexcept;

};

class Dword : public BitOp<std::uint32_t, DwordIndex>
{
    private:
        Word word0;
        Word word1;
    public:
        Dword(std::uint32_t number);
        std::string to_string() const noexcept;
        std::uint32_t restore() const noexcept;
        std::uint8_t bits_size() const noexcept;   
        void flip(const DwordIndex index);     
        bool operator[](const DwordIndex index) const noexcept;
};

class Qword : public BitOp<std::uint64_t, QwordIndex>
{
    private:
        Dword dword0;
        Dword dword1;
    public:
        Qword(std::uint64_t number);
        std::string to_string() const noexcept;
        std::uint64_t restore() const noexcept;
        std::uint8_t bits_size() const noexcept;   
        void flip(const QwordIndex index);     
        bool operator[](const QwordIndex index) const noexcept;        
};


