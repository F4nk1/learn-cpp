#include <bits/stdc++.h>

#include "../../tests/test.h"

using namespace std;

/*
    Tienes una función, con dos parámetros:
    - a: Es un número entero.
    - b: Es un número entero.

    Quiero que halles la suma de los dos números y que lo retornes como un int    
*/

int suma(int a, int b){
    // TODO resolver el problema desde aquí
    return a + b;
}

// Parte donde inicia el ejecutable
int main(){
    test_function("tests/00_00", suma);
}

/*
    FORMA DE EJECUCIÓN:
    * Para linux
    - g++ <nombre_del_programa>.cpp -o <nombre_del_ejecutable>.o
    - ./<nombre_del_ejecutable>.o
    * Para windows
    - g++ <nombre_del_programa>.cpp -o <nombre_del_ejecutable>.exe
    - ./<nombre_del_ejecutable>.exe    
*/