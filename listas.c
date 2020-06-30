#include "listas.h"
#define HORARIO 10

static list_especialidade raiz_especialidade;

/**
 * inicializar a raiz para a lista de especialidades
 */
void inicializar(){
    raiz_especialidade = NULL;
}

/**
 * cria um novo nó da list_medico de um determinado nó da lista de especialidades
 * @param nome - ponteiro parra o nome do medico
 * @param raiz - raiz da list_medico daquele nó
 * @return raiz atualizada da list_medico
 */
list_medico colocar_medico(char *nome, list_medico raiz) {
    list_medico  aux;
    list_medico  ant, prox;

    aux = (list_medico) malloc(sizeof(struct medico));
    if (aux == NULL){
        fprintf(stderr, "Insufficient space\n");
        return raiz;
    }

    aux->nome = (char *) malloc (sizeof(char) * (strlen(nome) + 1));
    strcpy(aux->nome, nome);

    aux->num_consultas = 0;

    for(int i =0; i< CONSULTAS; i++){
        aux->consultas[i] = NULL;
    }

    if (raiz == NULL){
        raiz = aux;
    }
    else{

        if(strcasecmp(aux->nome, raiz->nome) < 0){
            aux->next = raiz;
            raiz = aux;
        }

        else{
            ant = raiz;
            prox = raiz->next;

            while(prox != NULL && strcasecmp(nome, prox->nome) > 0){
                ant = ant->next;
                prox = prox ->next;
            }

            ant->next = aux;
            aux->next = prox;
        }
    }

    return raiz;
}

/**
 * cria um novo nó da list_paciente de um determinado nó da lista de especialidades
 * @param nome - ponteiro para o nome do paciente
 * @param grau - int com o grau do paciente
 * @param raiz - raiz da list_paciente daquele nó
 * @return raiz atualizada da list_paciente
 */
list_paciente colocar_paciente(char *nome, int grau, list_paciente raiz) {
    list_paciente  aux;
    list_paciente  ant, prox;

    aux = (list_paciente) malloc(sizeof(struct paciente));
    if (aux == NULL){
        fprintf(stderr, "Insufficient space\n");
        return raiz;
    }

    aux->nome = (char *) malloc (sizeof(char) * (strlen(nome)+1));
    strcpy(aux->nome, nome);
    aux->grau = grau;

    aux->medico = NULL;

    if (raiz == NULL){
        raiz = aux;
    }
    else{
        if(aux->grau > raiz->grau){
            aux->next = raiz;
            raiz = aux;
        }

        else{
            ant = raiz;
            prox = raiz->next;

            while(prox != NULL && prox->grau > grau){
                ant = ant->next;
                prox = prox ->next;
            }

            ant->next = aux;
            aux->next = prox;
        }

    }

    return raiz;
}

/**
 * print da lista de pacientes de um detrminado nó da lista de especialidade
 * @param raiz  - raiz da lista pacientes para aquele nó
 */
void print_paciente(list_paciente raiz){
    list_paciente aux = NULL;
    aux = raiz;
    while(aux != NULL){
        printf("%s %d\n", aux->nome, aux->grau);
        if(aux->medico != NULL){
            printf("->Medico %s %s\n", aux->medico->nome, aux->consulta);
        }
        else{
            printf("Estou em lista de espera.\n");
        }
        aux = aux->next;
    }
}

/**
 * procura determinada especialidade na lista de especialidades
 * @param especialidade - nome da especialidade
 * @return o nó da especialidade desejada, NULL se não for encontrado
 */
list_especialidade procurar_especialidade(char especialidade[]){
    list_especialidade aux = raiz_especialidade;
    while(aux!=NULL && strcasecmp(aux->tipo, especialidade) < 0){
        aux=aux->next;
    }
    if(aux != NULL && strcasecmp(aux->tipo, especialidade) == 0){
        return aux;
    }
    return NULL;
}

