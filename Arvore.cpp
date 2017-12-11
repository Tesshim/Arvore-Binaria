#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

typedef struct TipoNo * TipoApontador;

struct TipoNo
{
	long int chave;
	string nome;
	TipoApontador esq, dir;
};

void pesquisaInt(long int chave, TipoApontador arvore);

void insere(long int chave, string nome, TipoApontador &arvore);

void inicializa(TipoApontador &arvore);

void antecessor(TipoApontador q, TipoApontador &r);

void retira(long int chave, TipoApontador &arvore);

void mostra(TipoApontador arvore);

void leArquivo (TipoApontador &arvore);

void escreveArquivo (TipoApontador &arvore);

int get_size(const char* file_name);

void pesquisaNome (string nome, TipoApontador arvore);

int main()
{
	TipoApontador arvore; inicializa(arvore);	
	long int chave;
	char nome[40], buffer[2];
	
	if(get_size("Dados.txt") != 0)
	{
		leArquivo(arvore);
	}
	
	
	// MENU + INTERATIVO
	short int interromper = 0;
  	while(!interromper)
  	{
  		puts("Otica Boa Vista!");
    	puts("Digite:");
    	puts("1 : Cadastrar!");
    	puts("2 : Pesquisar!");
    	puts("3 : Mostrar!");
    	puts("4 : Excluir!");
    	puts("ESC : Sair do programa.");
    	switch(getch())
    	{
       	case '1':system("CLS");
                       // Coloque os itens aqui!
                       cout << "Entre com o codigo: ";
                       cin >> chave;
                       cout << "Entre com o nome: ";
                       cin.getline(buffer, 2);
                       cin.getline(nome, 40);
                       insere(chave, nome ,arvore);
                       cout << "CADASTRADO COM SUCESSO!!"<<endl;
                       system("PAUSE");
                   break;
       	case '2':system("CLS");
               // Coloque os itens aqui!
               			puts("Digite:");
               			puts("1 : Pesquisa Codigo ");
               			puts("2 : Pesquisa Nome");
               			switch(getch())
               			{
               					case '1':system("CLS");
               						cout << "Entre com o codigo: ";
               						cin >> chave;
               						pesquisaInt(chave, arvore);
               						system("PAUSE");
              			 			break;
              			 		case '2':system("CLS");
              			 			//cin.getline(buffer, 2);
              			 			cout << "Entre com o nome: ";
              			 			cin.getline(nome, 40);
              			 			pesquisaNome(nome, arvore);
              			 			system("PAUSE");
               						break;
			   			}
               			break;
       	case '3':system("CLS");
               // Coloque os itens aqui!
						mostra(arvore);
						system("PAUSE");
                   		break;
                   		
        case '4':system("CLS");
        	   // Coloque os itens aqui!
						cout << "Entre com o codigo do produto: ";
						cin >> chave;
						retira(chave, arvore);
						cout << "RETIRADO COM SUCESSO" << endl;
						system("PAUSE");
        				break;
        				
       	case 27:system("CLS"); // Opção da tecla ESC
                   interromper=1;
               break;
       	default:system("CLS");
              puts("Opcao invalida!\a");
                      break;
    	}
    	system("CLS");
	}
	
	ofstream arquivo ("Dados.txt");
	arquivo.clear();
	escreveArquivo(arvore);
	
	cout <<"PASSOU"<<endl;
	
	return 0;
}

void pesquisaNome (string nome, TipoApontador arvore)
{
	if (arvore == NULL)
		return;
		
	if (arvore->nome.compare(nome) == 0)
	{
		cout << "Chave: "<< arvore->chave << endl;
		cout << "Nome: "<< arvore->nome <<endl;
		return;
	}
	
	pesquisaNome(nome, arvore->dir);
	pesquisaNome(nome, arvore->esq);
	
}

void pesquisaInt(long int chave, TipoApontador arvore)
{
	if ( arvore == NULL)
	{
		cout <<"Registro nao encontrado"<<endl;
		return;
	}
		
		if (chave < arvore->chave)
			pesquisaInt(chave, arvore->esq);
		
		if (chave > arvore->chave)
			pesquisaInt(chave, arvore->dir);
			
		if (arvore->chave == chave)
		{
			cout<< "Chave: "<<arvore->chave<<endl;
			cout<< "Nome: "<<arvore->nome<<endl;
		}
			
}

void insere(long int chave, string nome, TipoApontador &arvore)
{
	
	if (arvore == NULL)
	{
		arvore = new TipoNo;
		arvore->chave = chave;
		arvore->nome = nome;
		arvore->dir = NULL;
		arvore->esq = NULL;
		return;
	}
	
	if(chave < arvore->chave)
		insere(chave,nome, arvore->esq);
	
	if(chave > arvore->chave)
		insere(chave,nome,arvore->dir);
		
	if (chave == arvore->chave)
	{
		cout <<"Registro ja cadastrado!!"<<endl;
		return;
	}	
		
}

void inicializa(TipoApontador &arvore)
{
	arvore = NULL;
	return;
}

void antecessor(TipoApontador q, TipoApontador &r)
{
	if(r->dir != NULL)
	{
		antecessor(q,r->dir);
		return;
	}
	
	q->chave = r->chave;
	q = r;
	r = r->esq;
	delete q;
	
}

void retira(long int chave, TipoApontador &arvore)
{
	TipoApontador aux;
	
	if( arvore == NULL)
	{
		cout << "Registro nao esta na arvore"<< endl;
		return;
	}
	
	if(chave < arvore->chave)
	{
		retira(chave, arvore->esq);
		return;
	}
	
	if(chave > arvore->chave)
	{
		retira(chave, arvore->dir);
		return;
	}
	
	if (arvore->dir == NULL)
	{
		aux = arvore;
		arvore = arvore->esq;
		delete aux;
		return;
	}
	
	if(arvore->esq != NULL)
	{
		antecessor(arvore, arvore->esq);
		return;
	}
	
	aux = arvore;
	arvore = arvore->dir;
	delete aux;
	
}

void mostra(TipoApontador arvore)
{
	if(arvore == NULL)
		return;
		
	mostra(arvore->esq);
	
	cout << "Registro: "<< arvore->chave << endl;
	cout << "Nome: "<< arvore->nome <<endl;
	cout << "________________________________"<<endl;
	
	mostra(arvore->dir);
	
	return;
}

void leArquivo (TipoApontador &arvore)
{
	
	long int cod, aux;
	char nome[40], a[2];
	ifstream arquivo("Dados.txt",ios::in);
	
	
	if(!arquivo.is_open())
	{
		cout<<"Nao abre"<<endl;
		return;
	}
	
	for(int i = 0 ; !arquivo.fail(); i++)
	{
		    
		arquivo>>cod;
		arquivo.getline(a, 40);
		arquivo.getline(nome, 40);
		
		if (i == 0){
			insere(cod,nome,arvore);
			aux = cod;	
		}
		if (aux != cod){
			insere(cod,nome,arvore);
			aux = cod;	
		}
	}
	
	arquivo.close();
	
	system ("cls");
	
}

void escreveArquivo (TipoApontador &arvore)
{
	ofstream arquivo("Dados.txt", ios::app);
	
	if (arvore == NULL)
		return;
		
	if (arvore != NULL)
	{
		arquivo << arvore->chave <<endl;
		arquivo << arvore->nome <<endl;
	}
	arquivo.close();
		
	escreveArquivo(arvore->esq);
	
	escreveArquivo(arvore->dir);
	
}

int get_size(const char* file_name)
{
    FILE *file = fopen(file_name, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}

