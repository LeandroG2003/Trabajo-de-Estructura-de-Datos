//
//  main.c
//  abb
//
//  Created by Mauro San Martín on 7/5/18.
//  Copyright © 2018 Mauro San Martín. All rights reserved.
//

#ifndef stdio_h
#include <stdio.h>
#define stdio_h
#endif

#ifndef stdlib_h
#include <stdlib.h>
#define stdlib_h
#endif

#ifndef abb_h
#include "abb.h"
#define abb_h
#endif


int main(int argc, const char * argv[]) {
    Abb *arbol = creaAbbVacio();
    arbol = insertaValorAbb(arbol,5);
    arbol = insertaValorAbb(arbol,8);
    arbol = insertaValorAbb(arbol,3);
    arbol = insertaValorAbb(arbol,9);
    arbol = insertaValorAbb(arbol,7);
    
    recorreAbbEnOrden(arbol);
    
    muestraArbolGV(arbol, "abb", 5);
    
    buscaValorRutaAbb(arbol, 3);
    printf("\n");
    buscaValorRutaAbb(arbol, 9);
    printf("\n");
    buscaValorRutaAbb(arbol, 7);
    printf("\n");
    buscaValorRutaAbb(arbol, 10);
    printf("\n");

    return 0;
}
