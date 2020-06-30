#ifndef PROJETO_LISTAS_H
#define PROJETO_LISTAS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CONSULTAS 10
#define HORARIO 10
#define MAXLINHA 128

typedef struct medico * list_medico;
typedef struct paciente * list_paciente;
typedef struct especialidade *list_especialidade;

struct medico{
    char *nome;
    int num_consultas;
    list_paciente consultas[CONSULTAS];
    struct medico * next;
};

struct paciente{
    char *nome;
    char consulta[6];
    int grau;
    struct medico * medico;
    struct paciente * next;
};

struct especialidade{
    char *tipo;
    list_paciente lista_pacientes;
    list_medico lista_medicos;
    int num_medicos;
    int num_pacientes; //SÓ PARA DEBUG
    struct especialidade * next;
};

void inicializar();

int read_file(char[], char[]);

void print_especialidade();

void marcar_consultas();

int write_file_medicos();

int write_file_pacientes();

void eliminar_list_especialidade();


#endif //PROJETO_LISTAS_H