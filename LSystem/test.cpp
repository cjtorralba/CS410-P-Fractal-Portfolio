//
// Created by cjtorralba on 6/14/23.
//

#include <stack>
#include <iostream>

using namespace std;

void test() {
    std::stack<double*> b;

}

int main() {
    std::stack<double*> bracketStack;
    double a[2];
    a[0] = 1;
    a[1] = 2;

    bracketStack.push(a);
    std::cout << "test";
}