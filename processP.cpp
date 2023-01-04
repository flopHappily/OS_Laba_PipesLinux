#include <iostream>

int main(int argn,char* args[]){
    int number;
    std::cin >> number;
    while(number){
        number*=number*number;
        std::cout << number << '\n';
        std::cin >> number;
    }
    std::cout << number <<'\n';
    return 0;
}