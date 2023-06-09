#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Registro para representar um produto
struct Produto {
    string nome;
    float valor;
    int quantidade;

    Produto(string nome1, float valor1, int quantidade1) {
        nome = nome1;
        valor = valor1;
        quantidade = quantidade1;
    }
}; 
 // Registro para representar a maquina
 struct MaquinaVendas {
    float faturamentoTotal;
    float faturamentoPossivel = 0.0;
    vector<Produto> produtos;
    MaquinaVendas() { 
       faturamentoTotal = 0.0;

      cout << "Bem vindo a Vending Machine\n"<< endl;
      cout << "Adicione seus primeiros produtos.\n"<< endl;

      // Adicione alguns produtos iniciais
      adicionarProdutos();
  
    }

      //fução para remover produtos
     
     template <typename T>
    void remove(vector<T>& produtos, size_t index){
          produtos.erase(produtos.begin() + index);
    }
     void removerProdutos(){
       
        int i;
       
       cout << "Digite o numero do produto que deseja remover: ";
       cin >> i;

       remove(produtos, i+1);
    }



     // função para adicionar produtos
    void adicionarProdutos(){
        string prod;
        float preco;
        int qtd;
        char decisao;
      
          do {

            cout << "Digite a descrição: ";
            cin.ignore();
            getline(cin, prod);
            cout << "Digite o preço: ";
            cin >>  preco;
            cout << "Digite a quantidade: ";
            cin >> qtd;
            produtos.push_back(Produto(prod, preco, qtd));

            listarProdutos();

            cout << "Deseja adicionar mais algum produto? [S/N]";
            cin >> decisao;
          }while(decisao == 's' || decisao == 'S');  
  
    }
// Modo Usuário: lista os produtos disponíveis e permite ao usuário escolher e comprar um produto
    void modoUsuario() {

      int escolha;
      float valorInserido;
      
        cout << "=== Modo Usuário ===" << endl;
        listarProdutos();

        cout << "Digite o número do produto que deseja comprar: ";
       
        cin >> escolha;

        if (escolha < 1 || escolha > produtos.size()) {
            cout << "Opção inválida!" << endl;
            return;
        }

        Produto& produtoEscolhido = produtos[escolha - 1];

        cout << "Produto escolhido: " << produtoEscolhido.nome << " - Valor: R$" << produtoEscolhido.valor << endl;

        cout << "Insira o valor: R$";
        cin >> valorInserido;

        if (valorInserido < produtoEscolhido.valor) {
            cout << "Valor insuficiente. Operação cancelada." << endl;
            return;
        }

        if (produtoEscolhido.quantidade <= 0) {
            cout << "Produto indisponível. Operação cancelada." << endl;
            return;
        }

        // Atualiza os valores
        produtoEscolhido.quantidade--;
        faturamentoTotal += produtoEscolhido.valor;

        cout << "Produto retirado: " << produtoEscolhido.nome << endl;
        cout << "Troco: R$" << valorInserido - produtoEscolhido.valor << endl;
    }

    // Modo Administrador: permite gerenciar a máquina, repor produtos, listar inventário e faturamento
    void modoAdministrador() {

      int opcao;
      
        cout << "=== Modo Administrador ===" << endl;
        cout << "Escolha uma opção:" << endl;
        cout << "1. Repor produtos" << endl;
        cout << "2. Listar inventário" << endl;
        cout << "3. Mostrar faturamento" << endl;
        cout << "4. Adicionar produtos" << endl;
        cout << "5. Remover produtos" << endl;
      
        cin >> opcao;

        switch (opcao) {
            case 1:
                reporProdutos();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                mostrarFaturamento();
                break;
            case 4:
                adicionarProdutos();
            case 5:
                removerProdutos();
            default:
                cout << "Opção inválida!" << endl;
                break;
        }
    }

    // Lista os produtos disponíveis na máquina
    void listarProdutos() {
        cout << "Produtos disponíveis:" << endl;

        for (int i = 0; i < produtos.size(); i++) {
            Produto produto = produtos[i];
            cout << i + 1 << ". " << produto.nome << " - Valor: R$" << produto.valor << " - Quantidade: " << produto.quantidade << endl;
        }
    }

    // Repõe a quantidade de produtos na máquina
    void reporProdutos() {
        listarProdutos();
        int escolha, quantidade;
      
        cout << "Digite o número do produto que deseja repor: ";
        
        cin >> escolha;

        if (escolha < 1 || escolha > produtos.size()) {
            cout << "Opção inválida!" << endl;
            return;
        }

        Produto& produtoReposto = produtos[escolha - 1];

        cout << "Digite a quantidade a ser adicionada: ";
        cin >> quantidade;

        produtoReposto.quantidade += quantidade;

        cout << "Reposição realizada com sucesso." << endl;
    }

    // Mostra o faturamento total da máquina
    void mostrarFaturamento() {
        
       for (int j = 0; j < produtos.size(); j++){
         Produto produtoRestante = produtos[j];
          faturamentoPossivel += produtoRestante.valor * produtoRestante.quantidade;}
      
        cout << "Faturamento total: R$" << faturamentoTotal << endl;
        cout << "Faturamento Possivel: R$"<< faturamentoPossivel << endl;
    }
};


int main() {
    MaquinaVendas maquina;

    int modo, senha, ADMsenha = 1234;// Senha do modo adm 1234
  do{
    cout << "\nEscolha uma opção:" << endl;
        cout << "1. Modo Usuario" << endl;
        cout << "2. Modo administrador" << endl;
        cout << "3. Desligar" << endl;
    cin >> modo;

    if (modo == 1) {
        maquina.modoUsuario();
    } else if (modo == 2) {
          do{
              cout << "DIGITE A SENHA:";
              cin >> senha;
              if (senha == ADMsenha){
                 maquina.modoAdministrador();
              }else 
                  cout << "Senha incorreta!" << endl; 
         }while(senha != ADMsenha);
    
    } else if (modo == 3) {
          do{
              cout << "\nDIGITE A SENHA:";
              cin >> senha;
              if (senha == ADMsenha){
                 cout << "Desligando..." << endl;
              }else 
                  cout << "Senha incorreta!" << endl; 
         }while(senha != ADMsenha);
      
    }else
      cout << "Modo inválido!" << endl;
  }while(modo !=3);
    return 0;
}
