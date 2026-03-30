#include "Book.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

Book::Book() : author("Unknown"), pageCount(0), price(0.0) {}

Book::Book(const Book& other)
    : author(other.author), works(other.works), pageCount(other.pageCount), price(other.price) {
}

Book::Book(const std::string& author, const std::vector<std::string>& works, int pageCount, double price)
    : author(author), works(works), pageCount(pageCount), price(price) {
}


Book::~Book() {
    works.clear();
}

Book& Book::operator=(const Book& other) {
    if (this != &other) {
        author = other.author;
        works = other.works;
        pageCount = other.pageCount;
        price = other.price;
    }
    return *this;
}

std::string Book::getAuthor() const {
    return author;
}

std::vector<std::string> Book::getWorks() const {
    return works;
}

int Book::getPageCount() const {
    return pageCount;
}

double Book::getPrice() const {
    return price;
}

void Book::setRating(int rating) {
    if (rating >= 1 && rating <= 5) {
        std::cout << "Рейтинг установлен: " << rating << std::endl;
    }
    else {
        std::cout << "Ошибка: рейтинг должен быть от 1 до 5." << std::endl;
    }
}

void Book::printInfo() const {
    std::cout << "Автор: " << author << std::endl;
    std::cout << "Произведения: " << vectorToString(works) << std::endl;
    std::cout << "Количество страниц: " << pageCount << std::endl;
    std::cout << "Стоимость: " << std::fixed << std::setprecision(2) << price << std::endl;
}

void Book::changePrice(double newPrice) {
    if (newPrice >= 0) {
        price = newPrice;
    }
    else {
        std::cout << "Ошибка: стоимость не может быть отрицательной." << std::endl;
    }
}

Book Book::operator+(const Book& other) const {
    std::string newAuthor;
    if (author == other.author) {
        newAuthor = author;
    }
    else {
        newAuthor = author + " и " + other.author;
    }

    int newPageCount = pageCount + other.pageCount;

    double newPrice = price + other.price;
    newPrice -= newPrice * 0.15;

    std::vector<std::string> newWorks;
    if (author == other.author) {
        newWorks = works;
        newWorks.insert(newWorks.end(), other.works.begin(), other.works.end());
        std::sort(newWorks.begin(), newWorks.end());
        newWorks.erase(std::unique(newWorks.begin(), newWorks.end()), newWorks.end());
    }
    else {
        for (const auto& work : works) {
            newWorks.push_back(author + "+" + work);
        }
        for (const auto& work : other.works) {
            newWorks.push_back(other.author + "+" + work);
        }
        std::sort(newWorks.begin(), newWorks.end());
        newWorks.erase(std::unique(newWorks.begin(), newWorks.end()), newWorks.end());
    }

    return Book(newAuthor, newWorks, newPageCount, newPrice);
}

Book& Book::operator+=(const Book& other) {
    if (author == other.author) {
    }
    else {
        author = author + " и " + other.author;
    }

    pageCount += other.pageCount;

    price = price + other.price;
    price -= price * 0.15;

    std::vector<std::string> newWorks;
    if (author.find(" и ") != std::string::npos) {
        for (const auto& work : works) {
            std::string origAuthor = author.substr(0, author.find(" и "));
            newWorks.push_back(origAuthor + "+" + work);
        }
        for (const auto& work : other.works) {
            newWorks.push_back(other.author + "+" + work);
        }
    }
    else {
        newWorks = works;
        newWorks.insert(newWorks.end(), other.works.begin(), other.works.end());
    }

    std::sort(newWorks.begin(), newWorks.end());
    newWorks.erase(std::unique(newWorks.begin(), newWorks.end()), newWorks.end());
    works = newWorks;

    return *this;
}

Book Book::operator/(const Book& other) const {
    std::string newAuthor;
    if (author == other.author) {
        newAuthor = author;
    }
    else {
        newAuthor = author + " и " + other.author;
    }

    int newPageCount = pageCount + other.pageCount;
    newPageCount -= static_cast<int>(newPageCount * 0.3);

    double newPrice = price + other.price;
    newPrice += newPrice * 0.10;

    std::vector<std::string> newWorks;
    if (author == other.author) {
        size_t half1 = works.size() / 2;
        size_t half2 = other.works.size() / 2;
        newWorks.insert(newWorks.end(), works.begin(), works.begin() + half1);
        newWorks.insert(newWorks.end(), other.works.begin(), other.works.begin() + half2);
    }
    else {
        size_t half1 = works.size() / 2;
        size_t half2 = other.works.size() / 2;
        for (size_t i = 0; i < half1; ++i) {
            newWorks.push_back(author + "+" + works[i]);
        }
        for (size_t i = 0; i < half2; ++i) {
            newWorks.push_back(other.author + "+" + other.works[i]);
        }
    }

    std::sort(newWorks.begin(), newWorks.end());
    newWorks.erase(std::unique(newWorks.begin(), newWorks.end()), newWorks.end());

    return Book(newAuthor, newWorks, newPageCount, newPrice);
}

std::string Book::vectorToString(const std::vector<std::string>& vec) {
    std::string result = "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        result += vec[i];
        if (i != vec.size() - 1) result += ", ";
    }
    result += "]";
    return result;
}