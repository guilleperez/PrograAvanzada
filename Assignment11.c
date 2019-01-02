/**
 * Crea un arbol binario y lo recorre en
 * preorden, inorden, y en postOrden
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int ROWS = 20, COLS = 4;

typedef enum Node {
    Color,
    Size,
    Act,
    Age
}Node;
Node node;

typedef struct etropia{
    double value;
    Node node;
}Entropia;

typedef struct objeto{
    char *color;
    char *size;
    char *act;
    char *age;
}Objeto;

/* estructura autoreferenciada */
struct nodoArbol {
    struct nodoArbol *ptrIzq;
    /*char ***datos;*/
    Objeto *obetos;
    struct nodoArbol *prtDer;
};

typedef struct nodoArbol NodoArbol; /* sinónimo de la estructura nodoArbol */
typedef NodoArbol *ptrNodoArbol; /* sinónimo de NodoArbol* */

// prototipos
void inOrden(ptrNodoArbol ptrArbol);
//void insertaNodo(ptrNodoArbol *ptrArbol, char ***valores, int hijo);
double calcularEntropiaRelativa(double *count, double I);
void  verificarHijo(ptrNodoArbol *ptrNodo, Objeto *objetos, Node node, char *value, int hijo);

void insertaNodo(ptrNodoArbol *ptrArbol, Objeto *valores, Objeto *valoresOpuesto, int hijo, int pos, char *value, Node node) {

    if (*ptrArbol == NULL) {
        *ptrArbol = malloc(sizeof(NodoArbol));
        printf("-----creando padre-----------\n");
        for (int i = 0; i < ROWS; i++) {
            if (valores[i].color != NULL && valores[i].size != NULL && valores[i].act != NULL && valores[i].age != NULL)
                printf("Objeto is %s, %s, %s, %s\n", valores[i].color, valores[i].size, valores[i].act, valores[i].age);
        }

        if (*ptrArbol != NULL) {
            if(value != NULL){

                verificarHijo(ptrArbol, valores, node, value,  hijo);
            }
            (*ptrArbol)->obetos = valores;
            (*ptrArbol)->ptrIzq = NULL;
            (*ptrArbol)->prtDer = NULL;
        }
    } else {
        //printf("%i\n", hijo);
        //hijo 0 = izquiero, 1 = derecho
        if (hijo == 0) {
            if (pos < 1) {
                if ((*ptrArbol)->ptrIzq == NULL && (*ptrArbol)->prtDer == NULL) {
                    printf("0 y ambos Null, voy izquierda y pos %i\n", pos);
                    insertaNodo(&((*ptrArbol)->ptrIzq), valores, valoresOpuesto, -1, pos + 1, value,  node);
                } else {
                    printf("0 y no Null, voy izquierda y pos %i\n", pos);
                    insertaNodo(&((*ptrArbol)->ptrIzq), valores, valoresOpuesto, 0, pos + 1, value,  node);
                }
            } else {
                //if (((*ptrArbol)->ptrIzq) != NULL && ((*ptrArbol)->prtDer) != NULL) {
                printf("0 y voy ambos y pos %i\n", pos);
                //(*ptrArbol)->obetos
                insertaNodo(&((*ptrArbol)->ptrIzq), valores, valoresOpuesto, 0, pos + 1, value,  node);
                insertaNodo(&((*ptrArbol)->prtDer), valoresOpuesto, valores, 1, pos + 1, value,  node);

            }
            /*if((*ptrArbol)->ptrIzq == NULL && (*ptrArbol)->prtDer == NULL) {
                printf("0 y ambos Null voy izquierda\n");
                insertaNodo(&((*ptrArbol)->ptrIzq), valores, valoresOpuesto, -1, pos+1);
            }else */
            /*if((*ptrArbol)->ptrIzq != NULL && (*ptrArbol)->prtDer == NULL) {
                printf("0 y left no Null, voy derecha\n");
                insertaNodo(&((*ptrArbol)->prtDer), valores, valoresOpuesto, -1, pos+1);
                } */


        } else if (hijo == 1) {
            if (pos < 1) {
                if ((*ptrArbol)->ptrIzq == NULL && (*ptrArbol)->prtDer == NULL)  {
                    printf("1 y ambos Null, voy derecha y pos %i\n", pos);
                    insertaNodo(&((*ptrArbol)->prtDer), valores, valoresOpuesto, -1, pos + 1, value,  node);
                }else{
                    printf("1 y no Null, voy derecha y pos %i\n", pos);
                    insertaNodo(&((*ptrArbol)->prtDer), valores, valoresOpuesto, 1, pos + 1, value,  node);
                }
                // printf("1 y ambos Null, voy izqiuerda\n");

            } else {
                printf("1 y voy ambos y pos %i\n", pos);
                insertaNodo(&((*ptrArbol)->ptrIzq), valoresOpuesto, valores, 0, pos + 1, value,  node);
                insertaNodo(&((*ptrArbol)->prtDer), valores, valoresOpuesto, 1, pos + 1, value,  node);

            }


            /*else if((*ptrArbol)->ptrIzq != NULL && (*ptrArbol)->prtDer == NULL) {
                //printf("1 y left no Null, voy derecha\n");
                insertaNodo(&((*ptrArbol)->prtDer), valores, valoresOpuesto, -1, pos+1);

            }else if((*ptrArbol)->ptrIzq != NULL && (*ptrArbol)->prtDer != NULL, pos+1) {
                if(pos < 1 ) {
                  //  printf("1 y no Null, voy derecha y pos %i\n", pos);
                    insertaNodo(&((*ptrArbol)->prtDer), valores, valoresOpuesto, 1, pos+1);
                }else {
                    //printf("1 y no Null, voy ambos y pos %i\n", pos);
                    insertaNodo(&((*ptrArbol)->ptrIzq), valores, valoresOpuesto, 0, pos+1);
                    insertaNodo(&((*ptrArbol)->prtDer), valores, valoresOpuesto, 1, pos+1);
                }*/

        }


    }
}

