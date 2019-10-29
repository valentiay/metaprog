#include <iostream>


struct Nil {
};

template<class Head, class Tail>
struct TypeList {
};

/*----------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------*/

template<class A = Nil, class B = Nil, class C = Nil, class D = Nil>
struct MakeTypeList {
    typedef TypeList<A, typename MakeTypeList<B, C, D>::result> result;
};

template<>
struct MakeTypeList<Nil, Nil> {
    typedef Nil result;
};

/*----------------------------------------------------------------------------*/

template<int A, class Tail>
struct Array;

template<class Array>
struct Increment;

template<int Head, class Tail>
struct Increment<Array<Head, Tail> > {
    typedef Array<Head + 1, typename Increment<Tail>::result> result;
};

template<>
struct Increment<Nil> {
    typedef Nil result;
};

/*----------------------------------------------------------------------------*/

template<class List, class A>
struct GetIndexOf;

template<class A>
struct GetIndexOf<Nil, A> {
    typedef Nil result;
};

template<class Tail, class A>
struct GetIndexOf<TypeList<A, Tail>, A> {
    typedef Array<0, typename Increment<typename GetIndexOf<Tail, A>::result>::result> result;
};

template<class Head, class Tail, class A>
struct GetIndexOf<TypeList<Head, Tail>, A> {
    typedef typename Increment<typename GetIndexOf<Tail, A>::result>::result result;
};

/*----------------------------------------------------------------------------*/

template<class Array>
struct PrintArray;

template<int Head, class Tail>
struct PrintArray<Array<Head, Tail> > {
    static void apply() {
        std::cout << Head << " :: ";
        PrintArray<Tail>::apply();
    }
};

template<>
struct PrintArray<Nil> {
    static void apply() {
        std::cout << "Nil" << std::endl;
    }
};

/*----------------------------------------------------------------------------*/

int main() {
    typedef TypeList<int, Nil> list1;
    typedef TypeList<double, list1> list2;
    typedef Append<list1, double>::result list3;

    std::cout << std::endl << "double in double :: int :: Nil:" << std::endl;
    PrintArray<GetIndexOf<list2, double>::result>::apply();

    std::cout << std::endl << "double in int :: double :: Nil:" << std::endl;
    PrintArray<GetIndexOf<list3, double>::result>::apply();

    std::cout << std::endl << "int in int :: int :: int :: int :: Nil:" << std::endl;
    PrintArray<GetIndexOf<MakeTypeList<int, int, int, int>::result, int>::result>::apply();

    std::cout << std::endl << "double in int :: int :: int :: int :: Nil:" << std::endl;
    PrintArray<GetIndexOf<MakeTypeList<int, int, int, int>::result, double>::result>::apply();

    std::cout << std::endl << "int in int :: double :: int :: double :: Nil:" << std::endl;
    PrintArray<GetIndexOf<MakeTypeList<int, double, int, double>::result, int>::result>::apply();

    std::cout << std::endl << "double in int :: double :: int :: double :: Nil:" << std::endl;
    PrintArray<GetIndexOf<MakeTypeList<int, double, int, double>::result, double>::result>::apply();
    return 0;
}