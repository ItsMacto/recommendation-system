#ifndef BOOKRECOMMENDER_H
#define BOOKRECOMMENDER_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include "user.h"
#include "book.h"


class BookRecommender
{
public:
    BookRecommender();
    BookRecommender(const std::string &filename);
    void addBook(std::string title);
    User *addUser(std::string name);
    bool loadData(const std::string &filename);
    void printRecommend(std::string userName) const;
    void printAverages() const;
    
private:
    std::vector<User*> users;
    std::vector<Book*> books;
    std::vector<std::pair<double, std::string>> similarity(User recommender) const;
    std::string removeWs(std::string line);
};

#endif // BOOKRECOMMENDER_H


