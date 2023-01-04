#include <iostream>

int main(int argn,char* args[]){
    int number;
    std::cin >> number;
    while(number){
        number*=7;
        std::cout << number << '\n';
        std::cin >> number;
    }
    std::cout << 0 <<'\n';
    return 0;
}

