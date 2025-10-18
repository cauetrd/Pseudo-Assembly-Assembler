#include <bits/stdc++.h>
using namespace std;

map<string, int> opcode = {
    {"ADD", 1}, {"SUB", 2}, {"MULT", 3}, {"DIV", 4}, {"JMP", 5}, {"JMPN", 6}, {"JMPP", 7}, {"JMPZ", 8}, {"COPY", 9}, {"LOAD", 10}, {"STORE", 11}, {"INPUT", 12}, {"OUTPUT", 13}, {"STOP", 14}};

vector<string> instrucoes = {
    "ADD", "SUB", "MULT", "DIV", "JMP", "JMPN", "JMPP", "JMPZ",
    "COPY", "LOAD", "STORE", "INPUT", "OUTPUT", "STOP"};

map<string, int> mnt; //mapeia o nome da macro para a linha da mdt que o corpo dela começa
vector<string> mdt; 

struct Simbolo
{
    string nome;
    int valor;
    int pendencia;
};

vector<Simbolo> tabela_simbolos;


string normalizaExpressao(string &linha) {
    string resultado = "";
    
    for (int i = 0; i < linha.size(); i++) {
        char atual = linha[i];
        

        if (atual == '+' || atual == '-') {
            while (!resultado.empty() && resultado.back() == ' ') {
                resultado.pop_back();
            }
            
 
            resultado += " ";
            resultado += atual;
            resultado += " ";
            

            while (i + 1 < linha.size() && linha[i + 1] == ' ') {
                i++;
            }
        } else if (atual == ',') {

            while (!resultado.empty() && resultado.back() == ' ') {
                resultado.pop_back();
            }
            

            resultado += ", ";
            

            while (i + 1 < linha.size() && linha[i + 1] == ' ') {
                i++;
            }
        } else {
            resultado += atual;
        }
    }
    
    return resultado;
}


bool verificaErroLabel(string label)
{
    if (isdigit (label[0])){
        return true;
    }
    for (char carac : label){
        if (!isdigit(carac) && !isalpha(carac) && !(carac=='_')){
            return true;
        }
    }
    return false;
}

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

string tiraVirgula (string arg){
    int temVirgula = achaChar(arg, ',');
    if (temVirgula == arg.size()-1){
        arg = arg.substr(0, arg.size() - 1);
    }
    return arg;
}

