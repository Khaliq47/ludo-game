#ifndef UTILS_H
#define UTILS_H

#include <iostream>


template <typename T>
T maxOf(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>
void printArray(T arr[], int n) {
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}


template <typename T>
int findIndex(T arr[], int n, T value) {
    for (int i = 0; i < n; i++)
        if (arr[i] == value) return i;
    return -1;
}



class Player; 

int humanChoice(Player& p, int roll);   
int botChoice(Player& p, int roll);     

#endif
