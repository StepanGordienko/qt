#pragma once
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class Book {
private:
    std::string author;
    std::vector<std::string> works;
    int pageCount;
    double price;

public:
    Book();
    Book(const Book& other);
    Book(const std::string& author, const std::vector<std::string>& works, int pageCount, double price);
    ~Book();

    Book& operator=(const Book& other);

    std::string getAuthor() const;
    std::vector<std::string> getWorks() const;
    int getPageCount() const;
    double getPrice() const;

    void setRating(int rating);

    void printInfo() const;
    void changePrice(double newPrice);

    Book operator+(const Book& other) const;
    Book& operator+=(const Book& other);
    Book operator/(const Book& other) const;

    static std::string vectorToString(const std::vector<std::string>& vec);
};

#endif