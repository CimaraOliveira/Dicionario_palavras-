#include "dicionario.h"

int main(){

    Arvore arvore;
    string  significado, texto;
    string palavra;
    vector<string>palavras;
    int opcao;

    do{

        cout<<"--------------------------------------\n";
        cout<<"|            DICIONRIO               |\n";
        cout<<"--------------------------------------";
        cout<<"\n|                                    |" ;
        cout<<"\n|    1 - INSERIR                     |" ;// (no Arquivo)";
        cout<<"\n|    2 - EXIBIR PALAVRAS             |";
        cout<<"\n|    3 - PROCURAR PALAVRA            |";
        cout<<"\n|    4 - PESQUISAR POR LETRA         |";
        cout<<"\n|    5 - REMOVER PALAVRA             |";
        cout<<"\n|    6 - SAIR                        |";
        cout<<"\n|                                    |" ;
        cout<<"\n-------------------------------------";
        cout<<"\n\n  ESCOLHA UMA OPCAO: ";
        cin>>opcao;
        // cin.ignore(256,'\n');//limpa a entrada do teclado
        cout<<"--------------------------------------\n";
        switch(opcao){
        case 1:
            cout<<"--------------------------------------\n";
            cout<<"|   INSERIR PALAVRAS NO DICIONRIO     |\n";
            cout<<"--------------------------------------\n";

            cout << "\nPalavra: ";
            cin>>palavra;

            cout << "\nSignificado: ";
            cin>>significado;

            for_each(palavra.begin(),palavra.end(),[](char & c)
            {
                c=::toupper(c);
            });
            for_each(significado.begin(),significado.end(),[](char & c)
            {
                c=::toupper(c);
            });

            arvore.inicializarArvore(palavras);
            arvore.userIsere(palavra, significado);

            break;
        case 2:

            cout<<"--------------------------------------\n";
            cout<<"|   PALAVRAS DO DICIONRIO     |\n";
            cout<<"--------------------------------------\n";
            arvore.inicializarArvore(palavras);
            arvore.emOrdem(arvore.getRaiz());
            break;
        case 3://ok
            cout<<"--------------------------------------\n";
            cout<<"|  PESQUISAR PALAVRAS DO DICIONRIO     |\n";
            cout<<"--------------------------------------\n";
            cout<< "\nPalavra: ";
            cin>>palavra;
            for_each(palavra.begin(),palavra.end(),[](char & c)
            {
                c=::toupper(c);
            });

            cout<<palavra<<endl;

            arvore.inicializarArvore(palavras);
            // arvore.emOrdem(arvore.getRaiz());
            cout<<"SIGNIFICADO DA PALAVRA : ";
            cout<<arvore.buscar_ordenada(palavra,arvore.getRaiz())->getSignificado()<<endl;
            //cout<< arvore.buscar_ordenada(palavra,arvore.getRaiz())->getSignificado();

            break;
        case 4://ok
            cout<<"--------------------------------------\n";
            cout<<"|  LISTA POR LETRA NO DICIONRIO       |\n";
            cout<<"--------------------------------------\n";
            char letra,dif;
            cout<< "\nInforme uma letra: ";
            cin>>letra;
            if (letra >= 'a' && letra <= 'z')
            {
                /* sabemos que é uma letra minúscula Para converter uma letra minúscula
                para maiúsculo, como sabemos que a tabela está em ordem alfabética,
                a "distância" (diferença) do caractere minúsculo lido em letra até
                a primeira letra ('a') é a mesma de 'A' (primeira letra maiúscula)
                até o correspondente maiúsculo.*/
                dif = letra - 'a'; /* distancia até a letra a */
                letra = 'A' + dif; /* é a mesma distacia de 'A' *///USANDO A TABELA
                //  cout<<"Maiuscula: %d \n" <<letra ;
            }



            arvore.inicializarArvore(palavras);
            arvore.listar_letra(arvore.getRaiz(),letra);

            cout<<"EXISTE : "<<total<< " PALAVRAS COM A LETRA - "<<letra<<endl;
            //arvore.emOrdem(arvore.getRaiz());

            //arvore.listar_letra(c letra,palavras);


            break;
        case 5:
            cout<<"--------------------------------------\n";
            cout<<"|        REMOVER DO DICIONRIO         |\n";
            cout<<"--------------------------------------\n";
            string opc;
            cout<< "\nInforme uma palavra: ";
            cin>>palavra;
            for_each(palavra.begin(),palavra.end(),[](char & c)
            {
                c=::toupper(c);
            });//DEIXAR MAIUSCULA A PALAVRA


            arvore.inicializarArvore(palavras);
            cout<<"DESEJA REALMENTE APAGRA A PALAVRA ("<<palavra<<") ?"<<endl;
            cout<<"Informe (SIM) ou (NAO) ?"<<endl;
            cin>>opc;

            if(opc == "SIM" || opc == "sim")
            {
                arvore.remover(arvore.getRaiz(),palavra);
                arvore.emOrdem(arvore.getRaiz());

            }
            else
            {
                cout<<"PALAVRA NAO SERA REMOVIDA!"<<endl;

            }


            break;

        }
    }
    while(opcao < 6);

    return 0;
}