/**
 * cria um nó da lista especialidade
 * @param especialidade
 * @param nome - nome paciente/medico
 * @param grau - int 0 a 4 (0 para médicos)
 * @return 0 em cao de sucesso, 1 em caso de erro
 */
int colocar_especialidade(char *especialidade, char *nome, int grau){
    list_especialidade aux;
    list_especialidade ant, prox;

    aux = (list_especialidade) malloc(sizeof(struct especialidade));
    if (aux == NULL){
        fprintf(stderr, "Insufficient space\n");
        return 1;
    }

    aux->tipo = (char *) malloc (sizeof(char) * (strlen(especialidade) + 1));
    strcpy(aux->tipo, especialidade);

    aux->num_medicos = 0;
    aux->num_pacientes = 0;

    aux->lista_pacientes = NULL;
    aux->lista_medicos = NULL;

    if(grau == 0){
        aux->lista_medicos = colocar_medico(nome, aux->lista_medicos);
        aux->num_medicos += 1;
    }
    if(grau != 0){
        aux->lista_pacientes = colocar_paciente(nome, grau, aux->lista_pacientes);
        aux->num_pacientes += 1;
    }

    if (raiz_especialidade == NULL){
        raiz_especialidade = aux;
    }
    else{

        if(strcasecmp(aux->tipo, (raiz_especialidade)->tipo) < 0){
            aux->next = raiz_especialidade;
            raiz_especialidade = aux;
        }

        else{
            ant = raiz_especialidade;
            prox = (raiz_especialidade)->next;

            while(prox != NULL && strcasecmp(especialidade, prox->tipo) > 0){
                ant = ant->next;
                prox = prox ->next;
            }

            ant->next = aux;
            aux->next = prox;
        }
    }

    return 0;
}

/**
 * função auxiliar
 * caso o nó da especilidade já existir chama a função colocar_paciente
 * caso contrário, chama a função colocar_especialidade que vai criar um novo nó
 * @param especialidade
 * @param nome
 * @param grau
 * @return 0 em caso de sucesso, 1 em caso de erro
 */
int colocar_especialidade_paciente(char *especialidade, char *nome, int grau){
    list_especialidade aux = NULL;
    aux = procurar_especialidade(especialidade);
    if(aux != NULL){
        aux->lista_pacientes = colocar_paciente(nome, grau, aux->lista_pacientes);
        aux->num_pacientes += 1;
    }
    else{
        colocar_especialidade(especialidade, nome, grau);
    }
    return 0;
}

/**
 * função auxiliar
 * caso o nó da especilidade já existir chama a função colocar_medico
 * caso contrário, chama a função colocar_especialidade que vai criar um novo nó
 * @param especialidade
 * @param nome
 * @return 0 em caso de sucesso, 1 em caso de erro
 */
int colocar_especialidade_medico(char *especialidade, char *nome){
    list_especialidade aux = NULL;
    aux = procurar_especialidade(especialidade);
    if(aux != NULL){
        aux->lista_medicos = colocar_medico(nome, aux->lista_medicos);
        aux->num_medicos += 1;
    }
    else{
        colocar_especialidade(especialidade, nome, 0);
    }
    return 0;
}

/**
 * função para debug - print da lista de especialidades
 * já inclui o print dos paciente e os seus médicos
 */
void print_especialidade(){
    list_especialidade aux = NULL;
    aux = raiz_especialidade;

    while(aux != NULL){
        printf("\n%s\nmedicos: %d, pacientes: %d\n", aux->tipo, aux->num_medicos, aux->num_pacientes);
        print_paciente(aux->lista_pacientes);
        aux = aux->next;
    }
}


/**
 * elimina a lista ligada de médicos de um nó da lista de especialidades
 * @param raiz - raiz da lista ligada de médicos
 */
void eliminar_list_medico (list_medico raiz){
    list_medico  aux = NULL;

    while(raiz != NULL){
        aux = raiz->next;
        free(raiz->nome);
        free(raiz);
        raiz = aux;
    }
}

