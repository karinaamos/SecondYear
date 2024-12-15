#include "BitField.h"


size_t BitField::GetMemIndex(size_t n) const{
    if (n >= _sizeBit)
        throw "Bit out of range!";
    size_t index = n / (8 * sizeof(uint16_t));
}
uint16_t BitField::GetMask(size_t n) const {
    return 1 << (n % (8 * sizeof(uint16_t)));
}

BitField::BitField(size_t len) {
    _sizeBit = len;
    _memSize = (len / (8 * sizeof(uint16_t))) + (len % (8 * sizeof(uint16_t)) != 0);
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = 0;
}

BitField::BitField(const BitField& tmp) {
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
}

BitField& BitField::operator=(const BitField& tmp) {
    if (_sizeBit != tmp._sizeBit){
        delete [] _mem;
        _sizeBit = tmp._sizeBit;
        _memSize = tmp._memSize;
        _mem = new uint16_t[_memSize];
    }
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
    return *this;
}
    
size_t BitField::GetLength() const {
    return _sizeBit;
}
void BitField::SetBit(size_t n) {
    _mem[GetMemIndex(n)] |= GetMask(n);
}
void BitField::ClrBit(size_t n) {
    uint16_t mask = GetMask(n);
    mask =~ mask;
    _mem[GetMemIndex(n)] &= mask;
}
uint8_t BitField::GetBit(size_t n) const {
    return (_mem[GetMemIndex(n)] & GetMask(n)) != 0;
}
BitField BitField::operator|(const BitField& tmp) {
    BitField B(*this);
    for (size_t i=0; i < _memSize; i++){
        B._mem[i] = _mem[i] | tmp._mem[i];
    }
    return B;
}

BitField BitField::operator&(const BitField& tmp) {
    BitField B(*this);
    for (size_t i=0; i < _memSize; i++){
        B._mem[i] = _mem[i] & tmp._mem[i];
    }
    return B;
}
BitField BitField::operator^(const BitField& tmp) {
    BitField B(*this);
    for (size_t i=0; i < _memSize; i++){
        B._mem[i] = _mem[i] ^ tmp._mem[i];
    }
    return B;
}
bool BitField::operator==(const BitField& tmp) const{
    for (size_t i=0; i<_memSize; i++){
        if (_mem[i] != tmp._mem[i]){
            return false;
        }
    }
    return true;
}
BitField BitField::operator~(){
    BitField cpy = BitField(*this);
    for (size_t i=0; i<_sizeBit; i++){
        if (GetBit(i)){
            cpy.ClrBit(i);
        }
        else{
            cpy.SetBit(i);
        }
    }
    return cpy;
}


size_t BitField:: GetByteIndex(size_t num_id) const {
    return bit_off[num_id] / 8;
}

size_t BitField:: GetBitOffset(size_t num_id) const {
    return bit_off[num_id] % 8;
}

size_t BitField:: GetBitCount(unsigned int num) const {
    if (num == 0){
        return 1; 
    }
    return std::ceil(std::log2(num + 1));
}

void BitField:: AddNumber(unsigned int number) {
    size_t bits = GetBitCount(number);
    bit_off.push_back(data.size() * 8);
    bit_counts.push_back(bits);
    num_numbers++;
    size_t new_bits_needed = data.size() * 8 + bits;
    size_t new_bytes_needed = (new_bits_needed + 7) / 8; // Округляем до байтов
    if (new_bytes_needed > data.size()){
        data.resize(new_bytes_needed, 0);
    }
    SetNumber(num_numbers -1, number);
}

void BitField:: SetNumber(size_t index, unsigned int number) {
    if (index >= num_numbers){ 
        throw std::out_of_range("Error");
    }
    size_t byte_id = GetByteIndex(index);
    size_t bit_off = GetBitOffset(index);
    size_t bits = bit_counts[index]; // Используем сохраненное количество битов
    unsigned int mask = (1u << bits) - 1; // Маска для выделения нужных битов
    number &= mask; // Убираем лишние биты из числа
    // Устанавливаем число в битовом поле
    for (size_t i = 0; i < bits; ++i) {
        if ((number >> i) & 1) {
            data[byte_id] |= (1u << (bit_off + i));
        } 
        else{
            data[byte_id] &= ~(1u << (bit_off + i));
        }
    }
}

unsigned int BitField:: GetNumber(size_t index) const {
    if (index >= num_numbers){
        throw std::out_of_range("Error");
    }
    size_t byte_id = GetByteIndex(index);
    size_t bit_off = GetBitOffset(index);
    size_t bits = bit_counts[index]; // Используем сохраненное количество битов
    unsigned int mask = (1u << bits) - 1;

    return (data[byte_id] >> bit_off) & mask;
}

size_t BitField:: GetTotalBits() const {
    size_t t_bit = 0;
    for (size_t bits : bit_counts) {
        t_bit += bits;
    }
    return t_bit;
}

size_t BitField:: GetNumNumbers() const { 
    return num_numbers; 
}


