//
// Created by guille on 10/05/2018.
//

/*Fingerprint Identification Systems use fingerprint features based on minutiae descriptors.
 * One of the most efficient and accurate minutiae descriptor is Cylinder Codes (CC).
 * Some applications represent CCs at low resolution (64 bits) to perform fast operations.
 * Implement a function with variable number of parameters (variadic) that receives many CCs
 * (each CC is represented with an unsigned integer of 64 bits)
 * and returns a new CC which contains the mixture of the CCs passed as parameters.
As an example, if the function receives the following CCs:
0…01110
0…11000
0…01100
the result will be:
0…11110*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define OPT_SUCCESS  1
#define ARG_OUT_OF_RANGE  -1

typedef struct sensorValues{
    double *values;
    short length;
}SensorValues;

typedef struct airPressureSensorValues{
    SensorValues *ps;
    SensorValues *pfv;
}AirPressureSensorsValues;


//prototipos
unsigned long long int mixMinutae(int n, ...);
AirPressureSensorsValues* createAirPressureSensorsValues(const short sizePS, const short sizePFV,  int *output);
int test_createAirPressureSensorsValues();
int test_createAirPressureSensorsValues_b();
void freeSensorValues(SensorValues *sensor);
void freeAirPressureSensorsValues(AirPressureSensorsValues *sensorsValues);
void applyFilter(AirPressureSensorsValues * airPressureSensorsValues, const double * filtro, const char size);
int test_applyFilter();
//int test_applyFilter_b();


//freeAirPressureSensorsValues that receives a pointer to AirPressureSensorsValues and releases the memory to which it points to and the memory
// occupied by its members. This function returns no value.

void freeSensorValues(SensorValues *sensor){
    free(sensor -> values);
    free(sensor);
}
void freeAirPressureSensorsValues(AirPressureSensorsValues *sensorsValues){
    freeSensorValues(sensorsValues -> ps);
    freeSensorValues(sensorsValues -> pfv);
    free(sensorsValues);
}

unsigned long long int mixMinutae(int n, ...){
    va_list minutas;
    va_start(minutas, n);
    unsigned long long int mix = 0;
    for (int i = 0; i <n ; ++i)
        mix |= (unsigned long long int) va_arg(minutas, unsigned long long int);

    va_end(minutas);
    return mix;
}

AirPressureSensorsValues* createAirPressureSensorsValues(const short sizePS, const short sizePFV,  int *output){
    //ARG_OUT_OF_RANGE if any of the first two parameters of the function contains a value lower or equal than 0;
    if(sizePS<=0 || sizePS<= 0){
        *output = ARG_OUT_OF_RANGE;
        return NULL;
    } else {
        //otherwise, output will contain the value OPT_SUCCESS
        *output = OPT_SUCCESS;

        AirPressureSensorsValues *sensorsValues = malloc(sizeof(AirPressureSensorsValues));

        sensorsValues->ps = malloc(sizeof(SensorValues));
        sensorsValues->ps->values = calloc(sizePS, sizeof(SensorValues));
        sensorsValues->ps->length = sizePS;

        sensorsValues->pfv = malloc(sizeof(SensorValues));
        sensorsValues->pfv->values = calloc(sizePFV, sizeof(SensorValues));
        sensorsValues->pfv->length = sizePFV;

        return sensorsValues;
    }
}

//test function with no parameters that returns 1 if the function createAirPressureSensorsValues returns NULL,
// while the parameter output is outputted with value ARG_OUT_OF_RANGE when the parameter indicating the length of ps has a value lower or equal than zero
//(otherwise, the test function returns 0). Notice that the parameter indicating the length of pfv must have a value greater than 0.

int test_createAirPressureSensorsValues(){
    int output;
    if(createAirPressureSensorsValues(0, 1,  &output) == NULL && output == ARG_OUT_OF_RANGE){
        return 1;
    } else{
        return 0;
    }


}

//test function with no parameters that returns 1 if the function createAirPressureSensorsValues returns a pointer to a AirPressureSensorsValues which memory
// was dynamically reserved with values greater than 0 and different to NULL, while the parameter output is returned with value OPT_SUCCESS;
// otherwise, the function returns 0. In order to return 1, the function must also verify correctly that the members length of ps and pfv
// have the same values that you specified as parameters when calling the function createAirPressureSensorsValues inside the test function.

int test_createAirPressureSensorsValues_b(){
    int output;
    AirPressureSensorsValues *a = createAirPressureSensorsValues(1, 1,  &output);
//    /&& &output == OPT_SUCCESS
    if(&a != NULL && output == OPT_SUCCESS){
        freeAirPressureSensorsValues(a);
        return 1;
    }else{
        return 0;
    }

}

//applyFilter that receives the parameters:
// a) a pointer to a struct AirPressureSensorsValues;
// b) a constant array to double;
// c) a constant integer of 8 bits that indicates the length of the array (b).
// This function returns nothing.
// The function applies the array of double as a filter over the respective arrays stored in the members ps and pfv
// of AirPressureSensorsValues. This kind of functions are common in signal processing to mitigate the noise in the signals

void applyFilter(AirPressureSensorsValues * airPressureSensorsValues, const double * filtro, const char size) {

    int relativeMitad = size / 2.0;

    int output;
    //relativeFiltro sirve para ir moviendo el filtro de acuerdo a la posicion de relativeMitad
    AirPressureSensorsValues *relativeFiltro = createAirPressureSensorsValues(airPressureSensorsValues->ps->length,
                                                                              airPressureSensorsValues->pfv->length,
                                                                              &output);


    //agrega el primer valor de la serie
    int j = 0;
    for (int i = 0; i < size; ++i) {
        if (i < relativeMitad)
            relativeFiltro->ps->values[i] = 0.0;
        else if (relativeMitad > 0) {
            relativeFiltro->ps->values[i] = airPressureSensorsValues->ps->values[j];
            j++;
        }
    }


    AirPressureSensorsValues *respuesta = createAirPressureSensorsValues(airPressureSensorsValues->ps->length,
                                                                         airPressureSensorsValues->pfv->length, &output);


    double res, respfv;
    int k;

    //PS
    for (int i = 0; i <= airPressureSensorsValues->ps->length; i++) {
        relativeMitad--;
        res = 0.0;

        //printf("------\n");
        /*for (int j = 0; j < size; j++){
            printf("%f\n", relativeFiltro ->ps -> values[j]);
        }*/

        for (int j = 0; j < airPressureSensorsValues->ps->length; j++) {
          //  printf("%f %f\n", filtro[j], relativeFiltro -> ps -> values[j]);
            res += filtro[j] * relativeFiltro->ps->values[j];
        }
        respuesta->ps->values[i] = res;
        //printf("\n%f\n------\n", respuesta -> ps -> values[i]);

        if (relativeMitad >= 0)
            k = 0;
        else {
            k = 0;
            k += (relativeMitad * -1);
        }
        for (int j = 0; j < size; ++j) {
            if (j < relativeMitad)
                relativeFiltro->ps->values[j] = 0.0;
            else if (j + relativeMitad > airPressureSensorsValues->ps->length)
                relativeFiltro->ps->values[j] = 0.0;
            else {
                relativeFiltro->ps->values[j] = airPressureSensorsValues->ps->values[k];
                k++;
            }

        }


        /*if(mitad == 1){
            p -> ps -> values[0] = pointer1 -> ps -> values[0];
            p -> ps -> values[1] = pointer1 -> ps -> values[1];
            p -> ps -> values[2] = pointer1 -> ps -> values[2];
        }else if(mitad == 2){
            p -> ps -> values[0] = pointer1 -> ps -> values[1];
            p -> ps -> values[1] = pointer1 -> ps -> values[2];
            p -> ps -> values[2] = pointer1 -> ps -> values[3];
        }else if(mitad == 3){
            p -> ps -> values[0] = pointer1 -> ps -> values[2];
            p -> ps -> values[1] = pointer1 -> ps -> values[3];
            p -> ps -> values[2] = 0;
        }*/
    }

    //pfv
    relativeMitad = size / 2.0;

    //agrega el primer valor de la serie
    j = 0;
    for (int i = 0; i < size; ++i) {
        if (i < relativeMitad)
            relativeFiltro->pfv->values[i] = 0.0;
        else if (relativeMitad > 0) {
            relativeFiltro->pfv->values[i] = airPressureSensorsValues->pfv->values[j];
            j++;
        }
    }

    for (int i = 0; i <= airPressureSensorsValues->pfv->length; i++) {
        relativeMitad--;
        res = 0.0;

        /*printf("------\n");
        for (int j = 0; j < size; j++){
            printf("%f\n", relativeFiltro ->pfv -> values[j]);
        }*/

        for (int j = 0; j < airPressureSensorsValues->pfv->length; j++) {
            //printf("%f %f\n", filtro[j], p -> ps -> values[j]);
            res += filtro[j] * relativeFiltro->pfv->values[j];
        }
        respuesta->pfv->values[i] = res;
        //printf("\n%f\n------\n", respuesta -> ps -> values[i]);

        if (relativeMitad >= 0)
            k = 0;
        else {
            k = 0;
            k += (relativeMitad * -1);
        }
        for (int j = 0; j < size; ++j) {
            if (j < relativeMitad)
                relativeFiltro->pfv->values[j] = 0.0;
            else if (j + relativeMitad > airPressureSensorsValues->pfv->length)
                relativeFiltro->pfv->values[j] = 0.0;
            else {
                relativeFiltro->pfv->values[j] = airPressureSensorsValues->pfv->values[k];
                k++;
            }

        }
    }

    //ps
    //printf("------\n");
    for (int j = 0; j < relativeFiltro->ps->length; j++) {
        //printf("%f\n",respuesta ->ps -> values[j]);
        airPressureSensorsValues->ps->values[j] = respuesta->ps->values[j];
    }

        //pfv
        for (int j = 0; j < relativeFiltro->pfv->length; j++) {
            //printf("%f\n",respuesta ->ps -> values[j]);
            airPressureSensorsValues->pfv->values[j] = respuesta->pfv->values[j];
        }
        //printf("------\n");
    freeAirPressureSensorsValues(respuesta);
    freeAirPressureSensorsValues(relativeFiltro);
        return;



}

