#include "BitField.h"
#include <math.h>

BitField::BitField(size_t len = 10) {
    _sizeBit = len;
    _memSize = (len / (8 * sizeof(uint16_t))) + (len % (8 * sizeof(uint16_t)) != 0);
    _mem = new uint16_t[_memSize];
    std::memset(_mem, 0, _memSize);
}

BitField::BitField(const BitField& tmp) {
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = new uint16_t[_memSize];
    std::memcpy(_mem, tmp._mem, _memSize * sizeof(uint16_t));
}

BitField& BitField::operator=(const BitField& tmp){
    if (_sizeBit != tmp._sizeBit){
        delete [] _mem;
        _sizeBit = tmp._sizeBit;
        _memSize = tmp._memSize;
        _mem = new uint16_t[_memSize];
    }
    std::memcpy(_mem, tmp._mem, _memSize * sizeof(uint16_t));
    return *this;
}

uint16_t BitField::GetMask(size_t n) const {
    return 1 << (n % (8 * sizeof(uint16_t)));
}

void BitField::SetBit(size_t n){
    _mem[GetMemIndex(n)] |= GetMask(n);
}

size_t BitField::GetMemIndex(size_t n) const {
    if (n >= _sizeBit)
        throw "Bit out of range!";
    return n / (8 * sizeof(uint16_t));
}

uint8_t BitField::GetBit(size_t n) const {
    return (_mem[GetMemIndex(n)] & GetMask(n)) != 0;
}

void BitField::ClrBit(size_t n){
    _mem[GetMemIndex(n)] &= ~GetMask(n);
}

BitField BitField::operator|(const BitField& tmp){
    BitField B(*this);
    for (size_t i = 0; i < _memSize; i++){
        B._mem[i] = _mem[i] | tmp._mem[i];
    }
    return B;
}

BitField BitField::operator&(const BitField& tmp){
    BitField B(*this);
    for (size_t i = 0; i < _memSize; i++){
        B._mem[i] &= tmp._mem[i];
    }
    return B;
}

BitField BitField::operator^(const BitField& tmp){
    BitField B(*this);
    for (size_t i = 0; i < _memSize; i++){
        B._mem[i] ^= tmp._mem[i];
    }
    return B;
}

bool BitField::operator==(const BitField& tmp) const{
    for (size_t i = 0; i < _memSize; i++){
        if (_mem[i] != tmp._mem[i]){
            return false;
        }
    }
    return true;
}

BitField BitField::operator~(){
    BitField cpy = BitField(*this);
    for (int i = 0; i < _sizeBit; i++){
        if (GetBit(i)){
            cpy.ClrBit(i);
        }
        else{
            cpy.SetBit(i);
        }
    }
    return cpy;
}


BitField::BitField(const BitField&& tmp){
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = tmp._mem;
}

BitField& BitField::operator=(const BitField&& tmp){
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = tmp._mem;
    return *this;
}


