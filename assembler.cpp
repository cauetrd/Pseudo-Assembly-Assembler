#include <bits/stdc++.h>
using namespace std;

map<string, int> opcode = {
    {"ADD", 1}, {"SUB", 2}, {"MULT", 3}, {"DIV", 4}, {"JMP", 5}, {"JMPN", 6}, {"JMPP", 7}, {"JMPZ", 8}, {"COPY", 9}, {"LOAD", 10}, {"STORE", 11}, {"INPUT", 12}, {"OUTPUT", 13}, {"STOP", 14}};

vector<string> instrucoes = {
    "ADD", "SUB", "MULT", "DIV", "JMP", "JMPN", "JMPP", "JMPZ",
    "COPY", "LOAD", "STORE", "INPUT", "OUTPUT", "STOP"};

map<string, int> mnt; //mapeia o nome da macro para a linha da mdt que o corpo dela começa
vector<string> mdt; 
int soma_nas_variaveis[10000];
map<int, int> endereco_para_linha_pre; // mapeia endereco da pendencia para linha do arquivo .pre

struct Simbolo
{
    int endereco;
    int pendencia;
};

map<string,Simbolo> tabela_simbolos;

string normalizaExpressao(string &linha)
{
    string resultado = "";

    for (int i = 0; i < linha.size(); i++)
    {
        char atual = linha[i];

        if (atual == '+')
        {
            while (!resultado.empty() && resultado.back() == ' ')
            {
                resultado.pop_back();
            }

            resultado += " ";
            resultado += atual;
            resultado += " ";

            while (i + 1 < linha.size() && linha[i + 1] == ' ')
            {
                i++;
            }
        }
        else if (atual == ',')
        {

            while (!resultado.empty() && resultado.back() == ' ')
            {
                resultado.pop_back();
            }

            resultado += ", ";

            while (i + 1 < linha.size() && linha[i + 1] == ' ')
            {
                i++;
            }
        }
        else
        {
            resultado += atual;
        }
    }

    return resultado;
}

