#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef enum MinutiaType{
    Ending = 0,
    Bifurcation = 1,
    Unknown = 2
}MinutiaType;

typedef struct Minutia{
    unsigned short x; //unsigned int 16 bits = unsigned short
    unsigned short y;
    float angle; //floating-point number of 32 bits.
    MinutiaType type;
}Minutia;

typedef struct MinutiaArray{
   Minutia * minutiae;
   unsigned short int length; //# of elements in array; unsigned integer of 16 bits.
}MinutiaArray;

//Protoypes
Minutia * createMinutia(unsigned short x, unsigned short y, float angle, MinutiaType memberType);
MinutiaArray * createMinutiaArray(unsigned short int length);
void releaseMinutiaArray(MinutiaArray *  minutiaArray);
Minutia * findCentroid(const MinutiaArray * minutiaArray, double (*computeDistance)
 (const Minutia * minutiaeA, const  Minutia * minutiaeB));
int testFindCentroid();

void initMinutia(Minutia * minutia, unsigned short x, unsigned short y, float angle, MinutiaType memberType){
    minutia -> x = x;
    minutia -> y = y;
    minutia -> angle = angle;
    minutia -> type = memberType;
    return;
}
Minutia * createMinutia(unsigned short x, unsigned short y, float angle, MinutiaType memberType){
    Minutia * minutia = (Minutia*) malloc(sizeof(Minutia));
    initMinutia(minutia, x, y, angle, memberType);
    return minutia;
}

MinutiaArray * createMinutiaArray(unsigned short int length){
    MinutiaArray * minutiaArray = (MinutiaArray*) malloc(sizeof(MinutiaArray));
    minutiaArray -> length = length; 
    minutiaArray -> minutiae = (Minutia*) calloc(length, sizeof(Minutia));
    

    for (int i = 0; i < length; i++) {
        createMinutia(0,0,0,Unknown);
    }
    
    return minutiaArray;
}


void releaseMinutiaArray(MinutiaArray *  minutiaArray){
    unsigned int length = minutiaArray -> length;
   free(minutiaArray -> minutiae);
    free(minutiaArray);
    //free(minutiaArray);
    return;
}

double computeDistance (const  Minutia * minutiaeA, const  Minutia * minutiaeB){
  double sum_x= 0;
  double sum_y= 0;
  //printf("%i %i", minutiaeA -> x, minutiaeB ->x);
   if (minutiaeA -> type != minutiaeB -> type)
       return -3;

    else if (minutiaeA -> type == Ending){
    	   sum_x += pow ((float) minutiaeA -> x  - (float) minutiaeB -> x, 2);
    	   sum_y += pow ((float) minutiaeA -> y  - (float) minutiaeB -> y, 2);
    	   
    }else if (minutiaeA -> type == Bifurcation){
	       if (minutiaeA -> x  != minutiaeB -> x && minutiaeA -> y  != minutiaeB -> y){
	            sum_x += 1;
	            sum_y += 1;
	       }
	    }
    

  return (sum_x + sum_y);
}


Minutia * findCentroid(const MinutiaArray * minutiaArray, 
    double (*computeDistance)(const Minutia * minutiaeA, const Minutia * minutiaeB)){
    
    Minutia * current;
    double total_distance;
    int index = 0;
    double lower_distance = DBL_MAX;
    unsigned int length = minutiaArray -> length;
    for (int i = 0; i < length; i++) {
        total_distance = 0;
        current = &(minutiaArray -> minutiae[i]);
        
        for (int j = 0; j < length; j++) {
             total_distance += computeDistance(current,&(minutiaArray -> minutiae[j]));
         }
         if(total_distance < lower_distance)
            index = i;
    }
    
    return minutiaArray[index].minutiae;
}

