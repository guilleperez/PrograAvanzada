#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 0.000001
#define EMPTY_ARRAY -1
#define DIFFERENT_LENGTHS -2
#define DIFFERENT_TYPES -3

enum fType
{
    numerical,
    nominal
};

typedef enum fType FeatureType;

struct instance
{
    double *features;
    FeatureType *featureTypes;
    int length;
};

typedef struct instance Instance;

int dequal(double a, double b)
{
    if (fabs(a - b) < EPSILON)
    {
        return 1;
    }
    return 0;
}

int verifyInstances(Instance *instances, int count)
{
    if(count == 0){
        return EMPTY_ARRAY;
    }
    if(!instances){
        return EMPTY_ARRAY;
    }
    int featureCount = instances[0].length;
    FeatureType featureType;

    for(int i = 0; i < count; i++){
        if(instances[i].length != featureCount){
            return DIFFERENT_LENGTHS;
        }
        for(int j = 0; j < featureCount; j++){
            if(instances[0].featureTypes[j] != instances[i].featureTypes[j]){
                return DIFFERENT_TYPES;
            }
        }
    }
    return 1;
}

void initInstance(Instance *instance, int featureCount)
{
    instance->length = featureCount;
    instance->features = calloc(featureCount, sizeof(double));
    instance->featureTypes = calloc(featureCount, sizeof(FeatureType));
}

Instance *createInstance(int featureCount)
{
    Instance *result = malloc(sizeof(Instance));
    initInstance(result, featureCount);
    return result;
}

Instance *createInstanceArray(int instanceCount, int featureCount)
{
    Instance *instances = malloc(instanceCount * sizeof(Instance));
    for (int i = 0; i < instanceCount; i++)
    {
        initInstance(instances + i, featureCount);
    }
    return instances;
}

void freeInstanceItems(Instance *instance)
{
    free(instance->features);
    free(instance->featureTypes);
}

void freeInstance(Instance *instance)
{
    freeInstanceItems(instance);
    free(instance);
}

void freeInstanceArray(Instance *instances, int instanceCount)
{
    for (int i = 0; i < instanceCount; i++)
    {
        freeInstanceItems(instances + i);
    }
    printf("finished \n");
    free(instances);
}

double computeEuclideanDissimilarity(const Instance *first, const Instance *second)
{
    double sum = 0;
    for (int i = 0; i < first->length; i++)
    {
        if (first->featureTypes[i] == nominal && second->featureTypes[i] == nominal)
        {
            sum += first->features[i] == second->features[i] ? 1 : 0;
        }
        if (first->featureTypes[i] == numerical && second->featureTypes[i] == numerical)
        {
            sum += pow(first->features[i] - second->features[i], 2);
        }
    }
    return sqrt(sum);
}

Instance *findNearestNeighbor(const Instance *instances, int length, const Instance *query, double (*computeDissimilarity)(const Instance *first, const Instance *second))
{
    Instance *result;
    double min = DBL_MAX, current;
    for (int i = 0; i < length; i++)
    {
        current = computeDissimilarity(&instances[i], query);
        if (current < min)
        {
            result = (Instance *)&instances[i];
            min = current;
        }
    }
    return result;
}

double computeMode(const Instance *instances, int instanceCount, int currentFeature)
{
    double maxValue = 0, currentValue;
    int maxCount = 0, currentCount;

    for (int i = 0; i < instanceCount; i++)
    {

        currentCount = 1;
        currentValue = instances[i].features[currentFeature];
        for (int j = i + 1; j < instanceCount; j++)
        {
            if (dequal(instances[i].features[currentFeature], instances[j].features[currentFeature]))
            {
                currentCount++;
            }
        }
        if (currentCount > maxCount)
        {
            maxValue = currentValue;
            maxCount = currentCount;
        }
    }
    return maxValue;
}

double computeMean(const Instance *instances, int instanceCount, int currentFeature)
{
    double result = 0;
    FeatureType featureType = instances[0].featureTypes[currentFeature];
    for (int i = 0; i < instanceCount; i++)
    {
        result += instances[i].features[currentFeature];
        if (featureType != instances[i].featureTypes[currentFeature])
        {
            return DIFFERENT_TYPES;
        }
    }
    result /= instanceCount;
    return result;
}

Instance *averageDataset(const Instance *instances, int instanceCount)
{
    
    Instance *average = createInstance(instances[0].length);
    for (int i = 0; i < instances[0].length; i++)
    {
        double result;
        switch (instances[0].featureTypes[i])
        {
        case nominal:
            result = computeMode(instances, instanceCount, i);
            average->featureTypes[i] = nominal;
            break;
        case numerical:
            result = computeMean(instances, instanceCount, i);
            average->featureTypes[i] = numerical;
            break;
        }
        average->features[i] = result;
    }
    return average;
}

int testNearestNeighbor()
{
    int count;
    scanf("%d", &count);

    Instance *instances = createInstanceArray(count, 2);
    Instance *query, *result;
    double x, y;
    for (int i = 0; i < count; i++)
    {
        scanf("%lf %lf", &x, &y);
        instances[i].features[0] = x;
        instances[i].features[1] = y;
        instances[i].featureTypes[0] = numerical;
        instances[i].featureTypes[1] = numerical;
    }
    query = createInstance(2);
    scanf("%lf %lf", &x, &y);
    query->features[0] = x;
    query->features[1] = y;
    query->featureTypes[0] = numerical;
    query->featureTypes[1] = numerical;

    result = findNearestNeighbor(instances, count, query, computeEuclideanDissimilarity);

    printf("nearest = %.5f, %.5f\n", result->features[0], result->features[1]);

    freeInstanceArray(instances, count);
    freeInstance(query);
    return 0;
}

int testAverageDataset()
{
    int count;
    scanf("%d", &count);

    Instance *instances = createInstanceArray(count, 3);
    Instance *result;
    double x, y, z;
    for (int i = 0; i < count; i++)
    {
        scanf("%lf %lf %lf", &x, &y, &z);
        instances[i].features[0] = x;
        instances[i].features[1] = y;
        instances[i].features[2] = z;
        instances[i].featureTypes[0] = numerical;
        instances[i].featureTypes[1] = nominal;
        instances[i].featureTypes[2] = numerical;
    }

    result = averageDataset(instances, count);

    printf("average = %.5f, %.5f, %.5f\n", result->features[0], result->features[1], result->features[2]);
    printf("featureTypes = %s %s %s\n", result->featureTypes[0] == numerical ? "numerical" : "nominal", result->featureTypes[1] == numerical ? "numerical" : "nominal", result->featureTypes[2] == numerical ? "numerical" : "nominal");
    printf("length = %d\n", result->length);
    freeInstanceArray(instances, count);
    freeInstance(result);
    return 0;
}

int testAverageDatasetEmpty()
{
    Instance *instances;
    Instance *result;
    result = averageDataset(instances, 10);
    if ((long long)result == EMPTY_ARRAY)
    {
        return 1;
    }
    return 0;
}

int main()
{
    printf("--- Testing Average Dataset ---\n");
    if (testAverageDatasetEmpty())
    {
        printf("Empty Array passed.\n");
    }
    else
    {
        printf("Empty Array did not pass.\n");
    }

    return 0;
}