vector<string> getTokens(string &linha)
{
    vector<string> tokens;
    int token_inicio = 0;
    while (token_inicio < linha.size())
    {
        string current_str = linha.substr(token_inicio);

        int pos_space = achaChar(current_str, ' ');
        int pos_tab   = achaChar(current_str, '\t');
        int pos_sep;
        if (pos_space == -1 && pos_tab == -1)
        {
            if (!current_str.empty())
                tokens.push_back(current_str);
            break;
        }
        else if (pos_space == -1)
        {
            pos_sep = pos_tab;
        }
        else if (pos_tab == -1)
        {
            pos_sep = pos_space;
        }
        else
        {
            pos_sep = min(pos_space, pos_tab);
        }
        if (pos_sep > 0){
            tokens.push_back(current_str.substr(0, pos_sep));
        }
        token_inicio += pos_sep + 1;
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

vector<string> expandeMacro(string &nome, vector<string> argumentos)
{
    vector<string> macroExpandida;
    if (mnt.find(nome) == mnt.end()){
        return macroExpandida;
    }
    int pos_mdt = mnt[nome];
    string linha_expandida = mdt[pos_mdt];

    while (linha_expandida != "ENDMACRO"){
        string linha = linha_expandida;
        
        for (int arg = 0; arg < argumentos.size(); arg++){
            string local_arg = "#" + to_string(arg + 1);

            vector<string> tokens = getTokens(linha);
            for (int j = 0; j < tokens.size(); j++){
                if (tokens[j] == local_arg){
                    tokens[j] = argumentos[arg];
                }
            }
            linha = juntaTokens(tokens);
        }
        
        vector<string> tokens_expandida = getTokens(linha);


        if (!tokens_expandida.empty()){
            string primeiro_token = tokens_expandida[0];
            int offset = 0;
            
            if (primeiro_token.size() > 0 && primeiro_token[primeiro_token.size() - 1] == ':'){
                if (tokens_expandida.size() > 1){
                    primeiro_token = tokens_expandida[1];
                    offset = 1;
                }
                else{

                    macroExpandida.push_back(linha);
                    pos_mdt++;
                    if (pos_mdt >= mdt.size()) break;
                    linha_expandida = mdt[pos_mdt];
                    continue;
                }
            }
            
           
            auto busca_instrucao = find(instrucoes.begin(), instrucoes.end(), primeiro_token);
            if (busca_instrucao == instrucoes.end() && mnt.find(primeiro_token) != mnt.end()){
                
                vector<string> args_macro;
                for (int i = 1 + offset; i < tokens_expandida.size(); i++){
                    string arg = tokens_expandida[i];
                    arg = tiraVirgula(arg);
                    args_macro.push_back(arg);
                }
                
                vector<string> macro_recursiva = expandeMacro(primeiro_token, args_macro);
                
                if (offset > 0){
                    if (!macro_recursiva.empty()){
                        macro_recursiva[0] = tokens_expandida[0] + " " + macro_recursiva[0];
                    }

                    else{
            
                        macroExpandida.push_back(tokens_expandida[0]);
                    }

                }
                

                for (string linha_rec : macro_recursiva){
                    macroExpandida.push_back(linha_rec);
                }
            }

            else{
                macroExpandida.push_back(linha);
            }
        }
        else{
            macroExpandida.push_back(linha);
        }
        
        pos_mdt++;
        if (pos_mdt >= mdt.size()){
            break;
        }
        linha_expandida = mdt[pos_mdt];
    }
    return macroExpandida;
}

vector<string> expandeTodasMacros(vector<string> cod)
{
    vector<string> expanded_code;
    int linha_mdt = 0;
    bool macro = false;
    vector<string> argumentos;
    for (string linha : cod)
    {
        vector<string> tokensMacro = getTokens(linha);
        if (macro)
        {
            for (int i = 0; i < argumentos.size(); i++)
            {
                string arg = argumentos[i];
                arg = tiraVirgula(arg);
                string arg_positional = "#" + to_string(i + 1);
                vector<string> tokens = getTokens(linha);
                for (int j = 0; j < tokens.size(); j++)
                {
                    if (tokens[j] == arg)
                    {
                        tokens[j] = arg_positional;
                    }
                }
                linha = juntaTokens(tokens);
            }
            mdt.push_back(linha);
            linha_mdt++;
            if (!tokensMacro.empty() && tokensMacro[0] == "ENDMACRO")
            {
                macro = false;
                argumentos.clear();
            }
        }
        else
        {
            if (tokensMacro.empty())
                continue;
            string primeiroToken = tokensMacro[0];
            if (tokensMacro.size() > 1 && tokensMacro[1] == "MACRO")
            {
                string nomeLabel = primeiroToken.substr(0, primeiroToken.size() - 1);
                mnt.insert({nomeLabel, linha_mdt});
                macro = true;
                argumentos.clear();
                for (int i = 2; i < tokensMacro.size(); i++)
                {
                    string current_arg = tokensMacro[i];
                    current_arg = tiraVirgula(current_arg);
                    argumentos.push_back(current_arg);
                }
            }
            else
            {
                string tokenBusca;
                int label_def = 0;
                if (primeiroToken[primeiroToken.size() - 1] == ':')
                {
                    if (tokensMacro.size() > 1)
                    {
                        tokenBusca = tokensMacro[1];
                        label_def = 1;
                    }
                    else
                    {
                        expanded_code.push_back(linha);
                        continue;
                    }
                }
                else
                {
                    tokenBusca = tokensMacro[0];
                }
                auto buscaInstrucao = find(instrucoes.begin(), instrucoes.end(), tokenBusca);
                if (buscaInstrucao != instrucoes.end())
                {
                    expanded_code.push_back(linha);
                }
                else
                {
                    if (mnt.find(tokenBusca) != mnt.end())
                    {
                        vector<string> local_args;
                        for (int j = 1 + label_def; j < tokensMacro.size(); j++)
                        {
                            string current_arg = tokensMacro[j];
                            current_arg = tiraVirgula (current_arg);
                            local_args.push_back(current_arg);
                        }
                        vector<string> linha_expandida = expandeMacro(tokenBusca, local_args);
                        for (string linha : linha_expandida)
                        {
                            expanded_code.push_back(linha);
                        }
                        argumentos.clear();
                    }
                    else
                    {
                        expanded_code.push_back(linha);
                    }
                }
            }
        }
    }
    return expanded_code;
}
vector<string> preProcessamento(vector<string> codigo)
{
    vector<string> codigoExpandido;
    string label;
    for (string linha : codigo)
    {
        maisculas(linha);
        tiraComentario(linha);
        

        linha = normalizaExpressao(linha);
        
        vector<string> tokens = getTokens(linha);
        linha = juntaTokens(tokens);
        if (linha.empty()) {
            continue;
        }
        string primeiroToken = tokens[0];
        if (tokens.size() == 1 && primeiroToken.size() > 0 && primeiroToken[primeiroToken.size()-1] == ':')
        {
            label += tokens[0] + " ";
            continue;
        }
        if (!label.empty())
        {
            linha = label + linha;
            label = "";
        }
        codigoExpandido.push_back(linha);
    }
    if (!label.empty()){
        codigoExpandido.push_back(label);
    }
    codigoExpandido = expandeTodasMacros(codigoExpandido);
    return codigoExpandido;
}

vector<int> o2(vector<int> codigoPendencias, vector<string> &pre)
{
    vector<int> codigoResolvido = codigoPendencias;
    int prox_pendencia;
    for (Simbolo s : tabela_simbolos)
    {
        prox_pendencia = s.pendencia;
        if (s.valor == -1)
        {
            while (prox_pendencia != -1)
            {
                int temp = codigoResolvido[prox_pendencia];
                codigoResolvido[prox_pendencia] = s.valor;
                pre[prox_pendencia] += " erro semântico";
                prox_pendencia = temp;
            }
        }
        else
        {
            while (prox_pendencia != -1)
            {
                int temp = codigoResolvido[prox_pendencia];
                codigoResolvido[prox_pendencia] = s.valor;
                prox_pendencia = temp;
            }
        }
    }
    return codigoResolvido;
}

int main(int argc, char *argv[])
{
    string nome_arquivo_entrada = argv[1];
    ifstream arquivo(nome_arquivo_entrada);
    vector<string> codigo;
    string linha;
    while (getline(arquivo, linha))
    {
        codigo.push_back(linha);
    }
    arquivo.close();
    vector<string> codigoExpandido = preProcessamento(codigo);
    /*string nome_arquivo_pre = nome_arquivo_entrada;
    size_t extensao = nome_arquivo_pre.find_last_of(".");
    if (extensao != std::string::npos) {
        nome_arquivo_pre = nome_arquivo_pre.substr(0, extensao); 
    }*/
    /*nome_arquivo_pre += ".pre";
    ofstream saida_pre(nome_arquivo_pre);*/  

    /*for (string linha : codigoExpandido){
        saida_pre << linha;
        saida_pre <<"\n";
    }
    saida_pre.close();*/
    for (string linha : codigoExpandido)
    {
        cout << linha << "\n";
    }
    return 0;
}