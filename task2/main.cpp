#include <iostream>

struct Nil {
};

template<class Head, class Tail>
struct TypeList {
};

template<class List, class A>
struct Append;
template<class A>
struct Append<Nil, A> {
    typedef TypeList<A, Nil> result;
};
template<class Head, class Tail, class A>
struct Append<TypeList<Head, Tail>, A> {
    typedef TypeList<Head, typename Append<Tail, A>::result> result;
};

template<class A = Nil, class B = Nil, class C = Nil, class D = Nil>
struct MakeTypeList {
    typedef TypeList<A, typename MakeTypeList<B, C, D>::result > result;
};
template <>
struct MakeTypeList <Nil, Nil> {
    typedef Nil result;
};

template<class List, class A>
struct GetIndexOf;
template<class A>
struct GetIndexOf<Nil, A> {
    enum {
        result = -1
    };
};
template<class Tail, class A>
struct GetIndexOf<TypeList<A, Tail>, A> {
    enum {
        result = 0
    };
};
template<class Head, class Tail, class A>
struct GetIndexOf<TypeList<Head, Tail>, A> {
    enum {
        result = (GetIndexOf<Tail, A>::result == -1) ? -1 : GetIndexOf<Tail, A>::result + 1
    };
};

int main() {
    typedef TypeList<int, Nil> list1;
    typedef TypeList<double, list1> list2;
    typedef Append<list1, double>::result list3;

    std::cout << GetIndexOf<list2, double>::result << std::endl;
    std::cout << GetIndexOf<list3, double>::result << std::endl;
    std::cout << std::endl;

    std::cout << GetIndexOf<MakeTypeList<int, int, int, int>::result, int>::result << std::endl;
    std::cout << GetIndexOf<MakeTypeList<int, int, int, int>::result, double>::result << std::endl;
    std::cout << GetIndexOf<MakeTypeList<int, double, int, double>::result, int>::result << std::endl;
    std::cout << GetIndexOf<MakeTypeList<int, double, int, double>::result, double>::result << std::endl;
    return 0;
}