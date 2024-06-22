#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <sstream>

using namespace std;

struct Book {
    string author;
    string title;
    string ISBN;
    bool Available;
};

struct purchaser {
    string name;
    string bookISBN;
    string borrowDate;
    string returnDate;
};

vector<Book> bookDatabase;
vector<purchaser> borrowerDatabase;
vector<purchaser> borrowHistory;

// Helper function to calculate days between two dates
int daysBetweenDates(const string& startDate, const string& endDate) {
    int startDay, startMonth, startYear;
    int endDay, endMonth, endYear;
    char slash;

    stringstream startStream(startDate);
    startStream >> startDay >> slash >> startMonth >> slash >> startYear;

    stringstream endStream(endDate);
    endStream >> endDay >> slash >> endMonth >> slash >> endYear;

    tm start = {0, 0, 0, startDay, startMonth - 1, startYear - 1900};
    tm end = {0, 0, 0, endDay, endMonth - 1, endYear - 1900};
    
    time_t startTime = mktime(&start);
    time_t endTime = mktime(&end);

    double difference = difftime(endTime, startTime) / (60 * 60 * 24);
    return static_cast<int>(difference);
}

void addBook() {
    Book book;
    cin.ignore();  // Ignore leftover newline character
    cout << "Enter book title: ";
    getline(cin, book.title);
    cout << "Enter book author: ";
    getline(cin, book.author);
    cout << "Enter book ISBN: ";
    getline(cin, book.ISBN);
    book. Available = true;
    bookDatabase.push_back(book);
    cout << "Book added successfully!" << endl;
}


void checkoutBook() {
    string ISBN;
    cin.ignore();  // Ignore leftover newline character
    cout << "Enter book ISBN to checkout: ";
    getline(cin, ISBN);
    for (auto& book : bookDatabase) {
        if (book.ISBN == ISBN && book. Available) {
            book. Available = false;
            purchaser borrower;
            cout << "Enter borrower name: ";
            getline(cin, borrower.name);
            cout << "Enter borrow date (DD/MM/YYYY): ";
            getline(cin, borrower.borrowDate);
            borrower.bookISBN = ISBN;
            borrower.returnDate = "";  // Initialize return date
            borrowerDatabase.push_back(borrower);
            borrowHistory.push_back(borrower);  // Add to history
            cout << "Book checked out successfully!" << endl;
            return;
        }
    }
    cout << "Book not found or not available!" << endl;
}
void searchBook() {
    string searchQuery;
    cin.ignore();  // Ignore leftover newline character
    cout << "Enter book title, author, or ISBN to search: ";
    getline(cin, searchQuery);
    bool found = false;
    for (const auto& book : bookDatabase) {
        if (book.title == searchQuery || book.author == searchQuery || book.ISBN == searchQuery) {
            cout << "Book found!" << endl;
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "ISBN: " << book.ISBN << endl;
            cout << "Availability: " << (book. Available ? "Available" : "Not Available") << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Book not found!" << endl;
    }
}


void returnBook() {
    string ISBN;
    cin.ignore();  // Ignore leftover newline character
    cout << "Enter book ISBN to return: ";
    getline(cin, ISBN);
    for (auto& book : bookDatabase) {
        if (book.ISBN == ISBN && !book. Available) {
            book. Available = true;
            for (auto it = borrowerDatabase.begin(); it != borrowerDatabase.end(); ++it) {
                if (it->bookISBN == ISBN) {
                    cout << "Enter return date (DD/MM/YYYY): ";
                    getline(cin, it->returnDate);
                    // Update the return date in the borrow history
                    for (auto& record : borrowHistory) {
                        if (record.bookISBN == ISBN && record.name == it->name && record.borrowDate == it->borrowDate) {
                            record.returnDate = it->returnDate;
                            break;
                        }
                    }
                    borrowerDatabase.erase(it);
                    cout << "Book returned successfully!" << endl;
                    return;
                }
            }
        }
    }
    cout << "Book not found or not borrowed!" << endl;
}

void calculateFine() {
    string ISBN;
    cin.ignore();  // Ignore leftover newline character
    cout << "Enter book ISBN to calculate fine: ";
    getline(cin, ISBN);
    for (const auto& record : borrowHistory) {
        if (record.bookISBN == ISBN) {
            if (record.returnDate.empty())
             {
                cout << "Book has not been returned yet!" << endl;
                return;
            }

            int daysOverdue = daysBetweenDates(record.borrowDate, record.returnDate);

            if (daysOverdue > 0) 
            {
                int fine = daysOverdue * 5;
                cout << "Fine: Rs. "  << fine << endl;
            } else {
                cout << "No fine!" << endl;
            }
            return;
        }
    }
    cout << "Book not found or not borrowed!" << endl;
}

int main() {
    int choice;
    while (true) 
    {
        cout << "Library Management System" << endl;
        cout << "1. Add book" << endl;
        cout << "2. Search book" << endl;
        cout << "3. Checkout book" << endl;
        cout << "4. Return book" << endl;
        cout << "5. Calculate fine" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                checkoutBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                calculateFine();
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}