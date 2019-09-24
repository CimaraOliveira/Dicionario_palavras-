#ifndef DICIONARIO_H_INCLUDED
#define DICIONARIO_H_INCLUDED
#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <locale.h>
#include <array>
#include <vector>
#include <ctype.h>


int total=0;

using namespace std;


class No //criando a classe no informaçoes do no
{
private:
    No *esq, * dir; //guardar no a esq e a direita
    string palavra; //chave
    string significado;//conteudo

public:
    //construtor
    No(string palavra, string significado)
    {
        this->palavra = palavra;
        this->significado = significado;
        esq = NULL; //criando o no folha
        dir = NULL;
    }

    //metodos para retornar a chave
    string getPalavra()
    {
        return palavra;
    }

    void setPalavra(string palavra)
    {
        this->palavra=palavra;
    }

    string getSignificado()
    {
        return significado;
    }

    void setSignificado(string significado)
    {
        this->significado=significado;
    }


    //metodos que vai retornar o no a esquerda
    No * getEsq()
    {
        return esq;
    }

      //metodos que vai retornar o no a direita
    No* getDir()
    {
        return dir;
    }

    //setando no a esquerda e a direita
    void setEsq(No* no)
    {
        esq = no;
    }

    void setDir(No* no)
    {
        dir = no;
    }
};

class Arvore //classe onde fica a raiz
{
private:
    No* raiz; //no raiz

public:
    Arvore() //construtor
    {
        raiz = NULL;
    }


    No* getRaiz()
    {
        return raiz;
    }

    void setRaiz(No *raiz)
    {
        this->raiz = raiz;
    }



    /*************************************************************************************************/
    /****************************FUNÇAO INSERIR*******************************************************/
    /*************************************************************************************************/


    void inserir(string palavra, string significado) //funcao para inserir passando a palavra e o significado
    {
        if(raiz == NULL) // arvore vazia
            raiz = new No(palavra,significado); //cria novo no passando a chave
        else
            inserirAux(raiz,palavra,significado); //insere no na raiz e verifica onde insere o no

    }

    void inserirAux(No *no,string palavra, string significado)//passamos o no de onde vamos comecar e a chave
    {
        if(palavra < no->getPalavra()) //se a palavra for menor que o no corrente
        {
            if(no->getEsq() == NULL) //verifica se tem um no a esquerda
            {
                No *novo_no = new No(palavra,significado); //cria um nono no
                no->setEsq(novo_no); //seta o no a esquerda insere

            }
            else
            {
                inserirAux(no->getEsq(),palavra,significado); //se tiver no a esquerda continua  busca no no a esquerda
            }
            //inserir(no->getDir());
        }
        else if(palavra > no->getPalavra())//se a palavra chave for maior
        {
            if(no->getDir() ==NULL) //verifica se tem no a direita
            {
                No*novo_no = new No(palavra,significado); //cria um novo no
                no->setDir(novo_no); //insere o no a direita do no corrente
            }
            else
            {
                inserirAux(no->getDir(),palavra,significado); //insere o no a direita
            }
        }
    }

// *********************************************************************************************
    /*************************************************************************************************/
    /****************************FUNÇAO BUSCAR*******************************************************/
    /*************************************************************************************************/


    No* buscar_ordenada(string palavra, No* no) //passando a palavra chave e o no
    {
        if(no==NULL || no->getPalavra().compare(palavra) == 0) //no for igual a null e no corrente  comparando a palavra for igual a zero
        {
            return no; //retorna o no

        }
        if(no->getPalavra().compare(palavra) < 0) //compara a menor palavra se a palavra chave for menor que zero
        {
            return buscar_ordenada(palavra,no->getDir()); //ordena a direita
        }
        else if(no->getPalavra().compare(palavra)> 0) //compara a maior palavra se a chave for maior que zero
        {
            return buscar_ordenada(palavra,no->getEsq()); //ordena a esquerda
        }
    }

// **********************************************************************************************
    /*************************************************************************************************/
    /****************************FUNÇAO LEITURA DE ARQUIVO*******************************************/
    /*************************************************************************************************/

    vector <string> leituraDeArquivo(string nome,vector<string> palavras)//funcionando nao mecha
    {

        string linha = "";
        ifstream arq_in(nome);
        // int i=0;

        if(arq_in.is_open())
        {
            //eof() - retorna true ao atingir o fim do arquivo
            while(! arq_in.eof())
            {
                getline (arq_in, linha);

                for_each(linha.begin(),linha.end(),[](char & c)
                {
                    c=::toupper(c);
                });

                palavras.push_back(linha);

            }
            arq_in.close();

        }
        else
        {
            cout << "ERRO: arquivo não foi aberto ou não existe" << endl;
        }

        return palavras; //retornar o vetor de palavras

    }

