// Lendo um arquivo de texto
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;


void gotoxy(int x, int y);
void desligaCursor();
void HabilitarCoresANSI();


void setCorRGB(int r, int g, int b, int R, int G, int B, string texto)
{
    // Formato ANSI para TrueColor RGB: \033[38;2;R;G;B;48;2;R;G;Bm texto \033[0m
    // \033: É o caractere de Escape (ESC) em octal;
    // [: É o caractere de colchete que, junto com o \033, forma o CSI (Control Sequence Introducer). É o gatilho padrão para a maioria dos comandos ANSI
    // 38: Informa ao terminal que você deseja alterar a cor do texto (frente)
    // 2: Especifica o modo de cor TrueColor (24 bits), permitindo usar a escala RGB de 0 a 255.
    // R ; G ; B: São as variáveis com os valores de Vermelho (Red), Verde (Green) e Azul (Blue) para o texto, separados por ponto e vírgula.
    // 48: Informa ao terminal que você deseja alterar a cor do fundo (background).
    // 2: Novamente, especifica o modo TrueColor (24 bits) para o fundo.
    // R ; G ; B: São as variáveis com os valores RGB para a cor de fundo.
    // m: É a letra que indica o fim da sequência de comandos de estilo gráfico (Select Graphic Rendition). Tudo o que foi configurado antes do m é aplicado a partir desse ponto.
    // texto: É a string que você passou como argumento e que será exibida com as cores que você acabou de configurar.
    // \033[0m: Este trecho no final é fundamental. O comando 0m diz ao terminal para restaurar o padrão original (limpar todas as cores e estilos). Se você não colocar isso, todo o texto que o terminal imprimir depois do seu programa continuará com a cor do fundo e do texto que você configurou.

    cout << "\033[38;2;" << r << ";" << g << ";" << b << ";48;2;" << R <<";"<<G<<";"<<B<< "m" << texto << "\033[0m";
}

int main ()
{
    int x = 41;
    int y = 9;
    string linha; //Variável que receberá a linha a ser lida
    ifstream meuArquivo ("piramide.txt"); // Declara a variável e abre o arquivo exemplo.txt
    if (meuArquivo.is_open()) //Verifica que o arquivo foi aberto
    {
        while ( getline (meuArquivo,linha) ) //A condição de parada do while é quando o getline encontra o EOF(EndOf File)
        {
            gotoxy(x,y++);
            setCorRGB(252,250,80,97,92,54, linha );
        }
        meuArquivo.close(); //Fecha o arquivo
    }
    else
        cout<< "Nao foi possivel abrir o arquivo"; //Caso não tenha sido aberto o arquivo imprime a mensagem de erro.
    gotoxy(0,0);
    return 0;
}



void gotoxy(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

void desligaCursor(){
    CONSOLE_CURSOR_INFO ConCurInf; //este é o objeto que configura o cursor
    ConCurInf.dwSize = 10; //este é o tamanho do cursor, que vai de 0% a 100%
    ConCurInf.bVisible = FALSE; //este atributo o deixa visivel ou não
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConCurInf);
}
void HabilitarCoresANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;

    if (hOut == INVALID_HANDLE_VALUE){
        return;
    }

    if (GetConsoleMode(hOut, &dwMode))
    {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
}

// Define a cor do texto usando valores RGB


