#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

#include "bookRecommender.h"
#include "user.h"
#include "book.h"
using namespace std;




int main(int argc, char *argv[])
{
    // file opening ** make so more than one file can be opened **
    if (argc < 2)
    {
        cout << "Error no file given via command line!" << endl;
        return 1;
    }
    class BookRecommender bookRecommender(argv[1]);

    string userInput;
    do
    {

        cin >> userInput;
        if (userInput == "recommend") // recommend option
        {
            string userName;
            cin >> userName;
            bookRecommender.printRecommend(userName);

        }
        else if (userInput == "averages") // averages option
        {
            bookRecommender.printAverages();
        }
    } while (userInput != "quit"); // quit option
    return 0;
}
