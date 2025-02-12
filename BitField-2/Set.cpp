#include "Set.h"
#include <math.h>

Set::Set(size_t mp) : _bitField(mp), _maxPower(mp){
}

Set::Set(const Set& set) : _bitField(set._bitField), _maxPower(set._maxPower){
}

Set::Set(const BitField& bf)  : _bitField(bf), _maxPower(bf.GetLength()){
}

void Set::InsElem(uint64_t elem){
    _bitField.SetBit(elem);
}

void Set::DelElem(uint64_t elem){
    _bitField.ClrBit(elem);
}

bool Set::IsMember(uint64_t elem) const{
    return _bitField.GetBit(elem);
}

bool Set::operator==(const Set& tmp) const{
    return _bitField == tmp._bitField;
}

Set& Set::operator=(const Set& tmp){
    _maxPower = tmp._maxPower;
    _bitField = tmp._bitField;
    return *this;
}

Set Set::operator+(const Set& tmp){
    return _bitField | tmp._bitField;
}

Set Set::operator+(uint64_t elem){
    Set s(*this);
    s.InsElem(elem);
    return s;
}

Set Set::operator-(uint64_t elem){
    Set s(*this);
    s.DelElem(elem);
    return s;
}
Set Set::operator*(const Set& ymp){
    return _bitField & ymp._bitField;
}
Set Set::operator~(){
    return Set(~_bitField);
}

bool Set::operator!= (const Set &s) const{
    return (_bitField == s._bitField) == 0;
}

std::vector<uint64_t> Set::GetPrimary(){
    BitField f = _bitField;
    std::vector<uint64_t> array;
    array.push_back(1);
    for (size_t i = 2; i <= sqrt(_maxPower); i++){
        if (f.GetBit(i) != 1) continue;
        array.push_back(i);
        for (size_t j = i + 1; j < _maxPower; j++){
            if (f.GetBit(j) == 1 && j % i == 0){
                f.ClrBit(j);
            }
        }
    }
    for (size_t i = sqrt(_maxPower) + 1; i < _maxPower; i++){
        if (f.GetBit(i) == 1){
            array.push_back(i);
        }
    }
    return array;
}