void inOrden(ptrNodoArbol ptrArbol) {
        /* si el árbol no está vacío, entonces recórrelo*/
        if (ptrArbol != NULL) {
            inOrden(ptrArbol->ptrIzq);
            Objeto *actual = ptrArbol->obetos;

            for (int i = 0; i < ROWS; ++i) {
                if(actual[i].color != NULL)
                    printf("Objeto is %s, %s, %s, %s\n", actual[i].color, actual[i].size, actual[i].act, actual[i].age);

            }
            printf("\n");

            inOrden(ptrArbol->prtDer);
        }

    }

double calcularEntropiaRelativa(double *count, double I){

    return ((-count[0]/ROWS * log2(count[0]/ROWS) -count[1]/ROWS * log2(count[1]/ROWS))/I);
}

double calcularEntropiaRelativaMinima(double min, double entropia, Node n){

    if(entropia > 0) {
        if (min > entropia) {
            min = entropia;
            node = n;
        }else if(min < 0){
            node = n;
            return entropia;
        }
    }

    return min;
}

double calcularMinimo(Entropia *entropias){

    double min = calcularEntropiaRelativaMinima(entropias[0].value, entropias[0].value, entropias[0].node);
    min = calcularEntropiaRelativaMinima(min, entropias[1].value, entropias[1].node);
    min = calcularEntropiaRelativaMinima(min, entropias[2].value, entropias[2].node);
    min = calcularEntropiaRelativaMinima(min, entropias[3].value, entropias[3].node);
    return min;
}

