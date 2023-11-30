/**
 * Stiven Castro Sanchez(202177771-2724)-
stiven.castro@correounivalle.edu.co

Miguel Angel Caicedo Mosquera(202177619-2724)
miguel.caicedo.mosquera@correounivalle.edu.co

Daniel Sebastian Leiva Guerrero (2024684-2724)
daniel.leiva@correounivalle.edu.co
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INSTRUCTION_LENGTH 20
#define MAX_OPERAND_LENGTH 5

// Definición de registros y memoria
int accumulator = 0; // Acumulador
int instructionCounter = 0;
int mar = 0; // Registro de dirección de memoria
int mdr = 0; // Registro de datos de memoria
int icr = 0;
int memory[1000] = {0}; // Memoria de 1000 posiciones

// Funciones para ejecutar las instrucciones
void executeSET(int op1, int op2, int op3)
{
    memory[op1] = op2;
}
void executeLDR(int op1, int op2, int op3)
{
    accumulator = memory[op1];
}
// aun estoy organizando esta funcion
void executeADD(int op1, int op2, int op3)
{
    if (op2 == 0 && op3 == 0)
    {
        accumulator += memory[op1];
    }
    else if (op3 == 0)
    {
        accumulator = memory[op1] + memory[op2];
    }
    else
    {
        memory[op3] = memory[op1] + memory[op2];
    }
}
void executeINC(int op1, int op2, int op3)
{
    memory[op1]++;
}
void executeDEC(int op1, int op2, int op3)
{
    memory[op1]--;
}
void executeSTR(int op1, int op2, int op3)
{
    memory[op1] = accumulator;
}

void executeSHW(int op1, int op2, int op3)
{
    switch (op1)
    {
    case 0:
        printf("Value in D2: %i\n", memory[op2]);
        break;
    case 1:
        printf("Value in accumulator: %i\n", accumulator);
        break;
    case 2:
        printf("Value in MAR: %i\n", mar);
        break;
    case 3:
        printf("Value in MDR %i\n", mdr);
        break;
    case 4:
        printf("Value in UC %i\n", icr);
        break;
    }
}
void executePAUSE(int op1, int op2, int op3)
{
    printf("Valor del acumulador: %i\n contadorInstrucciones: %i\n memoria: %i\n");
    exit(1);
}
void executeEND(int op1, int op2, int op3)
{
    printf("Resultados de los datos que fueron tomados valor del acumulador: %i\n contadorInstrucciones: %i\n memoria: %i\n");
}
// Función principal que interpreta las instrucciones
void interpretInstruction(char *instruction, int op1, int op2, int op3)
{
    char instructionType[1] = {'0'};

    if (instruction[1] == 'H')
    {
        instructionType[0] = instruction[1];
    }
    else if (instruction[1] == 'T')
    {
        instructionType[0] = instruction[1];
    }

    else
    {
        instructionType[0] = instruction[0];
    }

    switch (instructionType[0])
    {

    case 'S':
        executeSET(op1, op2, op3);
        break;
    case 'L':
        executeLDR(op1, op2, op3);
        break;
    case 'A':
        executeADD(op1, op2, op3);
        break;
    case 'I':
        executeINC(op1, op2, op3);
        break;
    case 'D':
        executeDEC(op1, op2, op3);
        break;
    case 'T':
        executeSTR(op1, op2, op3);
        break;
    case 'H':
        executeSHW(op1, op2, op3);
        break;
    case 'P':
        executePAUSE(op1, op2, op3);
        break;
    case 'E':
        executeEND(op1, op2, op3);
        break;
    default:
        printf("Instruccion no reconocida: %c\n", instructionType[0]);
    }
}

int main()
{

    FILE *archivo;

    char instruction[MAX_INSTRUCTION_LENGTH], registro[MAX_OPERAND_LENGTH],
        op1[MAX_OPERAND_LENGTH], op2[MAX_OPERAND_LENGTH], op3[MAX_OPERAND_LENGTH];

    // Abre el archivo en modo lectura
    archivo = fopen("programa1.txt", "r");

    // Verifica si el archivo se abrió correctamente
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Lee cada línea del archivo
    while (fscanf(archivo, "%s %s %s %s %s", instruction, registro, op1, op2, op3) == 5)
    {
        // Procesa la línea según tus necesidades
        printf("Instruccion: %s, Registro: %s, Op1: %s, Op2: %s, Op3: %s\n",
               instruction, registro, op1, op2, op3);

        // Llama a la función para interpretar y ejecutar la instrucción
        interpretInstruction(instruction, atoi(op1), atoi(op2), atoi(op3));
    }

    // Cierra el archivo
    fclose(archivo);

    return 0;
}
