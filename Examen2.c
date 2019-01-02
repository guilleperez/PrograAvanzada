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

    
int main(){
    
    
    //printf("%i\n",testFindCentroid());
  
    return 0;
}
