#include <stdio.h>

// (a) čtverec
void square(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("*");
        }
        printf("\n");
    }
}

// (b) levý rostoucí trojúhelník
void left_increasing_triangle(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

// (c) pravý rostoucí trojúhelník
void right_increasing_triangle(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n - i; j++) {
            printf(" ");
        }
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

// (d) pravý klesající trojúhelník
void right_decreasing_triangle(int n) {
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < n - i; j++) {
            printf(" ");
        }
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

// (e) levý klesající trojúhelník
void left_decreasing_triangle(int n) {
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

// hlavní funkce — volá všechny obrazce
void print_all(int n) {
    printf("(a)\n");
    square(n);
    printf("\n(b)\n");
    left_increasing_triangle(n);
    printf("\n(c)\n");
    right_increasing_triangle(n);
    printf("\n(d)\n");
    right_decreasing_triangle(n);
    printf("\n(e)\n");
    left_decreasing_triangle(n);
}

int main(void) {
    int n = 5;  // můžeš libovolně změnit
    print_all(n);
    return 0;
}

// #include <stdio.h>

// void print_shape(int type, int n) {
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             int print_star = 0; // výchozí — tiskneme mezeru

//             switch (type) {
//                 case 1: // (a) čtverec
//                     print_star = 1;
//                     break;

//                 case 2: // (b) levý rostoucí trojúhelník
//                     if (j <= i) print_star = 1;
//                     break;

//                 case 3: // (c) pravý rostoucí trojúhelník
//                     if (j >= n - i - 1) print_star = 1;
//                     break;

//                 case 4: // (d) pravý klesající trojúhelník
//                     if (j >= i) print_star = 1;
//                     break;

//                 case 5: // (e) levý klesající trojúhelník
//                     if (j < n - i) print_star = 1;
//                     break;
//             }

//             printf("%c", print_star ? '*' : ' ');
//         }
//         printf("\n");
//     }
// }

// int main(void) {
//     int n = 5;

//     printf("(a)\n");
//     print_shape(1, n);
//     printf("\n(b)\n");
//     print_shape(2, n);
//     printf("\n(c)\n");
//     print_shape(3, n);
//     printf("\n(d)\n");
//     print_shape(4, n);
//     printf("\n(e)\n");
//     print_shape(5, n);

//     return 0;
// }
