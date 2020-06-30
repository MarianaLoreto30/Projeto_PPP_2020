#include "listas.h"

/**ESTRUTURA DO PROGRAMA*/
/*
 * Projeto no âmbito da cadeira de Princípios de Programação Procedimental,
 * desenvolvido por Mariana Almeida Loreto
 *
 * O objetivo deste programa é a partir de 2 ficheiros - lista de pacientes e médicos - fazer a marcação de consultas.
 *
 * A minha interpretação do problema assentou na criação de uma lista de especialidades
 * (sendo este um fator comum de ambas a entidades - médicos e pacientes).
 *
 * Cada nó desta lista, tem 2 listas ligadas complementares.
 * Uma lista para médicos e uma lista para pacientes, ambas com atritutos distintos.
 *
 * Todas estas estruturas estão especificadas no ficheiro listas.h
 *
 * Todas as funções criadas estão toatalmente comentadas no listas.c
 */

/****MAIN****/

int main(int argc, char *argv[]) {


    if(argc != 3){
        fprintf(stderr, "Argumentos incorretos!\nComando correto: main <file_medicos> <file_pacientes>\n");
        return 1;
    }

    inicializar();

    /*LEITURA DOS FICHEIROS*/
    if(read_file(argv[1], NULL) !=0){
        fprintf(stderr, "Erro leitura file_medicos\n");
        return 1;
    }
    if(read_file(NULL, argv[2]) != 0){
        fprintf(stderr, "Erro leitura file_pacientes\n");
        return 1;
    }


    /*MARCAÇÂO DE CONSULTAS*/
    marcar_consultas();

    /*DEBUG - PRINT DA LISTA DE ESPECILIDADES COM AS MARCAÇÕES*/
    //print_especialidade();


    /*ESCRITA FINAL NOS FICHEIROS*/
    if(write_file_medicos() != 0){
        fprintf(stderr, "Erro escrita file_medicos\n");
    }

   if(write_file_pacientes() != 0){
       fprintf(stderr, "Erro escrita file_pacientes\n");
   }


   /*ELIMINAR A LISTA LIGADA E AS SUAS SUB-LISTAS*/
    eliminar_list_especialidade();

    return 0;

}