int test_applyFilter(){
    int resultado;
    AirPressureSensorsValues* airPressureSensorsValues = createAirPressureSensorsValues(3,4, &resultado);
    airPressureSensorsValues -> ps-> values[0] = 1;
    airPressureSensorsValues -> ps->values[1] = 3;
    airPressureSensorsValues -> ps->values[2] = 2;

    airPressureSensorsValues -> pfv-> values[0] = 1;
    airPressureSensorsValues -> pfv->values[1] = 3;
    airPressureSensorsValues -> pfv->values[2] = 2;
    airPressureSensorsValues -> pfv->values[3] = 1;
    double filtro[3] = {0.3, 0.4, 0.3};

    applyFilter(airPressureSensorsValues, filtro, 3);

    printf("------ ps\n");
    for (int j = 0; j < airPressureSensorsValues -> ps -> length; j++){
        printf("%f\n",airPressureSensorsValues ->ps -> values[j]);
    }

    /*if(airPressureSensorsValues ->ps -> values[0] != 1.3 ||
            airPressureSensorsValues ->ps -> values[1] != 2.1 ||
            airPressureSensorsValues ->ps -> values[2] != 1.7)*/
        //return 0;

    printf("\n");
    for (int j = 0; j < airPressureSensorsValues -> pfv -> length; j++){
        printf("%f\n",airPressureSensorsValues ->pfv -> values[j]);
    }
    printf("------ pfv\n\n");

    /*if(airPressureSensorsValues ->pfv -> values[0] != 1.3 ||
       airPressureSensorsValues ->pfv -> values[1] != 2.1 ||
       airPressureSensorsValues ->pfv -> values[2] != 2.0 ||
            airPressureSensorsValues ->pfv -> values[3] != 1.0)
        return 0;*/

    freeAirPressureSensorsValues(airPressureSensorsValues);
    return 1;

}