bool verificaErroLabel(string label)
{
    if (isdigit(label[0]))
    {
        return true;
    }
    for (char carac : label)
    {
        if (!isdigit(carac) && !isalpha(carac) && !(carac == '_'))
        {
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

string tiraVirgula(string arg)
{
    int temVirgula = achaChar(arg, ',');
    if (temVirgula == arg.size() - 1)
    {
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
        int pos_tab = achaChar(current_str, '\t');
        int pos_cr = achaChar(current_str, '\r');
        int pos_sep;
        if (pos_space == -1 && pos_tab == -1 && pos_cr == -1)
        {
            if (!current_str.empty())
                tokens.push_back(current_str);
            break;
        }
        else if (pos_space == -1 && pos_tab == -1)
        {
            pos_sep = pos_cr;
        }
        else if (pos_space == -1 && pos_cr == -1)
        {
            pos_sep = pos_tab;
        }
        else if (pos_tab == -1 && pos_cr == -1)
        {
            pos_sep = pos_space;
        }
        else if (pos_space == -1)
        {
            pos_sep = min(pos_tab, pos_cr);
        }
        else if (pos_tab == -1)
        {
            pos_sep = min(pos_space, pos_cr);
        }
        else if (pos_cr == -1)
        {
            pos_sep = min(pos_space, pos_tab);
        }
        else
        {
            pos_sep = min({pos_space, pos_tab, pos_cr});
        }
        if (pos_sep > 0)
        {
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
    if (mnt.find(nome) == mnt.end())
    {
        return macroExpandida;
    }
    int pos_mdt = mnt[nome];
    string linha_expandida = mdt[pos_mdt];

    while (linha_expandida != "ENDMACRO")
    {
        string linha = linha_expandida;

        for (int arg = 0; arg < argumentos.size(); arg++)
        {
            string local_arg = "#" + to_string(arg + 1);

            vector<string> tokens = getTokens(linha);
            for (int j = 0; j < tokens.size(); j++)
            {
                string limpa_token = tiraVirgula(tokens[j]);
                if (limpa_token == local_arg)
                {
                    if (tokens[j] != limpa_token)
                    {
                        tokens[j] = argumentos[arg] + ",";
                    }
                    else
                    {
                        tokens[j] = argumentos[arg];
                    }
                }
            }
            linha = juntaTokens(tokens);
        }

        vector<string> tokens_expandida = getTokens(linha);
        if (!tokens_expandida.empty())
        {
            string primeiro_token = tokens_expandida[0];
            int offset = 0;

            if (primeiro_token.size() > 0 && primeiro_token[primeiro_token.size() - 1] == ':')
            {
                if (tokens_expandida.size() > 1)
                {
                    primeiro_token = tokens_expandida[1];
                    offset = 1;
                }
                else
                {

                    macroExpandida.push_back(linha);
                    pos_mdt++;
                    if (pos_mdt >= mdt.size())
                        break;
                    linha_expandida = mdt[pos_mdt];
                    continue;
                }
            }

            auto busca_instrucao = find(instrucoes.begin(), instrucoes.end(), primeiro_token);
            if (busca_instrucao == instrucoes.end() && mnt.find(primeiro_token) != mnt.end())
            {

                vector<string> args_macro;
                for (int i = 1 + offset; i < tokens_expandida.size(); i++)
                {
                    string arg = tokens_expandida[i];
                    arg = tiraVirgula(arg);
                    args_macro.push_back(arg);
                }

                vector<string> macro_recursiva = expandeMacro(primeiro_token, args_macro);

                if (offset > 0)
                {
                    if (!macro_recursiva.empty())
                    {
                        macro_recursiva[0] = tokens_expandida[0] + " " + macro_recursiva[0];
                    }

                    else
                    {

                        macroExpandida.push_back(tokens_expandida[0]);
                    }
                }

                for (string linha_rec : macro_recursiva)
                {
                    macroExpandida.push_back(linha_rec);
                }
            }

            else
            {
                macroExpandida.push_back(linha);
            }
        }
        else
        {
            macroExpandida.push_back(linha);
        }

        pos_mdt++;
        if (pos_mdt >= mdt.size())
        {
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
            vector<string> tokens = getTokens(linha);
            if (tokens.empty())
            {
                continue;
            }
            for (int i = 0; i < argumentos.size(); i++)
            {
                string arg = argumentos[i];
                arg = tiraVirgula(arg);
                string arg_positional = "#" + to_string(i + 1);
                tokens = getTokens(linha);
                for (int j = 0; j < tokens.size(); j++)
                {
                    string limpa_token = tiraVirgula(tokens[j]);
                    if (limpa_token == arg)
                    {
                        if (tokens[j] != limpa_token)
                        {
                            tokens[j] = arg_positional + ",";
                        }
                        else
                        {
                            tokens[j] = arg_positional;
                        }
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
                    string arg_atual = tokensMacro[i];
                    arg_atual = tiraVirgula(arg_atual);
                    argumentos.push_back(arg_atual);
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
                            current_arg = tiraVirgula(current_arg);
                            local_args.push_back(current_arg);
                        }
                        vector<string> linha_expandida = expandeMacro(tokenBusca, local_args);
                        if (label_def == 1)
                        {
                            if (!linha_expandida.empty())
                            {
                                expanded_code.push_back(tokensMacro[0] + " " + linha_expandida[0]);
                                for (int i = 1; i < linha_expandida.size(); i++)
                                {
                                    expanded_code.push_back(linha_expandida[i]);
                                }
                            }
                            else
                            {
                                expanded_code.push_back(tokensMacro[0]);
                            }
                        }
                        else
                        {
                            for (string linha : linha_expandida)
                            {
                                expanded_code.push_back(linha);
                            }
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
        vector<string> tokens = getTokens(linha); // tira espaços em branco, tabs e enters
        linha = juntaTokens(tokens);
        if (linha.empty())
        {
            continue;
        }
        string primeiroToken = tokens[0];
        if (tokens.size() == 1 && primeiroToken.size() > 0 && primeiroToken[primeiroToken.size() - 1] == ':')
        {
            label += tokens[0] + " ";
            continue;
        }
        if (!label.empty())
        {
            if (primeiroToken != "ENDMACRO")
            {
                linha = label + linha;
                label = "";
            }
            else
            {
                codigoExpandido.push_back(label.substr(0, label.size() - 1));
                label = "";
            }
        }
        codigoExpandido.push_back(linha);
    }
    if (!label.empty())
    {
        codigoExpandido.push_back(label.substr(0, label.size() - 1));
    }
    codigoExpandido = expandeTodasMacros(codigoExpandido);
    for (int i = 0; i < codigoExpandido.size(); ++i)
    {
        codigoExpandido[i] = normalizaExpressao(codigoExpandido[i]);
    }
    vector<string> codigoFinal;
    string label_final;
    for (string linha : codigoExpandido)
    {
        vector<string> tokens = getTokens(linha);
        if (tokens.empty())
        {
            continue;
        }
        string primeiroToken = tokens[0];
        if (tokens.size() == 1 && primeiroToken.size() > 0 && primeiroToken[primeiroToken.size() - 1] == ':')
        {
            label_final += tokens[0] + " ";
            continue;
        }
        if (!label_final.empty())
        {
            linha = label_final + linha;
            label_final = "";
        }
        codigoFinal.push_back(linha);
    }
    if (!label_final.empty())
    {
        codigoFinal.push_back(label_final.substr(0, label_final.size() - 1));
    }

    return codigoFinal;
}

int valorDaVariavelNoEndereco(string& var, int endereco, int linha_pre){
        int saida;
        if( tabela_simbolos.find(var) == tabela_simbolos.end() ){ //se o símbolo ainda não está na tabela
            Simbolo s;
            s.endereco = -1;
            s.pendencia = endereco;
            tabela_simbolos.insert({var, s});
            endereco_para_linha_pre[endereco] = linha_pre; 
            saida = -1; //pendência
        }else{
            if(tabela_simbolos[var].endereco != -1){ //se o símbolo já foi definido
                saida = tabela_simbolos[var].endereco + soma_nas_variaveis[endereco];
            }else{
                saida = tabela_simbolos[var].pendencia;
                tabela_simbolos[var].pendencia = endereco;
                endereco_para_linha_pre[endereco] = linha_pre; // Map pendency address to source line
            }
        }
        return saida;
}

int adicionarSomaNoVetor (const vector<string>& tokens){
    int valor = 0; //caso não tenha soma ou subtração
    for(int i= 0; i< (int) tokens.size() -1; i++){
        if(tokens[i] == "+" || tokens[i] == "-"){
            string sinal = tokens[i];
            string prox = tokens[i+1];
            valor = stoi(prox);
            if(sinal == "-") valor = -valor;
        }
    }
    return valor;
}

static void processaLabel(vector<string>& tokens, int &endereco, vector <string> & pre, int linha_pre)
{
    if (tokens.empty()) return;
    string label = tokens[0];
    if (label.empty()) return;
    if (label[(int)label.size() - 1] == ':') {
        label = label.substr(0, (int)label.size() - 1);
        bool temErro = verificaErroLabel(label);
        if (temErro){
        pre [linha_pre] += " erro léxico";
        }
        if (tabela_simbolos.find(label) == tabela_simbolos.end()) {
            Simbolo s;
            s.endereco = endereco;
            s.pendencia = -1;
            tabela_simbolos.insert({label, s});
        } else {
            if ((tabela_simbolos)[label].endereco!=-1){
                pre [linha_pre] += " erro semântico";
            }
            tabela_simbolos[label].endereco = endereco;
        }
        tokens.erase(tokens.begin());
    }
}

static void handleSPACE(const vector<string>& tokens, vector<int>& saida, int &endereco)
{
    int qtd_zeros = 1;
    if (tokens.size() > 1) {
        qtd_zeros = stoi(tokens[1]);
    }
    for(int i= 0; i<qtd_zeros; i++){
        saida.push_back(0);
        endereco++;
    }
}

static void handleCONST(const vector<string>& tokens, vector<int>& saida, int &endereco)
{
    int valor_token = stoi(tokens[1]);
    saida.push_back(valor_token);
    endereco++;
}

static void handleCOPY(const vector<string>& tokens, vector<int>& saida, int &endereco, int linha_pre, vector<string> &pre)
{
    if (tokens.size() != 3 && tokens.size() != 5 && tokens.size() != 7) {
        pre[linha_pre] += " erro sintático"; 
        return;
    }
    
    if (tokens.size() == 5) {
        bool plus_at_2 = (tokens[2] == "+");
        bool plus_at_3 = (tokens[3] == "+");
        if (!(tokens[2] == "+") && !(tokens[3]== "+")) {
            pre[linha_pre] += " erro sintático";
            return;
        }
        if ((tokens[2] == "+") && (tokens[3]== "+")) {
            pre[linha_pre] += " erro sintático"; 
            return;
        }
    }
    else if (tokens.size() == 7) {
        if (tokens[2] != "+" || tokens[5] != "+") {
            pre[linha_pre] += " erro sintático"; 
            return;
        }
    }
    
    int posicao_virgula = -1;
    vector<string> variavel1;
    vector<string> variavel2;

    for(int i = 1; i<(int) tokens.size(); i++){
        string token_atual = tokens[i];
        
        if(!token_atual.empty() && token_atual[0] == ','){
            if(posicao_virgula != -1){
            }
            posicao_virgula = i;
            string sem_virgula = token_atual.substr(1);
            if(!sem_virgula.empty()) {
                variavel2.push_back(sem_virgula);
            }
        }
        else {
            if(posicao_virgula ==-1) variavel1.push_back(tiraVirgula(token_atual));
            else variavel2.push_back(tiraVirgula(token_atual));
        
            if(token_atual[token_atual.size()-1] == ','){
                    if(posicao_virgula != -1){
                    }
            posicao_virgula = i;
            }
        }
    }
    if(posicao_virgula==-1){
        pre[linha_pre] += " erro sintático"; // erro número de argumentos inválido para COPY
        return;
    }
    
    if (variavel1.empty() || variavel1[0].empty()) {
        pre[linha_pre] += " erro sintático"; // primeiro argumento vazio
        return;
    }
    
    if (variavel2.empty() || variavel2[0].empty()) {
        pre[linha_pre] += " erro sintático"; // segundo argumento vazio
        return;
    }
    
    string arg1 = variavel1[0];
    arg1= tiraVirgula (arg1);
    bool temErro = verificaErroLabel(arg1);
    if (temErro){
        pre [linha_pre] += " erro léxico";
    }
    string arg2 = variavel2[0];
    temErro = verificaErroLabel (arg2);
        if (temErro){
        pre [linha_pre] += " erro léxico";
    }
    
    int valor_soma1 = adicionarSomaNoVetor(variavel1);
    soma_nas_variaveis[endereco] = valor_soma1;
    int valor_arg1 = valorDaVariavelNoEndereco(arg1, endereco, linha_pre);
    saida.push_back(valor_arg1);
    endereco++;
    int valor_soma2 = adicionarSomaNoVetor(variavel2);
    soma_nas_variaveis[endereco] = valor_soma2;
    int valor_arg2 = valorDaVariavelNoEndereco(arg2, endereco, linha_pre);
    saida.push_back(valor_arg2);
    endereco++;
}

static void handleSingleArgInstruction(const string& instrucao, const vector<string>& tokens, vector <string> & pre, vector<int>& saida, int &endereco, int & linha_pre)
{
    if (tokens.size() < 2) {
        pre[linha_pre]+= " erro sintático";
        return;
    }
    else if (tokens.size() > 4 || (tokens.size() == 3) || (tokens.size() == 4 && tokens[2] != "+")){
        pre[linha_pre]+= " erro sintático";
        return;
    }
    string arg = tokens[1];
    bool temErro = verificaErroLabel(arg);
    if (temErro){
        pre [linha_pre] += " erro léxico";
    }
    
    soma_nas_variaveis[endereco] = adicionarSomaNoVetor(tokens);
    int valor_arg = valorDaVariavelNoEndereco(arg, endereco, linha_pre);
    saida.push_back(valor_arg);
    endereco_para_linha_pre[endereco] = linha_pre;
    endereco++;
}

static void handleInstruction(const string& instrucao, const vector<string>& tokens, vector<int>& saida, int &endereco, vector<string>& pre, int linha_pre)
{
    if (opcode.find(instrucao) == opcode.end()) {
        pre [linha_pre] += " erro sintático";
        return;
    }
    int valor_token = opcode[instrucao];
    saida.push_back(valor_token);
    endereco++;

    if (instrucao == "STOP") {
        if (tokens.size() > 1) {
            pre[linha_pre] += " erro sintático";
        }
    } else if (instrucao == "COPY") {
        handleCOPY(tokens, saida, endereco, linha_pre, pre);
    } else {
        handleSingleArgInstruction(instrucao, tokens, pre, saida, endereco, linha_pre);
    }
}

vector<int> o1(vector<string> &pre){
    vector<int> saida;
    int endereco = 0;
    int linha_pre = 0;
    for (string linha : pre) {
        vector<string> tokens = getTokens(linha);
        if (tokens.empty()) {
            linha_pre++;
            continue;
        }

        processaLabel(tokens, endereco, pre, linha_pre);

        if (tokens.empty()) {
            linha_pre++;
            continue;
        }

        string instrucao = tokens[0];

        if (instrucao == "SPACE") {
            handleSPACE(tokens, saida, endereco);
        } else if (instrucao == "CONST") {
            handleCONST(tokens, saida, endereco);
        } else {
            handleInstruction(instrucao, tokens, saida, endereco, pre, linha_pre);
        }
        linha_pre++;
    }

    return saida;
}


vector<int> o2(vector<int> codigoPendencias, vector<string> &pre){
    vector<int> saida = codigoPendencias;
    for(auto [nome, simbolo] : tabela_simbolos){
        int pendencia = simbolo.pendencia;
        int endereco = simbolo.endereco;
        if (endereco == -1)
        {
            while (pendencia != -1)
            {
                auto prox_endereco = endereco_para_linha_pre.find(pendencia);
                if (prox_endereco != endereco_para_linha_pre.end())
                {
                    int linha_pre = prox_endereco->second;
                    pre[linha_pre] += " erro semântico"; // simbolo nao definido
                }
                saida[pendencia] = endereco;
                pendencia = codigoPendencias[pendencia];
            }
        }
        else {
        while(pendencia != -1){
            saida[pendencia] = endereco + soma_nas_variaveis[pendencia];
            pendencia = codigoPendencias[pendencia];
        }
        }
    }
    return saida;
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
    vector<int> codigoO1 = o1(codigoExpandido);
    vector<int> codigoO2 = o2(codigoO1, codigoExpandido);
    /*for (string linha : codigoExpandido)
{
    cout << linha << "\n";
}

for (auto x : codigoO1)
    cout << x << " ";
cout << "\n";
for (auto x : codigoO2)
    cout << x << " ";
cout << "\n";*/
    string nome_arquivo_sem_extensao = nome_arquivo_entrada;
    int extensao = nome_arquivo_sem_extensao.find_last_of(".");
    if (extensao != std::string::npos)
    {
        nome_arquivo_sem_extensao = nome_arquivo_sem_extensao.substr(0, extensao);
    }

    string nome_arquivo_pre_final = nome_arquivo_sem_extensao + ".pre";
    ofstream saida_pre(nome_arquivo_pre_final);
    for (int i = 0; i < codigoExpandido.size(); i++)
    {
        string linha = codigoExpandido[i];
        saida_pre << linha;
        if (i != (codigoExpandido.size() - 1))
        {
            saida_pre << "\n";
        }
    }
    saida_pre.close();

    string nome_arquivo_o1 = nome_arquivo_sem_extensao + ".o1";
    ofstream saida_o1(nome_arquivo_o1);
    for (int i = 0; i < codigoO1.size(); i++)
    {
        saida_o1 << codigoO1[i];
        if (i < codigoO1.size() - 1)
        {
            saida_o1 << " ";
        }
    }
    saida_o1.close();

    string nome_arquivo_o2 = nome_arquivo_sem_extensao + ".o2";
    ofstream saida_o2(nome_arquivo_o2);
    for (int i = 0; i < codigoO2.size(); i++)
    {
        saida_o2 << codigoO2[i];
        if (i < codigoO2.size() - 1)
        {
            saida_o2 << " ";
        }
    }
    saida_o2.close();
    return 0;
}