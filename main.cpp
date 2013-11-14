#include <stdio.h>
#include "vector.hpp"
#include "triangle.hpp"

int main(){
	printf("\n\n\n");

	Vector a(1,2,3), b(3,2,2);
	printf("%.2f, %.2f, %.2f\n", (a-b)[0], (a-b)[1], (a+b)[2]);
	printf("%.2f, %.2f, %.2f\n", (3*a)[0], (3*a)[1], (3*a)[2]);
	printf("%.2f, %.2f, %.2f\n", (a*3)[0], (a*3)[1], (a*3)[2]);
	printf("%.2f\n", (a*b));
    printf("%.2f\n", ~a);

	printf("\n\n\n");
}
