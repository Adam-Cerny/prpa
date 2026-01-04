#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>

int* naplnPole(int* array, int* size)
{
    int velikosPole = 10;
    while (1)
    {
        int cislo;
        int ret;
        ret = scanf("%d", &cislo);
        if (ret != 1)
        {
            break;
        }
        //int novaVelikost = *size + 1;
        // vytvoreni noveho pole s velikosti +1
        if (velikosPole == *size)
        {
            velikosPole = velikosPole + 10;
            array = realloc(array, sizeof(int) * velikosPole);
        }
        // ulozeni hodnoty cislo na index ktery odpovida velikosti
        array[*size] = cislo;
        // zmena poctu polozek
        *size = *size + 1;
    }
    return array;
}

void vypisPole(int* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

float prumer(int* array, int size)
{
    if (size == 0)
    {
        return 0.0f;
    }
    int soucet = 0;
    for (int i = 0; i < size; i++)
    {
        soucet += array[i];
    }
    return (float)soucet / size;
}

float std(int* array, int size)
{
    if (size == 0)
    {
        return 0.0f;
    }
    float prumerHodnot = prumer(array, size);
    float soucet = 0.0f;
    for (int i = 0; i < size; i++)
    {
        float diff = array[i] - prumerHodnot;
        soucet += diff * diff;
    }
    return sqrtf(soucet / size);
}

int main(void)
{
    int *array = malloc(0);
    int size = 0;
    array = naplnPole(array, &size);
    vypisPole(array, size);
    printf("Prumer: %.2f\n", prumer(array, size)); 
    printf("Směrodatná odchylka: %.2f\n", std(array, size));
    free(array);
    array = NULL;

    return 0;
}
