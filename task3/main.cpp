#include <iostream>

struct NullType {
};

template<class Head, class Tail>
struct Typelist {};

template<typename ...Args>
struct MkTypelist
{
    typedef NullType Result;
};

template<typename H, typename ...T>
struct MkTypelist<H, T...>
{
    typedef Typelist<H, typename MkTypelist<T...>::Result> Result;
};

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

struct Bar {
    friend std::ostream&operator<<(std::ostream& os, Bar bar) {
        os << "Bar!";
        return os;
    }
};

typedef GenScatterHierarchy<MkTypelist<int, std::string, Bar>::Result, Holder> Foo;

template<class T, class H>
typename H::template Rebind<T>::Result &Field(H &obj) {
    return obj;
}

int main() {
    Foo obj;
    Bar bar;

    Field<int>(obj).value = 1234;
    Field<std::string>(obj).value = "Hello!";
    Field<Bar>(obj).value = bar;

    std::cout << Field<int>(obj).value << std::endl;
    std::cout << Field<std::string>(obj).value << std::endl;
    std::cout << Field<Bar>(obj).value << std::endl;

    return 0;
}