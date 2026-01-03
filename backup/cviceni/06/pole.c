#include <stdio.h>

// void nacti(int* array, int size)
// {
//     for (int i = 0; i < size; i++)
//     {
//         array[i] = i + 1;
//     }
// }

void vypis(int* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("[%02i] = %i\n", i, array[i]);
    }
}

void serad(int* array, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int najdiNteNejvyssi(int* array, int size, int n)
{   
    int predchozi = array[0];
    for (int i = 0; i < n; i++)
    {
        if (n == 1)
        {
            return predchozi;
        }
        if (predchozi != array[i])
        {
            n--;
        }
        predchozi = array[i];
    }
    return -999;
}

int main(void)
{
    int size = 10;
    int array[10] = {5, 3, 8, 6, 2, 7, 4, 10, 1, 9};

    // nacti(array, size);
    vypis(array, size);

    serad(array, size);
    printf("Po serazeni:\n");
    vypis(array, size);

    int nejvyssi = najdiNteNejvyssi(array, size, 2);
    printf("2. nejvyssi hodnota je: %i\n", nejvyssi);
    
    return 0;
}