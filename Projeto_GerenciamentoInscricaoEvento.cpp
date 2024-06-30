#include <iostream>
#include <ctime>
using namespace std;

// Estrutura para armazenar informações de um participante
struct participante{
    string nome;
    string num;
    string email;
    int porcentagem;
    participante* ant;
    participante* prox;
};

// Estrutura para armazenar informações de uma atividade
struct atividade{
    string titulo;
    string hora;
    string tipo;
    atividade* prox;
};

// Estrutura descritor para a lista de participantes
struct descritorP{
    participante* ini;
    participante* fim;
    int tam;
};

// Função para criar a lista de participantes
descritorP* criarL(){
    descritorP* novo= new descritorP;
    novo->ini= NULL;
    novo->fim= NULL;
    novo->tam= 0;
    return novo;
}

// Função para adicionar um participante ao final da lista
void fimParticipante(descritorP* L, string nome, string num, string email){
    participante* novo= new participante;
    novo->nome= nome;
    novo->num= num;
    novo->email= email;
    novo->prox= NULL;
    novo->ant= NULL;
    if(L->tam == 0){
        L->fim= novo;
        L->ini= novo;
    }
    else{
        L->fim->prox= novo;
        novo->ant= L->fim;
        L->fim= novo;
    }
    L->tam++;
}

void addParticipante(descritorP* L, string nome, string num, string email){
    int x= 0, cont= 0;

    cout << "Adicionar participantes na lista! " << endl;
    while (x != 2){
        cout << "Digite o nome do participante " << cont + 1 << ": ";
        cin.ignore();
        getline(cin, nome);
        cout << "Digite o numero de inscricao do participante " << cont + 1 << ": ";
        getline(cin, num);
        cout << "Digite o email do participante " << cont + 1 << ": ";
        getline(cin, email);
        fimParticipante(L, nome, num, email);
        cout << "Adicionar mais 1 participante a lista (1- sim/ 2- nao)? ";
        cin >> x;
        while (x != 1 && x != 2){
            cout << "Insira um valor valido (1- sim/ 2- nao)? ";
            cin >> x;
        }
        if(x == 1){
            cont++;
            cout << endl;
        }
    }
}

// Função para adicionar uma atividade ao final da lista
void fimAtividade(atividade*& L, string titulo, string hora, string tipo){
    atividade* novo= new atividade;
    novo->titulo= titulo;
    novo->hora= hora;
    novo->tipo= tipo;
    novo->prox= NULL;
    if(L == NULL){
        L= novo;
    }
    else{
        atividade* P= L;
        while (P->prox != NULL){
            P= P->prox;
        }
        P->prox= novo;
    }
}

// Funcao complemento para adicionar uma atividade na lista
void add_atividade(atividade*& L, string tit, string tipo, string hora){
    int x= 0, cont= 0;

    cout << "Adicionar atividades lista! " << endl;
    while (x != 2){
        cout << "Digite o titulo da atividade " << cont + 1 << ": ";
        cin.ignore();
        getline(cin, tit);
        cout << "Digite o tipo da atividade " << cont + 1 << ": ";
        getline(cin, tipo);
        cout << "Digite a hora que a " << cont + 1 << " atividade foi realizada: ";
        getline(cin, hora);
        fimAtividade(L, tit, hora, tipo);
        cout << "Adicionar mais 1 atividade a lista (1- sim/ 2- nao)? ";
        cin >> x;
        while (x != 1 && x != 2){
            cout << "Insira um valor valido (1- sim/ 2- nao)? ";
            cin >> x;
        }
        if(x == 1){
            cont++;
        }
        cout << endl;
    }
}

// Função para calcular o tamanho da lista de atividades
int tamanho(atividade* L){
    int cont= 1;
    if(L == NULL){
        return 0;
    }
    while (L->prox != NULL){
        L= L->prox;
        cont++;
    }
    return cont;
}

// Função para criar uma matriz de participação
bool** criar_matriz(descritorP* L, atividade* A){
    int tam= tamanho(A);
    bool** mtz= new bool* [L->tam];
    for (int i= 0; i < L->tam; i++){
        mtz[i]= new bool[tam];
    }
    return mtz;
}

// Função para preencher a matriz de participação
void add_matriz(bool** mtz, descritorP* L, atividade* A){
    participante* P= L->ini;
    int tam= tamanho(A);
    int x;

    for (int i= 0; i < L->tam; i++){
        atividade* At= A;
        for (int j= 0; j < tam; j++){
            cout << "Participante: " << P->nome << " participou do evento " << At->titulo << "? ";
            cout << "1- Sim, 2- Não: ";
            cin >> x;
            while (x != 1 && x != 2){
                cout << "Insira um valor válido (1- Sim, 2- Não): ";
                cin >> x;
            }
            if(x == 1){
                mtz[i][j]= true;
            }
            else{
                mtz[i][j]= false;
            }
            At= At->prox;
        }
        P= P->prox;
    }
}