/**
 * elimina a lista ligada de pacientes de um nó da lista de especialidades
 * @param raiz - raiz da lista de pacientes
 */
void eliminar_list_paciente (list_paciente raiz){
    list_paciente  aux = NULL;

    while(raiz != NULL){
        aux = raiz->next;
        free(raiz->nome);
        free(raiz);
        raiz = aux;
    }
}

/**
 * elimina toda a lista de especialidades
 * usa as funções eliminar_list_medico e eliminar_list_paciente
 */
void eliminar_list_especialidade (){
    list_especialidade aux = NULL;
    list_especialidade raiz = raiz_especialidade;

    while(raiz != NULL){
        aux =raiz->next;
        free(raiz->tipo);
        eliminar_list_medico(raiz->lista_medicos);
        eliminar_list_paciente(raiz->lista_pacientes);
        free(raiz);
        raiz = aux;
    }
}



/**
 * verifica se uma string tem números
 * @param string
 * @return 0 se não existirem números, 1 caso contrário
 */
int sem_numeros(char string[]){
    int i = 0;
    char c = string[i];

    while(c != '\0'){
        if(c > 47 && c < 58){
            return 1;
        }
        c = string[++i];
    }

    return 0;
}

/**
 * Ler ficheiro de texto
 * usa funções auxiliares para colocar os dados na lista ligada
 * @param file_medicos - nome do ficheiro (pode ser preenchido a NULL)
 * @param file_pacientes - nome do ficheiro (pode ser preenchido a NULL)
 * @return 1 em caso de erro, 0 caso contrario
 */
int read_file(char file_medicos[], char file_pacientes[]){

    char line[MAXLINHA] = "", *name_file = NULL;
    char *token = NULL, *aux = NULL, *ptr = NULL;
    char ** vetor = NULL;
    int i, grau, counter = 1, erros = 0;
    size_t tamanho_original;

    FILE *file = NULL;

    if(file_medicos != NULL){
        file = fopen(file_medicos, "r");
        name_file = file_medicos;
    }
    else if(file_pacientes != NULL){
        file = fopen(file_pacientes, "r");
        name_file = file_pacientes;
    }
    else{
        return 1;
    }

    fseek (file, 0, SEEK_SET);

    if(file == NULL){
        fprintf(stderr, "File not found\n");
        return 1;
    }

    while(fgets(line, sizeof(line), file) != NULL){

        i=1;

        /*Verificar se a linha não ultrapassa o número de carateres definido
         * se ultrapassar vou ignorar essa linha
        */
        if(line[strlen(line) - 1] != '\n'){
            while(fgets(line, sizeof(line), file) != NULL && line[strlen(line)-1] != '\n'){
                memset(line, '\0', strlen(line));
            }
            memset(line, '\0', strlen(line));
            fprintf(stderr, "Erro em %s - excedeu tamanho aceite - linha %d\n", name_file, counter);
            counter++;
            erros ++;
            continue;
        }

        line[strlen(line)-1]= '\0';
        line[strlen(line)-1]= '\0';

        tamanho_original = strlen(line);

        if(tamanho_original == 0){
            counter++;
            continue;
        }


        vetor= (char**)malloc(sizeof(char*)*4);

        token = strtok(line, "\t");

        aux=(char*)malloc(sizeof(char)*(strlen(token)+1));
        strcpy(aux, token);
        vetor[0]=aux;

        while(i<5 && token != NULL){
            token = strtok(NULL, "\t");

            if(token != NULL){
                aux=(char*)malloc(sizeof(char)*(strlen(token)+1));
                strcpy(aux, token);
                vetor[i]=aux;
                i++;
            }
        }


        if(i == 2 && file_medicos != NULL && sem_numeros(vetor[1])==0) {
            //MEDICO
            colocar_especialidade_medico(vetor[1],vetor[0]);
        }
        else if(i == 3 && file_pacientes != NULL && sem_numeros(vetor[1])==0){
            //PACIENTE
            grau = (int) strtol( vetor[2], &ptr, 10);
            if(0 < grau && grau < 5 && *ptr == NULL){
                colocar_especialidade_paciente(vetor[1],vetor[0], grau);
            }
            else{
                fprintf(stderr, "Erro em %s - grau incorreto - linha %d\n", name_file, counter);
            }
        }
        else{
            fprintf(stderr, "Erro em %s - linha %d\n", name_file, counter);
            erros ++;

            /*optei por definir um limite para os erros em cada ficheiro,
             * pode e deve ser alterado consoate o número de entidades em cada ficheiro*/
            if((erros == 5 && file_medicos != NULL) || (erros == 15 && file_pacientes != NULL)){
                fprintf(stderr, "%s tem demasiados erros para continuar. Tem a certeza que se trata do ficheiro certo?\nCorret command: main <file_medicos> <file_pacientes>\n", name_file);
                return 1;
            }

        }
        counter++;

        memset(line, '\0', tamanho_original);

        free(vetor);
        vetor = NULL;
        free(aux);
        aux = NULL;
    }

    fclose(file);
    return 0;
}



