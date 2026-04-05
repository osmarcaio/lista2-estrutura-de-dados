# Trabalho 2 - Order Book

## Descrição do projeto

Este projeto implementa um sistema simples de ordens de compra e venda em C++, conforme proposto no Trabalho 2 da disciplina.

O sistema gerencia ordens de **compra** e **venda** de uma única ação. Para cada nova ordem inserida, o programa verifica automaticamente se existe alguma contraparte compatível já armazenada no sistema e, caso exista, executa imediatamente a transação seguindo as regras definidas no enunciado.

O sistema permite:

- inserir novas ordens;
- cancelar ordens existentes;
- exibir ordens de compra em aberto;
- exibir ordens de venda em aberto;
- exibir transações executadas.

Cada ordem contém as seguintes informações:

- identificador único;
- tipo da ordem (`'B'` para compra e `'S'` para venda);
- preço;
- timestamp.

Cada transação registra:

- id da ordem de compra;
- id da ordem de venda;
- preço de execução.

## Organização dos arquivos

O projeto está organizado nos seguintes arquivos:

- `main.cpp`
- `OrderBook.hpp`
- `OrderBook.cpp`
- `Order.hpp`
- `Order.cpp`
- `Transaction.hpp`
- `Transaction.cpp`
- `Node.hpp`
- `Node.cpp`

### Função de cada arquivo

- **main.cpp**: contém os testes que demonstram o funcionamento do sistema;
- **Order.hpp / Order.cpp**: definem e implementam a classe `Order`, responsável por representar uma ordem de compra ou venda;
- **Transaction.hpp / Transaction.cpp**: definem e implementam a classe `Transaction`, responsável por representar uma transação executada;
- **OrderBook.hpp / OrderBook.cpp**: definem e implementam a classe `OrderBook`, responsável por armazenar, gerenciar, executar, cancelar e imprimir as ordens e transações do sistema;
- **Node.hpp / Node.cpp**: contêm as estruturas auxiliares encadeadas usadas para armazenar as ordens e transações dinamicamente.

## Instruções de compilação

Para compilar o projeto, utilize o comando:

```bash
g++ main.cpp OrderBook.cpp Order.cpp Transaction.cpp Node.cpp -o order_book
```

## Instruções de execução

Após a compilação, execute o programa com:

```bash
./order_book
```

No Windows, a execução também pode ser feita com:

```bash
order_book.exe
```

## Organização interna dos dados

Internamente, o sistema foi implementado com estruturas manuais, sem uso de estruturas da STL como `vector`, `list` ou `map`, conforme exigido pelo enunciado.

### 1. Armazenamento das ordens e transações

A classe `OrderBook` mantém três estruturas principais:

- uma lista de ordens de compra em aberto (`lista_de_compras`);
- uma lista de ordens de venda em aberto (`lista_de_vendas`);
- uma lista de transações executadas (`lista_de_transacoes`).

Essas estruturas são implementadas manualmente com listas encadeadas simples.

### 2. Estrutura usada para ordens

As ordens de compra e venda são armazenadas por meio da estrutura `OrderNode`, que possui:

- um objeto `Order`;
- um ponteiro para o próximo nó da lista.

O controle dessas listas é feito pela classe `OrderNodeControl`, que mantém:

- um ponteiro para o primeiro nó da lista;
- a quantidade total de elementos armazenados.

De forma conceitual, a estrutura pode ser entendida como:

```cpp
struct OrderNode {
    Order order;
    OrderNode* next;
};
```

### 3. Estrutura usada para transações

As transações executadas são armazenadas por meio da estrutura `TransactionNode`, que possui:

- um objeto `Transaction`;
- um ponteiro para o próximo nó da lista.

O controle dessa lista é feito pela classe `TransactionNodeControl`, que também mantém:

- um ponteiro para o primeiro nó;
- a quantidade de transações registradas.

De forma conceitual, a estrutura pode ser entendida como:

```cpp
struct TransactionNode {
    Transaction transaction;
    TransactionNode* next;
};
```

### 4. Funcionamento da inserção de ordens

No método `submit`, o sistema verifica o tipo da ordem recebida:

- se a ordem for de compra, ele percorre as ordens de venda em aberto;
- se a ordem for de venda, ele percorre as ordens de compra em aberto.

Durante essa busca, o sistema procura uma contraparte compatível e escolhe a melhor opção de acordo com as regras do trabalho:

- para compra, escolhe a venda de menor preço;
- para venda, escolhe a compra de maior preço;
- em caso de empate, escolhe a de menor timestamp.

Se houver pareamento:

1. a transação é criada;
2. a transação é armazenada na lista de transações;
3. a ordem antiga compatível é removida da lista correspondente;
4. o método retorna `true`.

Se não houver pareamento, a nova ordem é inserida na lista correspondente e o método retorna `false`.

### 5. Funcionamento do cancelamento

No método `cancel`, o sistema procura o id informado primeiro na lista de compras e depois na lista de vendas.

Quando a ordem é encontrada, o nó correspondente é removido da lista encadeada, os ponteiros são ajustados corretamente e o método retorna `true`.

Caso nenhuma ordem com o id informado seja encontrada, o método retorna `false`.

### 6. Funcionamento dos métodos `get...`

Os métodos:

- `getBuyOrders`
- `getSellOrders`
- `getTransactions`

retornam um novo array alocado dinamicamente com os elementos armazenados no sistema naquele momento.

Se não houver elementos, o método retorna `nullptr` e define `n = 0`.

Como os elementos são inseridos no início das listas encadeadas, o método `toArray` monta o array em ordem inversa de percurso, preservando a ordem original de inserção dos elementos.

### 7. Funcionamento da exibição do sistema

Os métodos `printBuyOrders`, `printSellOrders` e `printTransactions` utilizam os arrays retornados pelos métodos `get...` para imprimir o estado atual do sistema.

A saída é exibida com os elementos:

- identificação das seções;
- impressão de cada ordem ou transação no formato esperado;
- exibição de `(empty)` quando a estrutura estiver vazia.
