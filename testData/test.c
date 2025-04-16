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
    printf("Age is %d years old.\n", age);

    float updatedGPA = gpa + 0.2f;
    printf("GPA has been updated to %.2f\n", updatedGPA);

    balance = balance * 1.05;
    printf("Balance after interest: %.2lf %c\n", balance, currency);

    grade = 'B';
    printf("New grade is %c\n", grade);

    long futurePopulation = population + 10000000;
    printf("Estimated future population: %ld\n", futurePopulation);

    temperature = temperature + 2;
    printf("Temperature increased to: %hd°C\n", temperature);

    return 0;
}
