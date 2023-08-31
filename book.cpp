#include "book.h"

Book::Book(std::string title) : title(title) {}

std::string Book::getTitle() const { return title; }

void Book::addRating(double rating)
{
    if (rating == 0)
        return;
    else if (rating <= 5 && rating >= -5 )
    {
        ratingCount++;
        totalRating += rating;
    }else{
        throw std::invalid_argument("Invalid rating");
    }
}

double Book::getAverageRating() const
{
    if (ratingCount == 0)
        return 0;
    return totalRating / ratingCount;
}

    