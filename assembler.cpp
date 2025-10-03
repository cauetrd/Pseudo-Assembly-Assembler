#include <bits/stdc++.h>
using namespace std;

map<string, int> opcode = {
    {"ADD", 1}, {"SUB", 2}, {"MULT", 3}, {"DIV", 4}, {"JMP", 5}, {"JMPN", 6}, {"JMPP", 7}, {"JMPZ", 8}, {"COPY", 9}, {"LOAD", 10}, {"STORE", 11}, {"INPUT", 12}, {"OUTPUT", 13}, {"STOP", 14}};

map<string, int> mnt;
vector<string> mdt;

void maisculas(string &linha)
{
    for (auto &letra : linha)
    {
        letra = toupper(letra);
    }
}

int achaChar(string &str, char carac)
{
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == carac)
        {
            return i;
        }
    }
    return -1;
}

vector<string> getTokens(string &linha)
{
    vector<string> tokens;
    int token_inicio = 0;
    int pos_espaco = achaChar(linha, ' ');
    while (pos_espaco != -1)
    {
        if (!(linha.substr(token_inicio, pos_espaco - token_inicio)).empty())
        {
            tokens.push_back(linha.substr(token_inicio, pos_espaco - token_inicio));
        }
        token_inicio = pos_espaco + 1;
        string prox_string = linha.substr(token_inicio);
        int prox_espaco = achaChar(prox_string, ' ');
        if (prox_espaco != -1)
        {
            pos_espaco = token_inicio + prox_espaco;
        }
        else
        {
            pos_espaco = -1;
        }
    }
    if (!(linha.substr(token_inicio)).empty())
    {
        tokens.push_back(linha.substr(token_inicio));
    }
    return tokens;
}

string juntaTokens(vector<string> tokens)
{
    string resultado = "";
    for (int i = 0; i < tokens.size(); i++)
    {
        resultado += tokens[i];
        if (i < tokens.size() - 1)
        {
            resultado += " ";
        }
    }
    return resultado;
}

void tiraComentario(string &linha)
{
    int pos_comentario = achaChar(linha, ';');
    if (pos_comentario != -1)
    {
        linha = linha.substr(0, pos_comentario);
    }
}
vector<string> expandMacros(vector<string> cod)
{
    int linha_mdt = 0;
    bool macro = false;
    for (string linha : cod)
    {
        vector<string> tokensMacro = getTokens(linha);
        string primeiroToken = tokensMacro[0];
        if (primeiroToken[primeiroToken.size() - 1] == ':')
        {
            string nomeLabel = primeiroToken.substr(0, primeiroToken.size() - 1);
            if (tokensMacro[1] == "MACRO")
            {
                mnt.insert({nomeLabel, linha_mdt});
            }
        }
    }
}
vector<string> preProcessamento(vector<string> codigo)
{
    vector<string> codigoExpandido;
    for (string linha : codigo)
    {
        maisculas(linha);
        tiraComentario(linha);
        vector<string> tokens = getTokens(linha);
        linha = juntaTokens(tokens);
        if (!linha.empty())
        {
            codigoExpandido.push_back(linha);
        }
    }
    return codigoExpandido;
}

int main(int argc, char *argv[])
{
    string nome_arquivo = argv[1];
    ifstream arquivo(nome_arquivo);
    vector<string> codigo;
    string linha;
    while (getline(arquivo, linha))
    {
        codigo.push_back(linha);
    }
    arquivo.close();
    vector<string> codigoExpandido = preProcessamento(codigo);

    for (const string &linha : codigoExpandido)
    {
        cout << linha << "\n";
    }
    return 0;
}
