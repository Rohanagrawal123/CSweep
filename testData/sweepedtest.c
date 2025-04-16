#include <stdio.h>

int main() {
    // Variable declarations
    int age = 22;
    float gpa = 8.74f;
    double balance = 12345.6789;
    char grade = 'A';
    long population = 1400000000L;
    short temperature = 25;
    char currency = '$';

    // Simple usage of each variable
printf("Age is %d years old.\n", age); free(&age);

float updatedGPA = gpa + 0.2f; free(&gpa);
printf("GPA has been updated to %.2f\n", updatedGPA); free(&updatedGPA);

    balance = balance * 1.05;
printf("Balance after interest: %.2lf %c\n", balance, currency); free(&currency);

    grade = 'B';
printf("New grade is %c\n", grade); free(&grade);

long futurePopulation = population + 10000000; free(&population);
printf("Estimated future population: %ld\n", futurePopulation); free(&futurePopulation);

    temperature = temperature + 2;
printf("Temperature increased to: %hd°C\n", temperature); free(&temperature);

    return 0;
}
