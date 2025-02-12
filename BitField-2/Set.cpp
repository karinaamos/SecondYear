#include "Set.h"
#include <math.h>
#include "BitField.h"
#include <vector>

Set::Set(size_t mp):_bitField(mp){
    _maxPower = mp;
}
Set::Set(const Set &set): _bitField(set._bitField), _maxPower(set._maxPower){}       // конструктор копирования
Set::Set(const BitField &bf): _bitField(bf),  _maxPower(bf.GetLength()){} // конструктор преобразования типа

// доступ к битам
size_t Set::GetMaxPower(void) const{    // максимальная мощность множества
    return _maxPower;
}
void Set::InsElem(const uint64_t Elem){       // включить элемент в множество
    _bitField.SetBit(Elem);
}
void Set::DelElem(const uint64_t Elem){       // удалить элемент из множества
    _bitField.ClrBit(Elem);
}
bool Set::IsMember(const uint64_t Elem) const { // проверить наличие элемента в множестве
    return _bitField.GetBit(Elem);
}
// теоретико-множественные операции
bool Set::operator== (const Set &s) const{ // сравнение
    return _bitField == s._bitField;
}
bool Set::operator!= (const Set &s) const{ // сравнение
    if (_bitField == s._bitField){
        return false;
    }
    return true;
}
Set& Set::operator=(const Set& s){  // присваивание
    _maxPower = s.GetMaxPower();
    _bitField = s._bitField;
    return *this;
}
Set Set::operator+ (const uint64_t Elem){ // объединение с элементом
                                   // элемент должен быть из того же универса
    Set s(*this);
    s.InsElem(Elem);
    return s;
}
Set Set::operator- (const uint64_t Elem){ // разность с элементом
                                   // элемент должен быть из того же универса
    Set s(*this);
    s.DelElem(Elem);
    return s;
}
Set Set::operator+ (const Set& s){  // объединение
    return _bitField | s._bitField;
}
Set Set::operator* (const Set &s){  // пересечение
    return _bitField & s._bitField;
}
Set Set::operator~ (){          // дополнение
    return Set(~_bitField);
}
// Выдать простые числа множества
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