int test_applyFilter_b(){
    int resultado ;
    AirPressureSensorsValues* airPressureSensorsValues = createAirPressureSensorsValues(5,5, &resultado);
    airPressureSensorsValues -> ps-> values[0] = 1;
    airPressureSensorsValues -> ps->values[1] = 2;
    airPressureSensorsValues -> ps->values[2] = 3;
    airPressureSensorsValues -> ps->values[3] = 4;
    airPressureSensorsValues -> ps->values[4] = 5;

    double filtro[5] = {0.3,0.2,0.2,0.1,0.2};

    applyFilter(airPressureSensorsValues, filtro, 5);

    printf("------\n");
    for (int j = 0; j < 5; j++){
        printf("%f\n",airPressureSensorsValues ->ps -> values[j]);
    }
    printf("------\n\n");

    freeAirPressureSensorsValues(airPressureSensorsValues);
    return 1 ;

}

int main(){

    unsigned long long int minutaeA = 14;
    unsigned long long int minutaeB = 24;
    unsigned long long int minutaeC = 12;
    unsigned long long int mix = mixMinutae(3, minutaeA, minutaeB, minutaeC);
    printf("Mix \n%llu", mix);

    printf("\ntest_createAirPressureSensorsValues\n%i\n",test_createAirPressureSensorsValues() );
    printf("test_createAirPressureSensorsValues_b\n%i\n",test_createAirPressureSensorsValues_b() );

    printf("\ntest_applyFilter()\n %i",test_applyFilter());


    return 0;
}