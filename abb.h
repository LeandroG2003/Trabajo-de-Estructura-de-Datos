//
//  abb.h
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
#define abb_h
#endif /* abb_h */

typedef struct _nodo{
    int dato;
    struct _nodo *hizq, *hder;
} Nodo;

typedef Nodo Abb;


Abb *creaAbbVacio(){
    return(NULL);
}


int esAbbVacio(Abb *arbol){
    if(arbol == NULL){
        return(1);
    }
    return(0);
}


int buscaValorAbb(Abb *arbol, int valor){
    if(arbol == NULL){
        return(0);
    }else if(valor < arbol->dato){
        return(buscaValorAbb(arbol->hizq, valor));
    }else if(valor > arbol->dato){
        return(buscaValorAbb(arbol->hder, valor));
    }
    return(1);
}

int buscaValorRutaAbb(Abb *arbol, int valor){
    if(arbol == NULL){
        return(0);
    }else if(valor < arbol->dato){
        int encontrado = buscaValorRutaAbb(arbol->hizq, valor);
        if (encontrado == 1){
            printf("i");
        }
        return(encontrado);
    }else if(valor > arbol->dato){
        int encontrado = buscaValorRutaAbb(arbol->hder, valor);
        if (encontrado == 1){
            printf("d");
        }
        return(encontrado);
    }
//    printf("X");
    return(1);
}


Abb *insertaValorAbb(Abb *arbol, int valor){
    if(arbol == NULL){
        arbol = malloc(sizeof(Abb));
        arbol->hizq = NULL;
        arbol->hder = NULL;
        arbol->dato = valor;
    }else if(valor < arbol->dato){
        arbol->hizq = insertaValorAbb(arbol->hizq, valor);
    }else if(valor > arbol->dato){
        arbol->hder = insertaValorAbb(arbol->hder, valor);
    }
    return(arbol);
}


Abb *eliminaValorAbb(Abb *arbol, int valor){
    if(arbol == NULL){//elemento no encontrado
        return(NULL);
    }else if(valor < arbol->dato){
        arbol->hizq = eliminaValorAbb(arbol->hizq, valor);
    }else if(valor > arbol->dato){
        arbol->hder = eliminaValorAbb(arbol->hder, valor);
    }else{//elemento encontrado
        //hoja
        if((arbol->hizq == NULL)&&(arbol->hder == NULL)){
            free(arbol);
            return(NULL);
            //solo hijo izquierdo
        }else if((arbol->hizq != NULL)&&(arbol->hder == NULL)){
            Abb *aux = arbol->hizq;
            free(arbol);
            return(aux);
            //solo hijo derecho
        }else if((arbol->hizq == NULL)&&(arbol->hder != NULL)){
            Abb *aux = arbol->hder;
            free(arbol);
            return(aux);
            //2 hijos
        }else if((arbol->hizq != NULL)&&(arbol->hder != NULL)){
            //Buscar menor de los mayores
            Abb *aux = arbol->hder;
            Abb *sgte = aux->hizq;
            while(sgte!=NULL){
                aux = sgte;
                sgte = sgte->hizq;
            }
            //reemplazar valor
            arbol->dato = aux->dato;
            //Llamar recursivamente con el subárbol derecho
            arbol->hder = eliminaValorAbb(arbol->hder, arbol->dato);
        }
    }
    return(arbol);
}

//busca min
//busca max

//recorre en orden
void recorreAbbEnOrden(Abb *arbol){
    if(arbol != NULL){
        recorreAbbEnOrden(arbol->hizq);
        printf("%i \n", arbol->dato);
        recorreAbbEnOrden(arbol->hder);
    }
}


//elimina arbol
void eliminaAbb(Abb *arbol){
    if(arbol != NULL){
        eliminaAbb(arbol->hizq);
        eliminaAbb(arbol->hder);
        free(arbol);
    }
}



Abb *leeArchivoEnABB(const char *nombreArchivoDatos){
    //no se hace chequeo de errores:
    // - archivo debe existir
    // - n debe coincidir con la cantidad de enteros en la secuencia almacenada en el archivo
    FILE *archivo = fopen(nombreArchivoDatos,"rb");
    Abb *arbol = creaAbbVacio();
    int n, *numeros;
    fread(&n, sizeof(int), 1,archivo);
    numeros = malloc(sizeof(int)*n);
    fread(numeros, sizeof(int), n, archivo);
    fclose(archivo);
    for(int i = 0; i<n; i++){
        arbol=insertaValorAbb(arbol, numeros[i]);
    }
    return(arbol);
}


int escribeAbbEnOrden(Abb *arbol, FILE *archivo){
    if(arbol == NULL){
        return(0);
    }
    int nizq, nder;
    nizq = escribeAbbEnOrden(arbol->hizq, archivo);
    fwrite(&(arbol->dato), sizeof(int), 1, archivo);
    nder = escribeAbbEnOrden(arbol->hder, archivo);
    return(nizq + 1 + nder);
}


int generaArchivoOrdenado(Abb *arbol, const char *nombreArchivoOrdenado){
    FILE *archivo = fopen(nombreArchivoOrdenado,"wb");
    int n = 0;
    fwrite(&n, sizeof(int), 1,archivo);
    n = escribeAbbEnOrden(arbol, archivo);
    fclose(archivo);
    
    archivo = fopen(nombreArchivoOrdenado,"r+b");
    fwrite(&n, sizeof(int), 1,archivo);
    fclose(archivo);
    return(1);
}

/* Recorre recursivamente un arbol en orden y genera salida gv en archivo,
 retorna el numero de nodos visitados */
int recorreArbolGV(Abb *arbol, FILE *archivo){
    int visitadosIzq, visitadosDer;
    if(arbol == NULL){
        //printf("\nNULO!\n");
        return (0);
    }else{
        visitadosIzq = recorreArbolGV(arbol->hizq, archivo);
        if(arbol->hizq != NULL)
            fprintf(archivo, "%i -> %i [label=\"hi\"]\n", arbol->dato, arbol->hizq->dato);
        if(arbol->hder != NULL)
            fprintf(archivo, "%i -> %i [label=\"hd\"]\n", arbol->dato, arbol->hder->dato);
        visitadosDer = recorreArbolGV(arbol->hder, archivo);
    }
    return(visitadosIzq + 1 + visitadosDer);
}

/* Muestra arbol */
void muestraArbolGV(Abb *arbol, char *tipo, int tamano){
    int auxTamano;
    FILE *archivo;
    char nombreArchivo[20];
    sprintf(nombreArchivo, "%s%i.dot", tipo, tamano);
    archivo = fopen(nombreArchivo,"w");
    fprintf(archivo, "digraph %s%i\n {\n", tipo, tamano);
    auxTamano = recorreArbolGV(arbol, archivo);
    fprintf(archivo, "}\n");
    fclose(archivo);
    printf("\n GV Generado! \n Nodos visitados : %i (Tasa:%1.3f)\n$$$\n\n", auxTamano, (double)auxTamano/(double)tamano);
    //getchar();
}



