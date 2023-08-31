#ifndef USER_H
#define USER_H
#include <string>
#include <map>
#include <vector>
#include "book.h"

class User
{
public:
    User(std::string name);
    User(std::string name, const std::vector<Book*> &books);
    std::string getName() const;
    void addRatedBook(Book &book, double rating);
    double getRating(const Book &book) const;

private:
    std::string name;
    std::map<const Book *, double> ratedBooks;
};

#endif  //!__USER__H__