// Função para calcular a porcentagem de participação de cada participante
void calculo(bool** mtz, descritorP* L, atividade* A){
    participante* P= L->ini;
    int tam= tamanho(A);

    for (int i= 0; i < L->tam; i++){
        int porcentagem= 0;
        for (int j= 0; j < tam; j++){
            if(mtz[i][j]){
                porcentagem++;
            }
        }
        P->porcentagem= (porcentagem * 100) / tam;
        P= P->prox;
    }
}

// Função para remover participantes com participação inferior a 75%
void select_maior(descritorP* L){
    participante* P= L->ini;

    while (P != NULL){
        participante* A= P;
        P= P->prox;
        if(A->porcentagem < 75){
            if(A->ant == NULL){
                L->ini= P;
                if(P != NULL){
                    P->ant= NULL;
                }
            }
            else{
                A->ant->prox= P;
                if(P != NULL){
                    P->ant= A->ant;
                }
            }
            if(A == L->fim){
                L->fim= A->ant;
            }
            delete A;
            L->tam--;
        }
    }
}

// Função para verifar se um nome já foi sorteado
bool repetido(string* v, string nome, int tam){
    for (int i= 0; i < tam; i++){
        if(nome == v[i]){
            return true;
        }
    }
    return false;
}

// Função para realizar o sorteio entre os participantes
string* sorteio(descritorP* L, int tam){

    if(L->tam == 0){
        return NULL;
    }

    string* v= new string[tam];
    srand(time(0));

    for (int i= 0; i < tam; i++){
        int sort;
        participante* P;
        do{
            sort= rand() % L->tam;
            P= L->ini;
            for (int j= 0; j < sort; j++){
                P= P->prox;
            }
        } while (repetido(v, P->nome, i));

        v[i]= P->nome;
    }

    return v;
}

//Função para mostrar os participantes sorteados
void mostrar_sorteados(descritorP* L){
    int numGanhadores= 3;
    string* vetor_de_sorteados= sorteio(L, numGanhadores);

    if(vetor_de_sorteados != NULL){
        cout << "Os ganhadores do sorteio foram: " << endl;
        for (int i= 0; i < numGanhadores; i++){
            cout << "O ganhador do " << i + 1 << " brinde foi: " << vetor_de_sorteados[i] << endl;
        }
    }
    else{
        cout << "Nenhum participante disponível para sorteio." << endl;
    }
    delete[] vetor_de_sorteados;
}

int menu(){
    int op;
    cout << "----INFORMACOES----" << endl;
    cout << "1- Adicionar participantes." << endl;
    cout << "2- Adicionar atividades" << endl;
    cout << "3- Sorteio" << endl;
    cout << "4- Sair" << endl;
    cin >> op;

    return op;
}

// Função para liberar memória
void liberarMemoria(descritorP* listaParticipantes, atividade* listaAtividades, bool** matriz){
    participante* p= listaParticipantes->ini;
    while (p != NULL){
        participante* temp= p;
        p= p->prox;
        delete temp;
    }
    atividade* a= listaAtividades;
    while (a != NULL){
        atividade* temp= a;
        a= a->prox;
        delete temp;
    }
    for (int i= 0; i < listaParticipantes->tam; i++){
        delete[] matriz[i];
    }
    delete[] matriz;
    delete listaParticipantes;
}

// Função principal
int main(){
    descritorP* listaParticipantes= criarL();
    atividade* listaAtividades= NULL;

    string nome, num, email, tit, tipo, hora;

    int op= menu();

    while (op != 4){
        if(op == 1){
            addParticipante(listaParticipantes, nome, num, email);
        }
        else if(op == 2){
            add_atividade(listaAtividades, tit, tipo, hora);
        }
        else if(op == 3){
            bool** matriz= criar_matriz(listaParticipantes, listaAtividades);
            add_matriz(matriz, listaParticipantes, listaAtividades);
            calculo(matriz, listaParticipantes, listaAtividades);
            select_maior(listaParticipantes);
            mostrar_sorteados(listaParticipantes);
            liberarMemoria(listaParticipantes, listaAtividades, matriz);
        }
        else{
            op= 4;
        }
        op= menu();
    }
    return 0;
}