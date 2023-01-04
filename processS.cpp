#include <iostream>

int main(int argn,char* args[]){
    int number;
    int sum = 0;
    std::cin >> number;
    while(number){
        sum+=number;
        std::cin >> number;
    }
    std::cout << sum <<'\n';
    return 0;
}