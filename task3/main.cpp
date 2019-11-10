#include <iostream>

struct NullType {
};

template<class Head, class Tail>
struct Typelist {};

template<class TList, template<class> class Unit>
class GenScatterHierarchy;

template<class T1, class T2, template<class> class Unit>
class GenScatterHierarchy<Typelist<T1, T2>, Unit>
        : public GenScatterHierarchy<T1, Unit>, public GenScatterHierarchy<T2, Unit> {
public:
    template<typename T>
    struct Rebind {
        typedef Unit<T> Result;
    };
};

template<class AtomicType, template<class> class Unit>
class GenScatterHierarchy : public Unit<AtomicType> {
    template<typename T>
    struct Rebind {
        typedef Unit<T> Result;
    };
};

template<template<class> class Unit>
class GenScatterHierarchy<NullType, Unit> {
    template<typename T>
    struct Rebind {
        typedef Unit<T> Result;
    };
};


template<class T>
struct Holder {
    T value;
};

struct Bar {};

typedef GenScatterHierarchy<Typelist<int, std::string/*, Bar*/>, Holder> WidgetInfo;

template<class T, class H>
typename H::template Rebind<T>::Result &Field(H &obj) {
    return obj;
}

int main() {
    WidgetInfo obj;
    int name = static_cast<Holder<int> &>(obj).value;
    std::cout << "\"" << name << "\"";
    std::cout << Field<int>(obj).value;
    return 0;
}