void  verificarHijo(ptrNodoArbol *ptrNodo, Objeto *objetos, Node node, char *value, int hijo) {

    //crea el arreglo y aloca memoria
    Objeto *datos = calloc(ROWS,sizeof(Objeto));
    Objeto *datosOpuesto = calloc(ROWS,sizeof(Objeto));
    //printf("%s\n", value);
    /*for (int i = 0; i < ROWS; ++i) {
        datos[i] = calloc(COLS, sizeof(char*));
    }*/

    int i = 0;
    for (int i = 0; i < ROWS; i++) {
        switch (node){
            case Color:
                if (objetos[i].color == value) {
                    datos[i] = objetos[i];
                }else{
                    if (objetos[i].color != NULL && objetos[i].size != NULL && objetos[i].act != NULL && objetos[i].age != NULL) {
                       // printf("Valor objetos is %s, %s, %s, %s, %s\n", objetos[i].color, objetos[i].size,
                         //      objetos[i].act, objetos[i].age, value);

                        /*datosOpuesto[i].color = value;
                     datosOpuesto[i].size = objetos[i].size;
                     datosOpuesto[i].act = objetos[i].act;
                     datosOpuesto[i].age = objetos[i].age;*/
                        datosOpuesto[i] = objetos[i];
                    }
                }
                break;
            case Size:
                if (objetos[i].size == value) {
                    datos[i] = objetos[i];
                }else{
                    if (objetos[i].color != NULL && objetos[i].size != NULL && objetos[i].act != NULL && objetos[i].age != NULL) {
                        /*datosOpuesto[i].color = objetos[i].color;
                     datosOpuesto[i].size = value;
                     datosOpuesto[i].act = objetos[i].act;
                     datosOpuesto[i].age = objetos[i].age;*/
                        datosOpuesto[i] = objetos[i];
                    }
                }
                break;
            case Act:
                //printf("%i %s\n",node, value);
                if (objetos[i].act == value) {
                    datos[i] = objetos[i];
                }else{
                    if (objetos[i].color != NULL && objetos[i].size != NULL && objetos[i].act != NULL && objetos[i].age != NULL) {
                        /*datosOpuesto[i].color = objetos[i].color;
                      datosOpuesto[i].size = objetos[i].size;
                      datosOpuesto[i].act = value;
                      datosOpuesto[i].age = objetos[i].age;*/
                        datosOpuesto[i] = objetos[i];
                    }
                }
                break;
            case Age:
                if (objetos[i].age == value) {
                    datos[i] = objetos[i];
                }else{
                    /*
                    if (objetosOpuesto[i].color != NULL && objetosOpuesto[i].size != NULL && objetosOpuesto[i].act != NULL && objetosOpuesto[i].age != NULL)
                        printf("Valor objetos is %s, %s, %s, %s, %s\n", objetosOpuesto[i].color, objetosOpuesto[i].size, objetosOpuesto[i].act, objetosOpuesto[i].age, value);*/
                    if (objetos[i].color != NULL && objetos[i].size != NULL && objetos[i].act != NULL && objetos[i].age != NULL) {
                        /*printf("Valor objetos is %s, %s, %s, %s, %s\n", objetos[i].color, objetos[i].size,
                               objetos[i].act, objetos[i].age, value);*/

                        /*datosOpuesto[i].color = objetos[i].color;
                        datosOpuesto[i].size = objetos[i].size;
                        datosOpuesto[i].act = objetos[i].act;
                        datosOpuesto[i].age = value;*/
                        datosOpuesto[i] = objetos[i];
                        /*printf("Valor is %s, %s, %s, %s, %s\n", datosOpuesto[i].color, datosOpuesto[i].size,
                               datosOpuesto[i].act, datosOpuesto[i].age, value);*/
                    }

                }
                break;
        }

        /*if(datos[i].age != NULL)
            printf("Objeto is %s, %s, %s, %s\n", datos[i].color, datos[i].size, datos[i].act, datos[i].age);*/

        /*if(datosOpuesto[i].age != NULL)
            printf("Objeto is %s, %s, %s, %s\n", datosOpuesto[i].color, datosOpuesto[i].size, datosOpuesto[i].act, datosOpuesto[i].age);*/


    }

    insertaNodo(ptrNodo, datos, datosOpuesto, hijo, 0, value, node);
}

int  nodeInArray(Node node, Node *nodes, int size){
     for (int i=0; i < size; i++) {
         if (nodes[i] == node)
             return 1;
     }
     return 0;
 }

