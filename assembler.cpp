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

struct Simbolo
{
    int endereco;
    int pendencia;
};

map<string,Simbolo> tabela_simbolos;


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
    if (mnt.find(nome) == mnt.end())
    {
        return macroExpandida;
    }
    int pos_mdt = mnt[nome];
    string expand_linha = mdt[pos_mdt];
    while (expand_linha != "ENDMACRO")
    {
        string linha_expandida = expand_linha;
        for (int arg = 0; arg < argumentos.size(); arg++)
        {
            string local_arg = "#" + to_string(arg + 1);
            vector<string> tokens = getTokens(linha_expandida);
            for (int j = 0; j < tokens.size(); j++)
            {
                if (tokens[j] == local_arg)
                {
                    tokens[j] = argumentos[arg];
                }
            }
            linha_expandida = juntaTokens(tokens);
        }
        macroExpandida.push_back(linha_expandida);
        pos_mdt++;
        if (pos_mdt >= mdt.size())
        {
            break;
        }
        expand_linha = mdt[pos_mdt];
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

int valorDaVariavelNoEndereco(string& var, int endereco){
        int saida;
        if( tabela_simbolos.find(var) == tabela_simbolos.end() ){ //se o símbolo ainda não está na tabela
            Simbolo s;
            s.endereco = -1;
            s.pendencia = endereco;
            tabela_simbolos.insert({var, s});
            saida = -1; //pendência
        }else{
            if(tabela_simbolos[var].endereco != -1){ //se o símbolo já foi definido
                saida = tabela_simbolos[var].endereco;
            }else{
                saida = tabela_simbolos[var].pendencia;
                tabela_simbolos[var].pendencia = endereco;
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

static void processLabelIfAny(vector<string>& tokens, int &endereco)
{
    if (tokens.empty()) return;
    string label = tokens[0];
    if (label.empty()) return;
    if (label[(int)label.size() - 1] == ':') {
        label = label.substr(0, (int)label.size() - 1);
        if (tabela_simbolos.find(label) == tabela_simbolos.end()) {
            Simbolo s;
            s.endereco = endereco;
            s.pendencia = -1;
            tabela_simbolos.insert({label, s});
        } else {
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

static void handleCOPY(const vector<string>& tokens, vector<int>& saida, int &endereco)
{
    int posicao_virgula = -1;
    vector<string> variavel1;
    vector<string> variavel2;

    for(int i = 1; i<(int) tokens.size(); i++){
        string token_atual = tokens[i];
        
        if(posicao_virgula ==-1) variavel1.push_back(tiraVirgula(token_atual));
        else variavel2.push_back(tiraVirgula(token_atual));
    
        if(token_atual[token_atual.size()-1] == ','){
                if(posicao_virgula != -1){
                    cout << "tem duas virgulas " << endereco << "\n";
                    return;
                }
        posicao_virgula = i;
        }
    }
    if(posicao_virgula==-1){
        cout << "erro número de argumentos inválido para COPY; endereço " << endereco << "\n";
        return;
    }
    string arg1 = variavel1[0];
    string arg2 = variavel2[0];
    int valor_arg1 = valorDaVariavelNoEndereco(arg1, endereco);
    int valor_soma1 = adicionarSomaNoVetor(variavel1);
    soma_nas_variaveis[endereco] = valor_soma1;
    saida.push_back(valor_arg1);
    endereco++;
    int valor_arg2 = valorDaVariavelNoEndereco(arg2, endereco);
    int valor_soma2 = adicionarSomaNoVetor(variavel2);
    soma_nas_variaveis[endereco] = valor_soma2;
    saida.push_back(valor_arg2);
    endereco++;
}

static void handleSingleArgInstruction(const string& instrucao, const vector<string>& tokens, vector<int>& saida, int &endereco)
{
    if (tokens.size() < 2) {
        cout << "erro: instrução " << instrucao << " sem argumento; endereço " << endereco - 1 << "\n";
        return;
    }
    string arg = tokens[1];
    int valor_arg = valorDaVariavelNoEndereco(arg, endereco);
    saida.push_back(valor_arg);
    soma_nas_variaveis[endereco] = adicionarSomaNoVetor(tokens);
    endereco++;
}

static void handleInstruction(const string& instrucao, const vector<string>& tokens, vector<int>& saida, int &endereco)
{
    if (opcode.find(instrucao) == opcode.end()) {
        cout << "erro instrução inválida; endereço " << endereco << "\n";
        return;
    }

    int valor_token = opcode[instrucao];
    saida.push_back(valor_token);
    endereco++;

    if (instrucao == "STOP") {
        if (tokens.size() > 1) {
            cout << "erro STOP com argumento; endereço " << endereco - 1 << "\n";
        }
    } else if (instrucao == "COPY") {
        handleCOPY(tokens, saida, endereco);
    } else {
        handleSingleArgInstruction(instrucao, tokens, saida, endereco);
    }
}

vector<int> o1(vector<string> &pre){
    vector<int> saida;
    int endereco = 0;

    for (string linha : pre) {
        vector<string> tokens = getTokens(linha);

        // handle possible label at beginning (may erase tokens[0])
        processLabelIfAny(tokens, endereco);

        string instrucao = tokens[0];

        if (instrucao == "SPACE") {
            handleSPACE(tokens, saida, endereco);
        } else if (instrucao == "CONST") {
            handleCONST(tokens, saida, endereco);
        } else {
            handleInstruction(instrucao, tokens, saida, endereco);
        }
    }

    return saida;
}


vector<int> o2(vector<int> codigoPendencias, vector<string> &pre){
    vector<int> saida = codigoPendencias;
    for(auto [nome, simbolo] : tabela_simbolos){
        int pendencia = simbolo.pendencia;
        int endereco = simbolo.endereco;
        while(pendencia != -1){
            saida[pendencia] = endereco;
            pendencia = codigoPendencias[pendencia];
        }
    }
    for(int i= 0; i< (int)saida.size(); i++){
        saida[i] += soma_nas_variaveis[i];
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
    for(auto x : codigoO1) cout << x << " ";
    cout << "\n";
    vector<int> codigoO2 = o2(codigoO1, codigoExpandido);
    for(auto x : codigoO2) cout << x << " ";
    cout << "\n";
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