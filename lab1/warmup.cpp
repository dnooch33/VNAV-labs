#include <iostream>
#include <vector>


void reset(int &i){
    i = 0;
}

int main(){
    int i = 0, j;
    j = ++i;
    j = i++;
    std::cout << "Question 1" << std::endl;
    std::cout << "i = " << i << std::endl;
    std::cout << "j = " << j << std::endl;

    i = 42;
    std::string output = (i < 42) ? "a" : "b";

    std::cout << "Question 2" << std::endl;
    std::cout << output << std::endl;


    std::cout << "References and Pointers" << std::endl;
    int& ri = i;
    i = 5;
    ri = 10;
    std::cout << "Question 1" << std::endl;
    std::cout << i << " " << ri << std::endl;

    i = 42;
    int* k = &i;
    *k = *k**k;
    std::cout << "Question 2" << std::endl;
    std::cout << *k << std::endl;

    int b[4] = {42, 24, 42, 24};
    *(b+2) = *(b+1)-b[3];
    std::cout << "Question 3" << std::endl;
    std::cout << *(b+2) << std::endl;

    reset(j);
    std::cout << "Question 4" << std::endl;
    std::cout << j << std::endl;

    std::cout << "Numbers Question 2" << std::endl;
    int i;
    i = 3.14;
    std:: cout << i << std::endl;

    std::cout << "Numbers Question 3" << std::endl;
    unsigned char c = -1;
    std::cout << c << std::endl;

    std::cout << "Numbers Question 4" << std::endl;
    i = 42;
    if (i) {
        i = 0;
    } else {
        i = 43;
    }

    std::cout << i << std::endl;

    return 0;
}