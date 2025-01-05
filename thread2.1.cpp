#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std::chrono_literals;
std::atomic_int count = 1;
int clients = 5;

void clientThread(int clients) {
    while (count < clients)
    {
        count.fetch_add(1, std::memory_order_seq_cst);
        std::this_thread::sleep_for(1s);
        std::cout << count + 1 << " клиент(ов) в очереди. " << std::endl;
    }
}

void operatorThread() {
    while (count > 0) {
        count.fetch_sub(1, std::memory_order_seq_cst);
        std::this_thread::sleep_for(2s);
        if (count > 0) {
            std::cout << " Оператор обслужил клиента, " << count - 1 << " клиент(ов) в очереди. " << std::endl;
        }
        else {
            std::cout << "Оператор закончил рабоу. Номер клиента 0: " << count << std::endl;
            break;
        }
    }
}

int main() 
{
    system("chcp 1251");
    
    std::thread client(clientThread, clients);
    std::thread operatorT(operatorThread);

    client.join();
    operatorT.join();

    return 0;
}