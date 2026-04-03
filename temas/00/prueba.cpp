#include <bits/stdc++.h>

#include "../../tests/test.h"

using namespace std;

int suma(int a, int b){
    return a - b;
}

int main(){
    cout<<"Hola mundo"<<endl;

    auto respuesta = test_function("../../tests/00_00", suma);
    
    cout << respuesta.second << endl;
        
}