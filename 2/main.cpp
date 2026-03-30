#include "Book.h"
#include <iostream>

int main() {
    std::setlocale(LC_ALL, "Ru");
    std::vector<std::string> works1 = { "Война и мир", "Анна Каренина" };
    Book book1("Лев Толстой", works1, 1200, 500.0);

    std::vector<std::string> works2 = { "Преступление и наказание", "Идиот" };
    Book book2("Фёдор Достоевский", works2, 800, 450.0);

    std::vector<std::string> works3 = { "Евгений Онегин", "Руслан и Людмила" };
    Book book3("Александр Пушкин", works3, 600, 300.0);

    std::cout << "Книга 1:\n";
    book1.printInfo();
    std::cout << "\nКнига 2:\n";
    book2.printInfo();
    std::cout << "\nКнига 3:\n";
    book3.printInfo();

    std::cout << "\n--- Оператор + (book1 + book2) ---\n";
    Book book4 = book1 + book2;
    book4.printInfo();

    std::cout << "\n--- Оператор += (book1 += book3) ---\n";
    book1 += book3;
    book1.printInfo();

    std::cout << "\n--- Оператор / (book2 / book3) ---\n";
    Book book5 = book2 / book3;
    book5.printInfo();

    std::cout << "\n--- Демонстрация деструкторов ---\n";
    return 0;
}