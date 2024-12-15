#pragma once
#include <iostream>
#include <stdint.h>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>

class BitField {
private:
    size_t _sizeBit;
    uint16_t* _mem;
    size_t _memSize;
    std::vector<unsigned char> data; // хранилище данных в байтах
    std::vector<size_t> bit_off; // Смещения битов для каждого числа
    std::vector<size_t> bit_counts;  // Количество битов для каждого числа
    size_t num_numbers;              // Количество сохраненных чисел

    size_t GetMemIndex(size_t n) const;
    uint16_t GetMask(size_t n) const;
    size_t GetByteIndex(size_t num_id) const;
    size_t GetBitOffset(size_t num_id) const;
    size_t GetBitCount(unsigned int num) const;
    
public:
    void AddNumber(unsigned int number); //добавляет число в BitField
    void SetNumber(size_t index, unsigned int number);
    unsigned int GetNumber(size_t index) const; // возврат числа по индексу
    size_t GetTotalBits() const;  // Возвращает общее количество используемых битов
    size_t GetNumNumbers() const;

    BitField(size_t len);
    BitField(const BitField& tmp);
    BitField& operator=(const BitField& tmp);
    BitField() : num_numbers(0) {} // Конструктор по умолчанию
    
    size_t GetLength() const;
    void SetBit(size_t n);
    void ClrBit(size_t n);
    uint8_t GetBit(size_t n) const;


    BitField operator|(const BitField& tmp);
    BitField operator&(const BitField& tmp);
    BitField operator^(const BitField& tmp);
    bool operator==(const BitField& tmp) const;
    BitField operator~();

    ~BitField(){

    }
};