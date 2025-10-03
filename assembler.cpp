#include <bits/stdc++.h>
using namespace std;

map<string, int> opcode = {
    {"ADD", 1}, {"SUB", 2}, {"MULT", 3}, {"DIV", 4}, {"JMP", 5}, {"JMPN", 6}, {"JMPP", 7}, {"JMPZ", 8}, {"COPY", 9}, {"LOAD", 10}, {"STORE", 11}, {"INPUT", 12}, {"OUTPUT", 13}, {"STOP", 14}};

vector<string> instrucoes = {
        "ADD", "SUB", "MULT", "DIV", "JMP", "JMPN", "JMPP", "JMPZ",
        "COPY", "LOAD", "STORE", "INPUT", "OUTPUT", "STOP"
};
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

void expand_arguments_macro ();
vector<string> expandMacros(vector<string> cod)
{
    vector<string> expanded_code;
    int linha_mdt = 0;
    bool macro = false;
    vector <string> argumentos;
    for (string linha : cod)
    {
        vector<string> tokensMacro = getTokens(linha);
        if (macro){
            mdt[linha_mdt] = tokensMacro[0];
            linha_mdt++;
            if (tokensMacro[0]=="ENDMACRO"){
                macro=false;
            }
        }
        else {
            string primeiroToken = tokensMacro[0];
            if (tokensMacro[1]=="MACRO")
            {
                string nomeLabel = primeiroToken.substr(0, primeiroToken.size() - 1);
                mnt.insert({nomeLabel, linha_mdt});
                    macro= true;        
                for (int i=2; i<tokensMacro.size(); i++){
                    argumentos.push_back(tokensMacro[i]);
                }
            }
            else {
                string tokenBusca;
                if (primeiroToken[primeiroToken.size() - 1] == ':'){
                    tokenBusca= tokensMacro[1];
                }
                else {
                    tokenBusca = tokensMacro[0];
                }
                auto busca = find(instrucoes.begin(), instrucoes.end(), tokenBusca);
                if (busca != instrucoes.end()) {
                    expanded_code.push_back(linha);
                } 
                else {
                    if (mnt.find(labelName) != mnt.end()) {
                        int pos_mdt=mnt.find(labelName);
                        string expand_linha = mdt  [pos_mdt];
                        while (expand_linha!="ENDMACRO"){
                            
                        }
                    } 
                    else {
                        expanded_code.push_back(linha);
                    }                 
                }
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