void editarArray(Objeto *objetosLeft,Objeto *objetosRight, Objeto *datos, int node) {

    for (int i = 0; i < ROWS; ++i) {
        switch (node) {
            case Color:
                if (objetosLeft[i].color == "yellow") {
                    objetosLeft[i].color = datos[i].color;
                    objetosLeft[i].size = datos[i].size;
                    objetosLeft[i].act = datos[i].act;
                    objetosLeft[i].age = datos[i].age;
                } else {
                    objetosLeft[i].color = NULL;
                    objetosLeft[i].size = NULL;
                    objetosLeft[i].act = NULL;
                    objetosLeft[i].age = NULL;
                }

                if (objetosRight[i].color == "purple") {
                    objetosRight[i].color = datos[i].color;
                    objetosRight[i].size = datos[i].size;
                    objetosRight[i].act = datos[i].act;
                    objetosRight[i].age = datos[i].age;
                } else {
                    objetosRight[i].color = NULL;
                    objetosRight[i].size = NULL;
                    objetosRight[i].act = NULL;
                    objetosRight[i].age = NULL;
                }

                break;
            case Size:
                if (objetosLeft[i].size == "small") {
                    objetosLeft[i].color = datos[i].color;
                    objetosLeft[i].size = datos[i].size;
                    objetosLeft[i].act = datos[i].act;
                    objetosLeft[i].age = datos[i].age;
                } else {
                    objetosLeft[i].color = NULL;
                    objetosLeft[i].size = NULL;
                    objetosLeft[i].act = NULL;
                    objetosLeft[i].age = NULL;
                }

                if (objetosRight[i].size == "large") {
                    objetosRight[i].color = datos[i].color;
                    objetosRight[i].size = datos[i].size;
                    objetosRight[i].act = datos[i].act;
                    objetosRight[i].age = datos[i].age;
                } else {
                    objetosRight[i].color = NULL;
                    objetosRight[i].size = NULL;
                    objetosRight[i].act = NULL;
                    objetosRight[i].age = NULL;
                }
                break;
            case Act:
                if (objetosLeft[i].act == "stretch") {
                    objetosLeft[i].color = datos[i].color;
                    objetosLeft[i].size = datos[i].size;
                    objetosLeft[i].act = datos[i].act;
                    objetosLeft[i].age = datos[i].age;
                } else {
                    objetosLeft[i].color = NULL;
                    objetosLeft[i].size = NULL;
                    objetosLeft[i].act = NULL;
                    objetosLeft[i].age = NULL;
                }

                if (objetosRight[i].act == "dip") {
                    objetosRight[i].color = datos[i].color;
                    objetosRight[i].size = datos[i].size;
                    objetosRight[i].act = datos[i].act;
                    objetosRight[i].age = datos[i].age;
                } else {
                    objetosRight[i].color = NULL;
                    objetosRight[i].size = NULL;
                    objetosRight[i].act = NULL;
                    objetosRight[i].age = NULL;
                }
                break;
            case Age:
                if (objetosLeft[i].age == "adult") {
                    objetosLeft[i].color = datos[i].color;
                    objetosLeft[i].size = datos[i].size;
                    objetosLeft[i].act = datos[i].act;
                    objetosLeft[i].age = datos[i].age;
                } else {
                    objetosLeft[i].color = NULL;
                    objetosLeft[i].size = NULL;
                    objetosLeft[i].act = NULL;
                    objetosLeft[i].age = NULL;
                }

                if (objetosRight[i].age == "child") {
                    objetosRight[i].color = datos[i].color;
                    objetosRight[i].size = datos[i].size;
                    objetosRight[i].act = datos[i].act;
                    objetosRight[i].age = datos[i].age;
                } else {
                    objetosRight[i].color = NULL;
                    objetosRight[i].size = NULL;
                    objetosRight[i].act = NULL;
                    objetosRight[i].age = NULL;
                }
                break;
            default:
                break;
        }

    }
}

