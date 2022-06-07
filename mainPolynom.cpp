//
// Created by user on 19.03.2022.
//

#include "Polynomial/Polynomial.h"

int main()
{
    Polynomial p1(2);
    std::cout << "Polynomial p1 was created" << std::endl;
    std::cout << p1;

    Polynomial p2(2);
    std::cout << "Polynomial p2 was created" << std::endl;
    std::cout << p2;

//    // присваивание
//    Polynomial pCopy = p1;
//    std::cout << "Polynomial pCopy was created" << std::endl;
//    std::cout << pCopy;
//
//    //копирование
//    pCopy = p2;
//    std::cout << pCopy;
//    p2 *= p1;
//    p2 /= 5.78;
//    std::cout << p2[78];

    return 0;
}
