#pragma once
#include <vector>
#include <iostream>
#include <cstdint>
#include <cstring>

class BitField {
private:
    size_t _sizeBit;
    uint16_t* _mem;
    size_t _memSize;

    size_t GetMemIndex(size_t n) const;
    uint16_t GetMask(size_t n) const;
public:
    BitField(size_t len);
    BitField(const BitField& tmp);
    BitField(const BitField&& tmp);
    BitField& operator=(const BitField&& tmp);
    BitField& operator=(const BitField& tmp);
    
    size_t GetLength() const{
        return _sizeBit;
    } // Получить количество бит
    void SetBit(size_t n);
    void ClrBit(size_t n);
    uint8_t GetBit(size_t n) const;


    BitField operator|(const BitField& tmp);
    BitField operator&(const BitField& tmp);
    BitField operator^(const BitField& tmp);
    bool operator==(const BitField& tmp) const;
    BitField operator~();

    friend std::ostream& operator<<(std::ostream& os, BitField& f){
        for (int i = 0; i < f.GetLength(); i++){
            if (i % 8 == 0){
                std::cout<<" ";
            }
            if (f.GetBit(i)){
                std::cout<<"1";
            }
            else{
                std::cout<<"0";
            }
        }
        std::cout<<"\n";
        return os;
    } 


    ~BitField(){
    }
};