int testFindCentroid(){
    
    unsigned short int length = 10;
    MinutiaArray  * minutiaArray = createMinutiaArray(length);

    unsigned short x[10] = {3, 2, 4, 5, 6, 1, 6, 2, 7, 9}; //unsigned int 16 bits = unsigned short
    unsigned short y[10] = {4, 2, 5, 1, 3, 1, 3, 2, 7, 4};
    float angle[10] = {3, 2, 4, 5, 6, 1, 6, 2, 7, 9}; //floating-point number of 32 bits.
    MinutiaType type[10] = {Ending, Bifurcation, Unknown, Ending, Bifurcation, Unknown, Ending, Bifurcation, Unknown, Ending};
    
    Minutia * min;
    for (int i = 0; i < length; i++) {
        min = &(minutiaArray -> minutiae[i]);
        
        initMinutia(min, x[i], y[i], angle[i], type[i]);
    }
    
    Minutia * minutia = findCentroid(minutiaArray, computeDistance);
    int answer = 0;
    //printf("%p", minutia);
    if((int) minutia > 0)
        answer = 1;
    
    releaseMinutiaArray(minutiaArray);
    
    return answer;
     
     
} 
 
    
int main(){
    
    
    printf("%i\n",testFindCentroid());
  
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef enum MinutiaType{
    Ending = 0,
    Bifurcation = 1,
    Unknown = 2
}MinutiaType;

typedef struct Minutia{
    unsigned short x; //unsigned int 16 bits = unsigned short
    unsigned short y;
    float angle; //floating-point number of 32 bits.
    MinutiaType type;
}Minutia;

typedef struct MinutiaArray{
   Minutia * minutiae;
   unsigned short int length; //# of elements in array; unsigned integer of 16 bits.
}MinutiaArray;

//Protoypes
Minutia * createMinutia(unsigned short x, unsigned short y, float angle, MinutiaType memberType);
MinutiaArray * createMinutiaArray(unsigned short int length);
void releaseMinutiaArray(MinutiaArray *  minutiaArray);
Minutia * findCentroid(const MinutiaArray * minutiaArray, double (*computeDistance)
 (const Minutia * minutiaeA, const  Minutia * minutiaeB));
int testFindCentroid();

void initMinutia(Minutia * minutia, unsigned short x, unsigned short y, float angle, MinutiaType memberType){
    minutia -> x = x;
    minutia -> y = y;
    minutia -> angle = angle;
    minutia -> type = memberType;
    return;
}
Minutia * createMinutia(unsigned short x, unsigned short y, float angle, MinutiaType memberType){
    Minutia * minutia = (Minutia*) malloc(sizeof(Minutia));
    initMinutia(minutia, x, y, angle, memberType);
    return minutia;
}

MinutiaArray * createMinutiaArray(unsigned short int length){
    MinutiaArray * minutiaArray = (MinutiaArray*) malloc(sizeof(MinutiaArray));
    minutiaArray -> length = length; 
    minutiaArray -> minutiae = (Minutia*) calloc(length, sizeof(Minutia));
    

    for (int i = 0; i < length; i++) {
        createMinutia(0,0,0,Unknown);
    }
    
    return minutiaArray;
}


void releaseMinutiaArray(MinutiaArray *  minutiaArray){
    unsigned int length = minutiaArray -> length;
   
    free(minutiaArray);
    //free(minutiaArray);
    return;
}

double computeDistance (const  Minutia * minutiaeA, const  Minutia * minutiaeB){
  double sum_x= 0;
  double sum_y= 0;
  //printf("%i %i", minutiaeA -> x, minutiaeB ->x);
   if (minutiaeA -> type != minutiaeB -> type)
       return -3;

    else if (minutiaeA -> type == Ending){
    	   sum_x += pow ((float) minutiaeA -> x  - (float) minutiaeB -> x, 2);
    	   sum_y += pow ((float) minutiaeA -> y  - (float) minutiaeB -> y, 2);
    	   
    }else if (minutiaeA -> type == Bifurcation){
	       if (minutiaeA -> x  != minutiaeB -> x && minutiaeA -> y  != minutiaeB -> y){
	            sum_x += 1;
	            sum_y += 1;
	       }
	    }
    

  return (sum_x + sum_y);
}


Minutia * findCentroid(const MinutiaArray * minutiaArray, 
    double (*computeDistance)(const Minutia * minutiaeA, const Minutia * minutiaeB)){
    
    Minutia * current;
    double total_distance;
    int index = 0;
    double lower_distance = DBL_MAX;
    unsigned int length = minutiaArray -> length;
    for (int i = 0; i < length; i++) {
        total_distance = 0;
        current = &(minutiaArray -> minutiae[i]);
        
        for (int j = 0; j < length; j++) {
             total_distance += computeDistance(current,&(minutiaArray -> minutiae[j]));
         }
         if(total_distance < lower_distance)
            index = i;
    }
    
    return minutiaArray[index].minutiae;
}

int testFindCentroid(){
    
    unsigned short int length = 10;
    MinutiaArray  * minutiaArray = createMinutiaArray(length);

    unsigned short x[10] = {3, 2, 4, 5, 6, 1, 6, 2, 7, 9}; //unsigned int 16 bits = unsigned short
    unsigned short y[10] = {4, 2, 5, 1, 3, 1, 3, 2, 7, 4};
    float angle[10] = {3, 2, 4, 5, 6, 1, 6, 2, 7, 9}; //floating-point number of 32 bits.
    MinutiaType type[10] = {Ending, Bifurcation, Unknown, Ending, Bifurcation, Unknown, Ending, Bifurcation, Unknown, Ending};
    
    Minutia * min;
    for (int i = 0; i < length; i++) {
        min = &(minutiaArray -> minutiae[i]);
        
        initMinutia(min, x[i], y[i], angle[i], type[i]);
    }
    
    Minutia * minutia = findCentroid(minutiaArray, computeDistance);
    int answer = 0;
    //printf("%p", minutia);
    if((int) minutia > 0)
        answer = 1;
    
    releaseMinutiaArray(minutiaArray);
    
    return answer;
     
     
} 
 
    
int main(){
    
    
    printf("%i\n",testFindCentroid());
  
    return 0;
}
