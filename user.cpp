#include "user.h"

User::User(std::string name) : name(name) {}

User::User(std::string name, const std::vector<Book*> &books) : name(name)
{
    for (const auto &i : books)
    {
        ratedBooks[i] = 0;
    }
}

std::string User::getName() const { return name; }

void User::addRatedBook(Book &book, double rating)
{
    if (ratedBooks[&book] == 0)
    {
        ratedBooks[&book] = rating;
        book.addRating(rating);
    }
}

double User::getRating(const Book &book) const
{
    auto it = ratedBooks.find(&book);
    if (it != ratedBooks.end())
        return it->second;
    else
        return 0;
}
