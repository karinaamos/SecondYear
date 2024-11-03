#include "Set.h"
#include <cmath>

Set::Set(size_t mp) : _bitField(mp) {
}
Set::Set(const Set &s) : _maxPower(s._maxPower), _bitField(s._bitField){

} 
Set::Set(const BitField &bf) : _maxPower(bf.GetLength()), _bitField(bf){

}

size_t Set::GetMaxPower() const{
    return _maxPower;
}    
void Set::InsElem(const uint64_t Elem){
    if (Elem<_maxPower){
        _bitField.SetBit(Elem);
    }
}
void Set::DelElem(const uint64_t Elem){
    if (Elem < _maxPower){
        _bitField.ClrBit(Elem);
    }
}
bool Set::IsMember(const uint64_t Elem) const{
    return Elem < _maxPower && _bitField.GetBit(Elem);
}


bool Set::operator== (const Set &s) const{
    if (_maxPower != s._maxPower){
        return false;
    }
    return _bitField == s._maxPower;
}
bool Set::operator!= (const Set &s) const{
    
}
Set& Set::operator=(const Set &s){
    _maxPower = s._maxPower;
    _bitField = s._bitField;
    return *this;
}
Set Set::operator+ (const uint64_t Elem){
    Set result(*this);
    result.InsElem(Elem);
    return result;
}
                                  
Set Set::operator- (const uint64_t Elem){
    Set result(*this);
    result.DelElem(Elem);
    return result;
}
                                   
Set Set::operator+ (const Set &s){
    Set result(_maxPower);
    result._bitField = _bitField | s._bitField;
    return result;
}
Set Set::operator* (const Set &s){
    Set result(_maxPower);
    result._bitField = _bitField & s._bitField;
    return result;
}
Set Set::operator~ (){
    Set result(_maxPower);
    result._bitField = _bitField;
    return result;
}
std::vector<uint64_t> Set::GetPrimary(){
    std::vector<uint64_t> prim;
    BitField s=_bitField;
    for (size_t i = 2; i < sqrt(_maxPower); ++i) {
        if (s.GetBit(i) != 1) { 
            prim.push_back(i); 
            for (size_t j = i + 1; j < _maxPower; j ++) {
                s.ClrBit(j);
            }
        }
    }
    for (size_t i = sqrt(_maxPower) + 1; i < _maxPower; i++) {
        if (s.GetBit(i) == 1) { 
            prim.push_back(i); 
        }
    }
    return prim;
}