/**
 * marcar consultas
 * consiste a atribuir um médico a cada paciente (caso existam médicos disponíves)
 */
void marcar_consultas(){

    int num_consultas;

    list_especialidade aux = NULL;
    list_paciente paciente_aux = NULL;
    list_medico medico_aux = NULL;

    aux = raiz_especialidade;

    while(aux != NULL){
        paciente_aux = aux->lista_pacientes;
        medico_aux = aux->lista_medicos;

        /*Percorro a lista de pacientes para aquele nó da lista de especialidades,
         *se existir um médico disponível, vou marcar a consulta.
         *Isto consiste colocar o paciente a apontar para o seu médico
         *e o médico a apontar para o seu paciente dentro do vetor de consultas
         */
        while(paciente_aux != NULL){
            if(aux->num_medicos == 0){
                break;
            }
            else{
                if(medico_aux == NULL){
                    medico_aux = aux->lista_medicos;
                }
                else{
                    num_consultas = medico_aux->num_consultas;
                    /*um medico só pode ter no máximo 10 consultas*/
                    if(num_consultas < CONSULTAS){
                        medico_aux->consultas[num_consultas] = paciente_aux;
                        paciente_aux->medico = medico_aux;
                        if(num_consultas % 2 == 0){
                            sprintf(paciente_aux->consulta,"%dh%s", HORARIO + num_consultas/2, "00");
                        }
                        else{
                            sprintf(paciente_aux->consulta,"%dh%s", HORARIO + num_consultas/2, "30");
                        }
                        medico_aux->num_consultas += 1;
                        medico_aux = medico_aux->next;
                    }
                    paciente_aux = paciente_aux->next;
                }
            }
        }
        aux = aux->next;
    }
}



/**
 * lê os nomes para os ficheiros de saída
 * @param linha número da linha do ficheiro (1 ou 2)
 * @param name_file nome do ficheiro de saída que foi lido
 * @return 1 em caso de erro, 0 caso contrario
 */
int config(int linha, char name_file[]){
    char line[MAXLINHA];
    int counter = 0;

    FILE *file = NULL;
    file = fopen("../config.txt", "r");

    if(file == NULL) {
        fprintf(stderr, "File not found\n");
        return 1;
    }

    fseek (file, 0, SEEK_SET);

    while(counter != linha && fgets(line, sizeof(line), file) != NULL){
        counter +=1;
    }

    line[strlen(line) - 1] = '\0';
    line[strlen(line) - 1] = '\0';

    sprintf(name_file, "../%s.txt", line);

    fclose(file);

    return 0;
}

/**
 * Escrita no ficheiro de texto dos medicos
 * @return 1 em caso de erro, 0 caso contrario
 */
