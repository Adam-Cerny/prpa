#include <stdio.h>

void vypisMatice1(int n)
{
    for (int i = 0; i < 100; i++) {
        printf("%3d", i);        
        if ((i + 1) % 10 == 0)   
            printf("\n");
    }
}

void vypisMatice2(int n)
{
    // for (int i = 0; i < 10; i++) {         
    //     for (int j = 0; j < 10; j++) {    
    //         printf("%3d", i * 10 + j);
    //     }
    //     printf("\n");
    // }

    // for (int i = 0; i < 100; i+=10) {         
    //     for (int j = 0; j < 10; j++) {    
    //         printf("%3d", i + j);
    //     }
    //     printf("\n");
    // }

    for (int i = 0; i < 10; i++) {         
        for (int j = 0; j < 10; j++) {  
            if (i == 0)
            {
                printf("%d  ", j);
            }  
            else 
            {
                printf("%d%d ", i, j);
            }
        }
        printf("\n");
    }
}

void vypisDiagonaly1(int n)
{
    for (int i = 0; i < 10; i++) {         
        for (int j = 0; j < 10; j++) { 
            if (i == j)
            {
                printf("%3d", i * 10 + j);
            }   
            else
            {
                printf("   ");
            }   
        }
        printf("\n");
    }
}

void vypisDiagonaly2(int n)
{
    for (int i = 0; i < 10; i++) {         
        for (int j = 0; j < 10; j++) { 
            if (i + j == 9)
            {
                printf("%3d", i * 10 + j);
            }   
            else
            {
                printf("   ");
            }   
        }
        printf("\n");
    }
}

void vypisDiagonaly3(int n)
{
    for (int i = 0; i < 10; i++) {         
        for (int j = 0; j < 10; j++) { 
            if (i == j || i + j == 9)
            {
                printf("%3d", i * 10 + j);
                if (j >= 5)
                {
                    break; 
                }
            }   
            else
            {
                printf("   ");
            }   
        }
        printf("\n");
    }
}

int main(void)
{
    // vypisMatice1(100);

    // vypisMatice2(10);

    vypisDiagonaly1(100);

    vypisDiagonaly2(100);

    vypisDiagonaly3(100);

    return 0;
}
