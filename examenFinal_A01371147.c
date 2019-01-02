/*
Sergio Erick Chávez Flores
A0137147
Examen Final Programación Avanzada
*/
#include <stdio.h>
#include <stdlib.h>
#define OPT_SUCCESS 1
#define ARG_OUT_OF_RANGE -1

typedef struct sensor{
	double *values;
	int length;
}SensorValues;

typedef struct airPressure{
	SensorValues* ps; 
	SensorValues* pfv; 
	SensorValues* pfll; 	
}AirPressureSensorsValues;

AirPressureSensorsValues* createAirPressureSensorsValues(const short int lenPS, const short int lenPFV, const short int lenPFLL, int *output){
	if(lenPS<=0 || lenPFV<= 0 || lenPFLL<=0){
		*output = ARG_OUT_OF_RANGE;
		return NULL; 
	}
	else{
		*output = OPT_SUCCESS; 
	}

	AirPressureSensorsValues * nuevoSensor = malloc(sizeof(AirPressureSensorsValues));

	nuevoSensor->ps = malloc(sizeof(SensorValues)); 
	nuevoSensor->ps->values = malloc(lenPS*sizeof(SensorValues));
	nuevoSensor->ps->length = lenPS; 

	nuevoSensor->pfv = malloc(sizeof(SensorValues)); 
	nuevoSensor->pfv->values = malloc(lenPFV*sizeof(SensorValues)); 
	nuevoSensor->pfv->length = lenPFV; 

	nuevoSensor->pfll = malloc(sizeof(SensorValues)); 
	nuevoSensor->pfll->values = malloc(lenPFLL*sizeof(SensorValues));
	nuevoSensor->pfll->length = lenPFLL; 

	return nuevoSensor; 
}

int createAirPressureSensorsValues_Prueba_1(){
	int resultado; 
	if(createAirPressureSensorsValues(0,1,1, &resultado)==NULL && resultado==ARG_OUT_OF_RANGE){
		return 1; 
	}
	else{
		return 0; 
	}
}

int createAirPressureSensorsValues_Prueba_2(){ 
	int resultado; 
	if(createAirPressureSensorsValues(1,0,1, &resultado)==NULL && resultado==ARG_OUT_OF_RANGE){
		return 1; 
	}
	else{
		return 0; 
	}
}

int createAirPressureSensorsValues_Prueba_3(){
	int resultado;
	if(createAirPressureSensorsValues(1,1,0, &resultado)==NULL && resultado==ARG_OUT_OF_RANGE){
		return 1;
	}
	else{
		return 0; 
	}
}

int createAirPressureSensorsValues_Prueba_4(){
	int resultado; 
	AirPressureSensorsValues* resultado2 = createAirPressureSensorsValues(1,1,1, &resultado); 
	if(resultado2->ps->length==1 && resultado2->pfv->length==1 && resultado2->pfll->length==1 && resultado==OPT_SUCCESS){
		return 1; 
	}
	else{
		return 0; 
	}

}

void freeAirPressureSensorsValues(AirPressureSensorsValues* a){
	free(a); 
}

void applyFilter(AirPressureSensorsValues *pointer1,const double *filtro, const short size){
	int mitad = 0;
	int m = size / 2.0;
	int s = size;

	int resultado;
	AirPressureSensorsValues *p = createAirPressureSensorsValues(pointer1->ps->length,pointer1->ps->length,
																 pointer1->ps->length, &resultado);

	p -> ps -> values = calloc(size,sizeof(SensorValues));
	p -> ps -> length = pointer1->ps->length;

	for (int i = 0; i < size ; ++i) {
		if(i < m)
			p -> ps -> values[i] = 0.0;
		else if ( m > 0){
			p -> ps -> values[i] = pointer1 -> ps -> values[i-1];
		}
	}
	s -= 2;

	AirPressureSensorsValues *rp = createAirPressureSensorsValues(pointer1->ps->length,pointer1->ps->length,
																 pointer1->ps->length, &resultado);
	rp -> ps -> values = calloc(size,sizeof(SensorValues));
	rp -> ps -> length = pointer1->ps->length;

	double res;

	//PS
	for(int i = 0; i<= pointer1->ps->length; i++){
		mitad++;
		res = 0.0;

		/*printf("------\n");
		for (int j = 0; j < size; j++){
			printf("%f\n",p ->ps -> values[j]);
		}
		printf("------\n");*/

		for (int j = 0; j < pointer1->ps->length; j++){
			//printf("%f %f\n", filtro[j], p -> ps -> values[j]);
			res += filtro[j] * p -> ps -> values[j];
		}
		rp -> ps -> values[i] = res;

		m = s / 2.0;
		for (int j = 0; j < size ; ++j) {
			if(j < m)
				p -> ps -> values[j] = 0.0;
			else if (m == 0 && s > 0)
				p -> ps -> values[j] = pointer1 -> ps -> values[j];
			else if(m == 0 && s < 0)
				p->ps->values[j] = pointer1->ps->values[j + 1];
			else if ((j + m) <= size && m > 0)
				p->ps->values[j] = pointer1->ps->values[(j + m)];
			else if ((j + (m*-1) + 1) <= size)
				p->ps->values[j] = pointer1->ps->values[(j + (m*-1) + 1)];
			else
				p->ps->values[j] = 0.0;

		}

		s -= 2;


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

	printf("------\n");
	for (int j = 0; j < p -> ps -> length; j++){
		printf("%f\n",rp ->ps -> values[j]);
	}
	printf("------\n");


	//PFV
	/*for(int i = 0; i<pointer1->pfv->length; i++){
		if (mitad<0){
			mitad=0;
		} 
		for (int j = mitad; j < size; j++){
			printf("%d %d\n", i, j);
		}
	}

	//PFLL
	for(int i = 0; i<pointer1->pfll->length; i++){
		if (mitad<0){
			mitad=0;
		} 
		for (int j = mitad; j < size; j++){
			printf("%d %d\n", i, j);
		}
	}*/
}

int test_applyFilter_1(){
	int resultado; 
	AirPressureSensorsValues* p = createAirPressureSensorsValues(4,4,4, &resultado);
	p->ps->values[0] = 1;
	p->ps->values[1] = 3;
	p->ps->values[2] = 2;
	p->ps->values[3] = 1;
	double *filtro = calloc(3, sizeof(double));
	filtro[0] = 0.3;
	filtro[1] = 0.4;
	filtro[2] = 0.3;
	applyFilter(p, filtro, 3);
	return 1 ;
	
}

int main(){
	printf("Probando createAirPressureSensorsValues...\n\n");
	printf("\t%d\n", createAirPressureSensorsValues_Prueba_1());
	printf("\t%d\n", createAirPressureSensorsValues_Prueba_2());
	printf("\t%d\n", createAirPressureSensorsValues_Prueba_3());
	printf("\t%d\n\n", createAirPressureSensorsValues_Prueba_4());

	printf("Probando applyFilter...\n");
	printf("\t%d\n", test_applyFilter_1());
	//printf("No me salió D:\n"); 
	return 0;
}