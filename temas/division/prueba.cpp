#include <bits/stdc++.h>

#include "../../tests/test.h"

using namespace std;

/*
    Tienes una función, con dos parámetros:
    - a: Es un número entero positiva.
    - b: Es un número entero positiva.

    Quiero que retornes la división exacta de a sobre b, en caso que b sea 0, que retornes -1
*/

int division(int a, int b){
    // TODO resolver el problema desde aquí
    return a / (b );
}

// Parte donde inicia el ejecutable
int main(){
    test_function("tests/00_01", division);
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