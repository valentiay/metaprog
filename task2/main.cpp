#include <iostream>

//template<class T, class U>
//struct is_same {
//    is_same() : value(false) {}
//    bool value;
//};
//
//template<class T>
//struct is_same<T, T> {
//    is_same() : value(true) {}
//    bool value;
//};

struct Nil {
};

template<class Head, class Tail>
struct TypeList {
};

template<class List>
struct Length;
template<>
struct Length<Nil> {
    enum {
        result = 0
    };
};
template<class Head, class Tail>
struct Length<TypeList<Head, Tail> > {
    enum {
        result = Length<Tail>::result + 1
    };
};

template<class List, class A>
struct Append;
template <class A>
struct Append<Nil, A> {
    typedef TypeList<A, Nil> result;
};
template<class Head, class Tail, class A>
struct Append<TypeList<Head, Tail>, A> {
    typedef TypeList<Head, typename Append<Tail, A>::result > result;
};


//template<class S, >
//struct getIndexOf {
//};

int main() {
    std::cout << Length<TypeList<int, TypeList<double, Nil> > >::result <<
              std::endl;
    std::cout << Length<Append<Append<Nil, int>::result, double>::result>::result << std::endl;
    return 0;
}