int write_file_medicos(){

    char *line = NULL, name[64] = "";
    int tamanho = 0;

    list_especialidade aux = NULL;
    list_medico aux_medico;

    aux = raiz_especialidade;


    /*ler o nome do ficheiro de saída*/
    config(1, name);

    if(strcmp(name, "") == 0){
        strcpy(name, "../medicos_output_standart.txt");
        fprintf(stderr, "Erro na leitura do file config\nNome standart escolhido para o ficheiro de medicos\n");
    }


    FILE *file = NULL;
    file = fopen(name, "w");

    fseek (file, 0, SEEK_SET);

    if(file == NULL) {
        fprintf(stderr, "File not found\n");
        return 1;
    }


    while(aux != NULL){
        if(aux->num_medicos != 0){
            tamanho = 0;
            aux_medico = aux->lista_medicos;

            /*Para cada iteração deste ciclo vou alocar espaço para uma linha com o nome do médico.
             * A seguir, vou realocando esse espaço para inserir mais informação à linha.
             * Para isso uso a função realloc e a função strcat para concatenar.
             * No final da iteração liberto a linha com um free e coloca esta linha a apontar para NULL.
             */

            while(aux_medico != NULL){

                tamanho += 1 + (int) strlen(aux_medico->nome);
                line = (char*) malloc (tamanho*sizeof(char));
                strcpy(line, aux_medico->nome);

                tamanho += 2 + (int) strlen(aux->tipo);
                line = (char*) realloc (line, tamanho*sizeof(char));
                strcat(line, "\t");
                strcat(line, aux->tipo);

                for(int i =0; i < aux_medico->num_consultas; i++){
                    tamanho += 2 + (int) strlen(aux_medico->consultas[i]->nome);
                    line = (char*) realloc (line, tamanho*sizeof(char));
                    strcat(line, "\t");
                    strcat(line, aux_medico->consultas[i]->nome);
                }
                aux_medico = aux_medico->next;

                fprintf(file, "%s\n", line);

                free(line);

                line = NULL;
            }
        }

        aux = aux->next;
    }

    fclose(file);

    return 0;
}

/**
 * Escrita no ficheiro de texto dos pacientes
 * @return 1 em caso de erro, 0 caso contrario
 */
int write_file_pacientes(){

    char name[64] = "";

    list_especialidade aux = NULL;
    list_paciente aux_paciente;


    /*ler o nome do ficheiro de saída*/
    config(2, name);
    if(strcmp(name, "") == 0){
        strcpy(name, "../pacientes_output_standart.txt");
        fprintf(stderr, "Erro na leitura do file config\nNome standart escolhido para o ficheiro de pacientes\n");
    }


    FILE *file = NULL;
    file = fopen(name, "w");

    fseek (file, 0, SEEK_SET);

    if(file == NULL) {
        fprintf(stderr, "File not found\n");
        return 1;
    }

    aux = raiz_especialidade;

    /*Formato de saída: paciente por linha com estes atributos
     * nome paciente\t
     * grau\t
     * especialidade\t
     * horário\tnome medico OU "em lista de espera"
     * */

    while(aux != NULL){
        aux_paciente = aux->lista_pacientes;
        while(aux_paciente != NULL){
            if(aux_paciente->medico != NULL){
                fprintf(file, "%s\t%d\t%s\t%s\t%s\n", aux_paciente->nome, aux_paciente->grau, aux->tipo, aux_paciente->consulta, aux_paciente->medico->nome);
            }
            else{
                /*Caso em que não existe médico disponível para atender o paciente - fica em lista de espera*/
                fprintf(file, "%s\t%d\t%s\t%s\n", aux_paciente->nome, aux_paciente->grau, aux->tipo, "em lista de espera");
            }
            aux_paciente = aux_paciente->next;
        }
        aux = aux->next;
    }

    return 0;
}

