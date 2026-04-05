#include <iostream>
#include <string>
#include <iomanip>

#include "OrderBook.hpp"
#include "Order.hpp"
#include "Transaction.hpp"

void testar(bool condicao, const std::string& nome_teste) {
    if (condicao) {
        std::cout << "[PASSOU] " << nome_teste << std::endl;
    } else {
        std::cout << "[FALHOU] " << nome_teste << std::endl;
    }
}

int main() {
    std::cout << std::fixed << std::setprecision(1);

    std::cout << "===== TESTE 1: order book criado =====" << std::endl;
    {
        OrderBook book;
        std::cout << "Sistema criado com sucesso." << std::endl;
    }
    std::cout << std::endl;

    std::cout << "===== TESTE 2: ordem sem execucao =====" << std::endl;
    {
        OrderBook book;

        testar(book.submit(Order(1, 'B', 10.0, 1)) == false,
               "submit(Order(1, 'B', 10.0, 1)) deve armazenar a ordem");

        book.printBuyOrders();
        book.printSellOrders();
        book.printTransactions();
    }
    std::cout << std::endl;

    std::cout << "===== TESTE 3: execucao imediata =====" << std::endl;
    {
        OrderBook book;

        book.submit(Order(1, 'B', 10.0, 1));

        testar(book.submit(Order(2, 'S', 9.0, 2)) == true,
               "submit(Order(2, 'S', 9.0, 2)) deve casar com a compra de id 1");

        book.printBuyOrders();
        book.printSellOrders();
        book.printTransactions();
    }
    std::cout << std::endl;

    std::cout << "===== TESTE 4: escolha da melhor contraparte =====" << std::endl;
    {
        OrderBook book;

        testar(book.submit(Order(10, 'S', 9.5, 10)) == false,
               "Inserir venda (10, 'S', 9.5, 10)");
        testar(book.submit(Order(11, 'S', 8.0, 11)) == false,
               "Inserir venda (11, 'S', 8.0, 11)");
        testar(book.submit(Order(12, 'S', 8.0, 12)) == false,
               "Inserir venda (12, 'S', 8.0, 12)");

        testar(book.submit(Order(13, 'B', 10.0, 13)) == true,
               "Compra (13, 'B', 10.0, 13) deve escolher a melhor venda compativel");

        std::cout << "Estado apos a execucao (deve remover a venda de menor preco e menor timestamp):" << std::endl;
        book.printBuyOrders();
        book.printSellOrders();
        book.printTransactions();
    }
    std::cout << std::endl;

    std::cout << "===== TESTE 5: ordem nao compativel =====" << std::endl;
    {
        OrderBook book;

        testar(book.submit(Order(20, 'S', 12.0, 20)) == false,
               "Inserir venda (20, 'S', 12.0, 20)");
        testar(book.submit(Order(21, 'B', 10.0, 21)) == false,
               "Compra (21, 'B', 10.0, 21) nao deve executar");

        book.printBuyOrders();
        book.printSellOrders();
        book.printTransactions();
    }
    std::cout << std::endl;

    std::cout << "===== TESTE 6: cancelamentos =====" << std::endl;
    {
        OrderBook book;

        book.submit(Order(20, 'S', 12.0, 20));
        book.submit(Order(21, 'B', 10.0, 21));

        testar(book.cancel(21) == true,
               "Cancelar ordem existente id 21");
        testar(book.cancel(21) == false,
               "Cancelar novamente a ordem id 21");
        testar(book.cancel(999) == false,
               "Cancelar ordem inexistente id 999");

        book.printBuyOrders();
        book.printSellOrders();
        book.printTransactions();
    }
    std::cout << std::endl;

    std::cout << "===== TESTE 7: getBuyOrders / getSellOrders / getTransactions =====" << std::endl;
    {
        OrderBook book;

        book.submit(Order(20, 'S', 12.0, 20));

        int nBuy = -1;
        int nSell = -1;
        int nTrans = -1;

        Order* buyOrders = book.getBuyOrders(&nBuy);
        Order* sellOrders = book.getSellOrders(&nSell);
        Transaction* transactions = book.getTransactions(&nTrans);

        testar(nBuy >= 0, "getBuyOrders preenche n corretamente");
        testar(nSell >= 0, "getSellOrders preenche n corretamente");
        testar(nTrans >= 0, "getTransactions preenche n corretamente");

        std::cout << "Quantidade de buy orders: " << nBuy << std::endl;
        std::cout << "Quantidade de sell orders: " << nSell << std::endl;
        std::cout << "Quantidade de transactions: " << nTrans << std::endl;

        if (buyOrders == nullptr) {
            std::cout << "getBuyOrders retornou nullptr" << std::endl;
        } else {
            std::cout << "Buy orders retornadas por getBuyOrders:" << std::endl;
            for (int i = 0; i < nBuy; i++) {
                std::cout << "[" << buyOrders[i].getId()
                          << " | " << buyOrders[i].getPrice()
                          << " | " << buyOrders[i].getTimestamp()
                          << "]" << std::endl;
            }
        }

        if (sellOrders == nullptr) {
            std::cout << "getSellOrders retornou nullptr" << std::endl;
        } else {
            std::cout << "Sell orders retornadas por getSellOrders:" << std::endl;
            for (int i = 0; i < nSell; i++) {
                std::cout << "[" << sellOrders[i].getId()
                          << " | " << sellOrders[i].getPrice()
                          << " | " << sellOrders[i].getTimestamp()
                          << "]" << std::endl;
            }
        }

        if (transactions == nullptr) {
            std::cout << "getTransactions retornou nullptr" << std::endl;
        } else {
            std::cout << "Transactions retornadas por getTransactions:" << std::endl;
            for (int i = 0; i < nTrans; i++) {
                std::cout << "[" << transactions[i].getBuyOrderId()
                          << ", " << transactions[i].getSellOrderId()
                          << ", " << transactions[i].getExecutionPrice()
                          << "]" << std::endl;
            }
        }

        delete[] buyOrders;
        delete[] sellOrders;
        delete[] transactions;
    }
    std::cout << std::endl;

    std::cout << "===== TESTE 8: novo cenario de compra e venda =====" << std::endl;
    {
        OrderBook book;

        book.submit(Order(20, 'S', 12.0, 20));

        testar(book.submit(Order(30, 'B', 11.0, 30)) == false,
               "Inserir compra id 30");
        testar(book.submit(Order(31, 'B', 13.0, 31)) == true,
               "Compra id 31 deve casar com a venda 20");
        testar(book.submit(Order(32, 'S', 12.0, 32)) == false,
               "Venda id 32 nao deve casar com a compra 30");

        book.printBuyOrders();
        book.printSellOrders();
        book.printTransactions();
    }
    std::cout << std::endl;

    std::cout << "===== TESTE 9: validando quantidades finais =====" << std::endl;
    {
        OrderBook book;

        book.submit(Order(20, 'S', 12.0, 20));
        book.submit(Order(30, 'B', 11.0, 30));
        book.submit(Order(31, 'B', 13.0, 31));
        book.submit(Order(32, 'S', 12.0, 32));

        int nBuy = -1;
        int nSell = -1;
        int nTrans = -1;

        Order* buyOrders = book.getBuyOrders(&nBuy);
        Order* sellOrders = book.getSellOrders(&nSell);
        Transaction* transactions = book.getTransactions(&nTrans);

        testar(nBuy >= 0, "Quantidade final de compras consultada");
        testar(nSell >= 0, "Quantidade final de vendas consultada");
        testar(nTrans >= 0, "Quantidade final de transacoes consultada");

        delete[] buyOrders;
        delete[] sellOrders;
        delete[] transactions;
    }
    std::cout << std::endl;

    std::cout << "===== TESTE 10: estado final completo =====" << std::endl;
    {
        OrderBook book;

        book.submit(Order(20, 'S', 12.0, 20));
        book.submit(Order(30, 'B', 11.0, 30));
        book.submit(Order(31, 'B', 13.0, 31));
        book.submit(Order(32, 'S', 12.0, 32));

        book.printBuyOrders();
        book.printSellOrders();
        book.printTransactions();
    }

    return 0;
}