int main() {
    ptrNodoArbol ptrRaiz = NULL; /* árbol inicialemnte vacío */
    double count[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};

    Node nodes[4];
    int pos = 0;

    char *values[4][2] = {{"yellow",  "purple"}, {"small",   "large"}, {"stretch", "dip"}, {"adult",   "child"}};

    char *datos[20][4] = {{"yellow", "small", "stretch", "adult"},
                          {"yellow", "small", "stretch", "adult"},
                          {"yellow", "large", "stretch", "adult"},
                          {"yellow", "large", "stretch", "adult"},
                          {"purple", "small", "stretch", "adult"},
                          {"purple", "small", "stretch", "adult"},
                          {"purple", "large", "stretch", "adult"},
                          {"purple", "large", "stretch", "adult"},
                          {"yellow", "small", "stretch", "child"},
                          {"yellow", "small", "dip",     "adult"},
                          {"yellow", "small", "dip",     "child"},
                          {"yellow", "large", "stretch", "child"},
                          {"yellow", "large", "dip",     "adult"},
                          {"yellow", "large", "dip",     "child"},
                          {"purple", "small", "stretch", "child"},
                          {"purple", "small", "dip",     "adult"},
                          {"purple", "small", "dip",     "child"},
                          {"purple", "large", "stretch", "child"},
                          {"purple", "large", "dip",     "adult"},
                          {"purple", "large", "dip",     "child"}};


    /*char ***elementos = calloc(ROWS, sizeof(char **));
    for (int i = 0; i < ROWS; ++i) {
        elementos[i] = calloc(COLS, sizeof(char *));
        for (int j = 0; j < COLS; ++j) {
            elementos[i][j] = datos[i][j];
        }
    }*/

    Objeto *objetos = calloc(ROWS,sizeof(Objeto));
    Objeto *objetosLeft = calloc(ROWS,sizeof(Objeto));
    Objeto *objetosRight = calloc(ROWS,sizeof(Objeto));

    for (int i = 0; i < ROWS; ++i) {
        //objetos[i] = malloc(sizeof(Objeto));
        objetos[i].color = datos[i][0];
        objetos[i].size = datos[i][1];
        objetos[i].act = datos[i][2];
        objetos[i].age = datos[i][3];

        objetosLeft[i].color = datos[i][0];
        objetosLeft[i].size = datos[i][1];
        objetosLeft[i].act = datos[i][2];
        objetosLeft[i].age = datos[i][3];

        objetosRight[i].color = datos[i][0];
        objetosRight[i].size = datos[i][1];
        objetosRight[i].act = datos[i][2];
        objetosRight[i].age = datos[i][3];
    }



    /*for (int i = 0; i < ROWS; i++) {
        if (elementos[i][0] == "yellow") count[0][0] += 1;
        else count[0][1] += 1;

        if (elementos[i][1] == "small") count[1][0] += 1;
        else count[1][1] += 1;

        if (elementos[i][2] == "stretch") count[2][0] += 1;
        else count[2][1] += 1;

        if (elementos[i][3] == "adult") count[3][0] += 1;
        else count[3][1] += 1;
    }*/

    for (int i = 0; i < ROWS; i++) {
        if (objetos[i].color  == "yellow") count[0][0] += 1;
        else count[0][1] += 1;

        if (objetos[i].size == "small") count[1][0] += 1;
        else count[1][1] += 1;

        if (objetos[i].act == "stretch") count[2][0] += 1;
        else count[2][1] += 1;

        if (objetos[i].age == "adult") count[3][0] += 1;
        else count[3][1] += 1;
    }

    double I = -1.0 / 2 * log2(1.0 / 2) - 1.0 / 2 * log2(1.0 / 2);

    //a partir de aqui debe de loopear
    Entropia *entropias = calloc(4, sizeof(Entropia));

    //entropia para color
    /*double color_entropy = calcularEntropiaRelativa(count[0], I);
    //double min = calcularEntropiaRelativaMinima(color_entropy, color_entropy, Color);
     //printf("\n%f ",min);
    //node = Color;*/
    entropias[0].value =  calcularEntropiaRelativa(count[0], I);
    entropias[0].node = Color;


    //entropia para size
    /*double size_entropy = calcularEntropiaRelativa(count[1], I);
    // min = calcularEntropiaRelativaMinima(min, size_entropy, Size);
    //printf("\n%f ",min);*/
    entropias[1].value = calcularEntropiaRelativa(count[1], I);
    entropias[1].node = Size;

    //entropia para act
    /*double act_entropy = calcularEntropiaRelativa(count[2], I);
    //min = calcularEntropiaRelativaMinima(min, act_entropy, Act);
    //printf("\n%f ",min);*/
    entropias[2].value = calcularEntropiaRelativa(count[2], I);
    entropias[2].node = Act;

    //entropia para age
    /*double age_entropy = calcularEntropiaRelativa(count[3], I);
    //min = calcularEntropiaRelativaMinima(color_entropy, size_entropy, act_entropy, age_entropy);*/
    entropias[3].value = calcularEntropiaRelativa(count[3], I);
    entropias[3].node = Age;

    //nodo raiz
    insertaNodo(&ptrRaiz, objetos, NULL, -1,0, NULL, Color);
    //printf("\n%f ",min);

    //double ent[4] = {color_entropy,  act_entropy, age_entropy, size_entropy};
    int l = 0;
    //Node nodeAntiguo = 1;
    double min;

    while (l < 3) {

        min = calcularMinimo(entropias);
        printf("NODO %i\n", node);

        if (nodeInArray(node, nodes, 4) == 0) {
            nodes[pos] = node;
        }

        pos++;

        for (int k = 0; k < 4; ++k) {
            if (entropias[k].node == node)
                entropias[k].value = -1;
        }

        if (pos == 4)
            break;

        if(pos == 1 ) {
            editarArray(objetosLeft, objetosRight, objetos, node);

            insertaNodo(&ptrRaiz, objetosLeft, NULL, 0, 0, NULL , node);
            //insertaNodo(&ptrRaiz, objetosRight, NULL, 1, 0);

        } else if (pos > 1){

            verificarHijo(&ptrRaiz, objetosLeft, node, values[node][0], 0);
            ///editarArray(objetosLeft, objetosRight, objetos, node);
            //editarArray(objetosLeft, objetos, node);
            //verificarHijo(&ptrRaiz, objetosRight, node, values[node][1], 1, "right", 0);
        }




        /*for (int j = 0; j < ROWS; ++j) {
            if(objetosLeft[j].color != NULL)
                printf("Left is %s, %s, %s, %s\n", objetosLeft[j].color, objetosLeft[j].size, objetosLeft[j].act, objetosLeft[j].age);
        }
        printf("\n");*/




        /*for (int i = 0; i < ROWS; ++i) {
            if(objetosLeft[i].color != NULL)
                printf("Left is %s, %s, %s, %s\n", objetosLeft[i].color, objetosLeft[i].size, objetosLeft[i].act, objetosLeft[i].age);
        }
        printf("\n");
        for (int i = 0; i < ROWS; ++i) {
            if(objetosRight[i].color != NULL)
                printf("Right is %s, %s, %s, %s\n", objetosRight[i].color, objetosRight[i].size, objetosRight[i].act, objetosRight[i].age);
        }
        printf("\n\n");*/
        /*double *entropias = calloc(4 - pos, sizeof(double));
        for (int i = 0; i < 4 - pos; ++i) {
            entropias[i] = ent[i];
        }*/
        /*entropias = realloc(entropias, 4 - pos);
        for (int i = 0, j = 0; i < 4 - pos; ++i, j++) {

            if(i == node ) {
                //i--;
                printf("%i\n", node);
            }
            else
                entropias[i] = ent[j];
        }*/
        /*for (int i = 0, j = 0; i < 4; ++i, j++) {
    printf("%f\n", entropias[i].value);
}*/

        node = Color;
        //printf("%i\n\n", pos);
        l++;
    }

    //}

    /* recorre el árbol en in inorden */
    printf("El recorrido inorden es:\n");
    //inOrden(ptrRaiz);

    return 0;
}



//entropia para color
/*double min =  (-count[0][0]/20 * log2(count[0][0]/20) -count[0][1]/20 * log2(count[0][1]/20))/I;
Node node = Color;

size_entropy = (-count[1][0]/20 * log2(count[1][0]/20) -count[1][1]/20 * log2(count[1][1]/20))/I;
 * if (min > size_entropy){
    min = size_entropy;
    node = Size;
}
printf("%f\n",size_entropy);

//entropia para act
//double act_entropy = (-count[2][0]/20 * log2(count[2][0]/20) -count[2][1]/20 * log2(count[2][1]/20))/I;

/*if (min > act_entropy){
    min = act_entropy;
    node = Act;
}

//entropia para age
double age_entropy = (-count[3][0]/20 * log2(count[3][0]/20) -count[3][1]/20 * log2(count[3][1]/20))/I;
if (min > age_entropy){
    min = age_entropy;
    node = Age;
}
//printf("%f\n",age_entropy);*/