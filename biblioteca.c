#include "biblioteca.h"
#include <stdio.h>

//Função para criar a tarefa onde o usuário pode declarar a prioridade, categoria e descrição do lembrete;
int criartarefa(listadetarefas *lt){
    if (lt->qtd < 100) { //se a quantidade de tarefas for menor que cem (o máximo) o programa irá pedir a prioridade da tarefa, sua categoria e descrição.
        printf("Prioridade (0 a 10): ");
        scanf("%d", &lt->tarefas[lt->qtd].prioridade); //Pedimos a prioridade da tarefa e guardamos a informação na memória.
        printf("Categoria: ");
        scanf(" %[^\n]", lt->tarefas[lt->qtd].categoria); // Usamos " %[^\n]" para ler o "scanf" com espaços, guardando o que o usuário informar como prioridade na memória..
        printf("Descricao: ");
        scanf(" %[^\n]", lt->tarefas[lt->qtd].descricao); // Usamos " %[^\n]" para ler o "scanf" com espaços, guardando o que o usuário informar como prioridade na memória.
        lt->qtd++; //A quantidade de tarefas aumenta quando o usuário terminar de descrever sua tarefa.
        printf("Tarefa cadastrada!\n"); //Quando o usuário terminar de descrever a tarefa essa mensagem aparece.
    } else {
        printf("A lista de tarefas esta cheia! Nao e possivel adicionar mais tarefas.(MAXIMO 100)\n"); //Caso haja mais de 100 tarefas é informado que foi atingida a capacidade máxima.
    }
    return 0;
}


int deletartarefa(listadetarefas *lt){ //Função para deletar tarefas
    int posicao;
    printf("Digite o numero da tarefa que deseja deletar (de 1 a %d): ", lt->qtd); //Pedindo pro usuário informar a tarefa que deve ser deletada.
    scanf("%d", &posicao);//Usuário informa qual é sua tarefa e ela é deletada a partir da posição que está na lista de tarefas (encontramos ela na lista por sua posição).
    if (posicao >= 1 && posicao <= lt->qtd) { //Se a posição da tarefa foi maior que 1 e menor ou igual que a quantidade, poderá ser encontrada (pois ela existe)
        posicao--; //Apaga a tarefa
        for (int i = posicao; i < lt->qtd - 1; i++) { //Um "for" para iterar entre as posições , e enquanto for menor que a quantidade da lista de tarefas, ele apaga e corrige a posição da tarefa na lista.
            lt->tarefas[i] = lt->tarefas[i + 1];
        }
        lt->qtd--; //Diminui a quantidade de tarefas.
        printf("Tarefa deletada!\n"); //Informa que ela foi deletada com sucesso
    } else {
        printf("Essa tarefa nao existe!\n"); //Caso a tarefa não for encontrada (for menor que 1 ou maior que a quantidade atual), será informado que ela não existe.
    }
    return 0;
}


int listartarefa(listadetarefas lt){ //Função para listar as tarefas previamente adicionadas
    if (lt.qtd == 0) {
        printf("A lista de tarefas esta vazia.\n"); //Se a quantidade de tarefas for 0 aparecerá essa mensagem
    } else {
        printf("Lista de tarefas:\n"); //Caso a quantidade de tarefas for maior que 0, pegamos a tarefa por sua posição (i) e listamos.
        for (int i = 0; i < lt.qtd; i++) {
            printf("Tarefa %d:\n", i + 1);//Imprime a tarefa em ordem cronológica (começando por "Tarefa 1"), assim, conforme o número de tarefas cresce é somado o número da tarefa anterior à 1.
            printf("Prioridade: %d\n", lt.tarefas[i].prioridade); //Imprime a prioridade, procurando a  informação a partir da posição da tarefa na lista.
            printf("Categoria: %s\n", lt.tarefas[i].categoria); //Imprime a categoria, procurando a  informação a partir da posição da tarefa na lista.
            printf("Descricao: %s\n", lt.tarefas[i].descricao); //Imprime a descrição, procurando a  informação a partir da posição da tarefa na lista.
            printf("\n"); //Imprime um espaço para organizar a listagem
        }
    }
    return 0;
}


int salvarlista(listadetarefas *lt, char nome[]){ //Função para salvar a lista no arquivo
    FILE *f = fopen(nome, "wb"); //Abre um arquivo no formato binário
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n"); //Caso o arquivo não exista, esta mensagem aparece no terminal alertando o usuário
        return 1;
    }
    fwrite(lt, sizeof(listadetarefas), 1, f); //Este comando escreve no arquivo em formato binário as informações dadas pelo usuário
    fclose(f); //Fecha o arquivo
    return 0;
}


int carregarlista(listadetarefas *lt, char nome[]){ //Função para carregar a lista de tarefas
    FILE *f = fopen(nome, "rb"); //Abre o arquivo em formato de leitura binária
    if (f == NULL) {
        printf("Arquivo nao encontrado.\n"); //Caso o arquivo não exista, esta mensagem aparece no terminal alertando o usuário
        return 1;
    }
    fread(lt, sizeof(listadetarefas), 1, f); //Este comando le o arquivo binário
    fclose(f); //Fecha o arquivo
    return 0;
}