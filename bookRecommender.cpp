#include "bookRecommender.h"
#include "book.h"
#include "user.h"

using namespace std;

BookRecommender::BookRecommender() {}

BookRecommender::BookRecommender(const string &filename)
{
    loadData(filename);
}

void BookRecommender::addBook(string title)
{
    Book* b = new Book(title);
    books.push_back(b);
}

User *BookRecommender::addUser(string name)
{
    // Check if the user already exists in the users vector
    for (auto user : users)
    {
        if (user->getName() == name)
        {
            return user;
        }
    }
    User* user = new User(name, books); 
    users.push_back(user);
    return user;
}

bool BookRecommender::loadData(const string &filename)

{
    // file opening
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cout << "Error opening file!" << endl;
        return false;
    }

    string line;
    set<string> bookSet; // adds all books from file to bookSet so no duplicates
    int count = 1;
    while (getline(inputFile, line))
    {
        
        line = removeWs(line);
        if (count % 3 == 2)
        { // only lines books are on
            bookSet.insert(line);
        }
        count++;
    }
    // creates book objects and adds them to books vector
    for (auto i : bookSet)
        addBook(i);

    // map of person name and their rating, index or rating corresponds to the index of book it belongs to
    inputFile.clear(); // file to start again
    inputFile.seekg(0, ios::beg);

    string userName, bookName, ratingStr;
    double rating;
    while (getline(inputFile, userName)) // gets the name, book, and rating
    {
        getline(inputFile, bookName);
        getline(inputFile, ratingStr);

        userName = removeWs(userName); // removes whitespace
        bookName = removeWs(bookName);
        ratingStr = removeWs(ratingStr);

        rating = stod(ratingStr); // converts string to double

        User* user = addUser(userName); 

        for (auto &i : books) 
        {
            
            if (i->getTitle() == bookName)
            {
                user->addRatedBook(*i, rating);
                
            }
        }
    }
return true;}

void BookRecommender::printRecommend(string userName) const
{
    for (auto i : users)
    {
        cout << users.size() << endl;
        if (i->getName() == userName) // if user in the user list
        {

            vector<pair<double, string>> userSimilarities = similarity(*i);

            for (auto const &[rating, book] : userSimilarities) // print
            {
            
                if (rating > 0)
                {
                    cout << book << " " << rating << endl;
                }
            }
            return;
        }
    }
    printAverages();
}

void BookRecommender::printAverages() const
{
    vector<pair<double, string>> avgList;
    for (auto i : books)
    {
        avgList.push_back(make_pair(i->getAverageRating(), i->getTitle()));
    }
    sort(avgList.rbegin(), avgList.rend());

    for (auto i : avgList)
    {
        cout << i.second << " " << i.first << endl;
    }
}

vector<pair<double, string>> BookRecommender::similarity(User recommender) const
{
    double sum;
    vector<pair<double, const User *>> userSimilarities; // list of pair user, similarity dot product
    for (auto comparedUser : users) 
    {
        sum = 0;
        if (comparedUser->getName() != recommender.getName()){
            for (auto bookPtr : books)
            {
                sum += comparedUser->getRating(*bookPtr) * recommender.getRating(*bookPtr);
            }
            userSimilarities.push_back(make_pair(sum, comparedUser));
        }
    }


    sort(userSimilarities.rbegin(), userSimilarities.rend());


    // take top 3 similar users, averages the books that are non 0, retuns best books in order
    vector<pair<double, string>> avgSimList; // list of pair rating, book name
    for (int bookI = 0; bookI < books.size(); bookI++) // for each book
    {
        avgSimList.push_back(make_pair(0, books[bookI]->getTitle())); // list of pair rating 0, book name
        int count = 0;
        for (int i = 0; i < 3; i++) //for the top 3 similar users
        {
            const User *simUser = userSimilarities[i].second;

            if ((*simUser).getRating(*books[bookI]) != 0) // for the top 3 that did not rate it 0, add rating to list
            {
                avgSimList[bookI].first += (*simUser).getRating(*books[bookI]);
                count++;
            }
        }
        if (count != 0)
        {
            avgSimList[bookI].first = (avgSimList[bookI].first) / count; // if it was rated find the average
        }
    }
    sort(avgSimList.rbegin(), avgSimList.rend()); // sort highest first
    return avgSimList;
}

string BookRecommender::removeWs(string line)

{
    // Remove leading whitespaces
    line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch)
                                          { return !std::isspace(ch); }));

    // Remove trailing whitespaces
    line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch)
                            { return !std::isspace(ch); })
                   .base(),
               line.end());

    return line;
}