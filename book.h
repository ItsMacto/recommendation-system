#ifndef  BOOK_H
#define  BOOK_H
#include <string>

class Book
{
public:
    Book(std::string title);
    std::string getTitle() const;
    void addRating(double rating);
    double getAverageRating() const;

private:
    std::string title;
    double totalRating = 0, ratingCount = 0;
};

#endif  