    /*************************************************************************************************/
    /****************************FUNÇAO INICIALIZAR ARVORE*******************************************************/
    /*************************************************************************************************/
    void inicializarArvore(vector <string> palavras) //funcionando nao mecha
    {

        palavras = leituraDeArquivo("palavras.txt",palavras); //vetor de palavras vai receber o arquivo txt
        string str; //vetor de string
        string palavra;//chave
        string significado;//conteudo

        int tamanho= palavras.size();//tamanho do meu vector

        for(int i=0; i<tamanho; i++){

            str = palavras[i];

            int proxima,length;
            proxima = str.find("\t",0);

            palavra = str.substr(0,proxima);//aqui pega o que tem antes do barra t;


            length = proxima+1;
            proxima = str.find("\t",length);

            significado=str.substr(length,proxima-length);//aqui pega depois do barra t

            //cout<<palavra<<endl;
            //cout<<significado<<endl;

            inserir(palavra,significado); //inserindo palavra e significado no arquivo


        }
        palavras.clear();//limpar array

    }
    /*************************************************************************************************/
    /****************************FUNÇAO EM ORDEM*******************************************************/
    /*************************************************************************************************/

    void emOrdem(No* no){
        if(no != NULL){
            emOrdem(no->getEsq());/*desce a sub árvore da esquerda dos nós até que a sub árvore da esquerda for vazia (NULL) */
            cout << no->getPalavra()+ "\t"+ no->getSignificado()<<endl;/*Para cada nó que visitou a sub árvore da esquerda volta a visita o nó e desce a sub árvore da direita*/
            emOrdem(no->getDir());/*nesse momento passa a visitar os nós e depois visita a sub árvore da direita até que esteja vazia.*/
        }
    }

    /*************************************************************************************************/
    /****************************FUNÇAO USUARIO INSERIR**********************************************/
    /***********************************************************************************************/


    void userIsere(string palavra,string significado){//inserindo ordenado
        if( buscar_ordenada(palavra,this->raiz)== NULL)  //se palavra e raiz == null
        {

            inserir(palavra,significado); //insere a palavra e o significado
            cout<<" Inserido com sucesso!"<<endl;
        }
        else
        {
            cout<<"Existe!"<<endl;

        }

    }

    /*************************************************************************************************/
    /****************************FUNÇAO LISTAR POR LETRA***********************************************/
    /*************************************************************************************************/

    void listar_letra(No *no,char letra){

        if(no != NULL)
        {
            listar_letra(no->getEsq(),letra);/*desce a sub árvore da esquerda dos nós até que a sub árvore da esquerda for vazia (NULL) */
            string aux = no->getPalavra(); //aux recebe no corrente palavra
            if(letra == aux[0])
            {
                cout << no->getPalavra()+ "\t"+ no->getSignificado()<<endl;/*Para cada nó que visitou a sub árvore da esquerda volta a visita o nó e desce a sub árvore da direita*/
                total++;
            }

            listar_letra(no->getDir(),letra);/*nesse momento passa a visitar os nós e depois visita a sub árvore da direita até que esteja vazia.*/
        }

    }
    /*************************************************************************************************/
    /****************************FUNÇAO ARVORE COMPLETA***********************************************/
    /*************************************************************************************************/

 void arvoreCompleta(vector <string> palavras){
        palavras = leituraDeArquivo("palavras.txt",palavras);

        Arvore *a;

        int tam = palavras.size();

        cout<<tam<<endl;
        if(tam %2==0)
        {
            cout<<tam-1<<endl;
        }
        else
        {
            cout<<"errp";

        }



    }
    /*************************************************************************************************/

    /*************************************************************************************************/
    /****************************FUNÇAO MENOR VALOR*******************************************************/
    /*************************************************************************************************/


    No* minValor(No* no){
        No* atual = no;

        /* Procurar folha aesquerda menor */
        while (atual && atual->getEsq() != NULL)
            atual = atual->getEsq();
        cout<<atual->getEsq();

        return atual;
    }
    /*************************************************************************************************/
    /****************************FUNÇAO REMOVER*******************************************************/
    /*************************************************************************************************/
    No* remover(No* no, string palavra) //remover no e palavra
     {
        if (no == NULL) //se no= null
            return no; //retorna no
        else if (palavra.compare(no->getPalavra()) < 0) //se palavra comparando o no corrente for menor que zero
            no->setEsq(remover(no->getEsq(),palavra)); //no setando a esquerda remove no a esquerda
        else if (palavra.compare(no->getPalavra()) > 0)//se palavra comparando o no corrente for maior que zero
            no->setDir( remover(no->getDir(),palavra));//no setando a direita remove no a direita
        else
        {
            //no sem filho
            if (no->getEsq() == NULL && no->getDir() == NULL) //no a esquerda for igual a null e no a direita == a null
            {
                delete no; //deleta nó
                no = NULL; //no recebe null
                return no; //retornara ao no
            }
            // No com filho a direita
            else if (no->getEsq() == NULL) //compara o no da esquerda
            {
                No* temp = no; // variavel auxiliar tmpp recebe no
                no = no->getDir(); // no é igual a no da direita
                delete temp;
                return no;
            }
            // No com filho a esquerda
            else if (no->getDir() == NULL) //compara o no da direita
            {
                No* temp = no;
                no = no->getEsq();
                delete temp;
                return no;
            }
            else// No com dois filhos
            {
                No* temp = minValor(no->getDir());
                no->setPalavra(temp->getPalavra());
                no->setDir( remover(no->getDir(), temp->getPalavra()));
            }
        }
        return no;
    }
};

#endif // DICIONARIO_H_INCLUDED
