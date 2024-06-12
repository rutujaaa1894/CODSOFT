#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    string isbn;
    bool isAvailable;

    Book(int id, string title, string author, string isbn) 
        : id(id), title(title), author(author), isbn(isbn), isAvailable(true) {}
};

struct User {
    int id;
    string name;
    vector<int> borrowedBooks;

    User(int id, string name) : id(id), name(name) {}
};

struct Transaction {
    int userId;
    int bookId;
    time_t checkoutDate;
    time_t returnDate;

    Transaction(int userId, int bookId, time_t checkoutDate) 
        : userId(userId), bookId(bookId), checkoutDate(checkoutDate), returnDate(0) {}
};

class Library {
private:
    vector<Book> books;
    vector<User> users;
    vector<Transaction> transactions;

    Book* findBookById(int bookId) {
        for (auto &book : books) {
            if (book.id == bookId) return &book;
        }
        return nullptr;
    }

    User* findUserById(int userId) {
        for (auto &user : users) {
            if (user.id == userId) return &user;
        }
        return nullptr;
    }

public:
    void addBook(int id, string title, string author, string isbn) {
        books.emplace_back(id, title, author, isbn);
    }

    void addUser(int id, string name) {
        users.emplace_back(id, name);
    }

    void searchBook(string keyword) {
        for (const auto &book : books) {
            if (book.title.find(keyword) != string::npos || book.author.find(keyword) != string::npos || book.isbn.find(keyword) != string::npos) {
                cout << "Book ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.isbn << ", Available: " << (book.isAvailable ? "Yes" : "No") << endl;
            }
        }
    }

    void checkoutBook(int userId, int bookId) {
        Book* book = findBookById(bookId);
        User* user = findUserById(userId);
        if (book && user && book->isAvailable) {
            book->isAvailable = false;
            user->borrowedBooks.push_back(bookId);
            time_t now = time(0);
            transactions.push_back({userId, bookId, now});
            cout << "Book checked out successfully!" << endl;
        } else {
            cout << "Checkout failed. Book may not be available or user not found." << endl;
        }
    }

    void returnBook(int userId, int bookId) {
        Book* book = findBookById(bookId);
        User* user = findUserById(userId);
        if (book && user) {
            auto it = find(user->borrowedBooks.begin(), user->borrowedBooks.end(), bookId);
            if (it != user->borrowedBooks.end()) {
                user->borrowedBooks.erase(it);
                book->isAvailable = true;

                for (auto &transaction : transactions) {
                    if (transaction.userId == userId && transaction.bookId == bookId && transaction.returnDate == 0) {
                        transaction.returnDate = time(0);
                        break;
                    }
                }
                cout << "Book returned successfully!" << endl;
            } else {
                cout << "User did not borrow this book." << endl;
            }
        } else {
            cout << "Return failed. Book or user not found." << endl;
        }
    }

    void calculateFine(int userId) {
        const double finePerDay = 1.0;  // Define fine rate
        User* user = findUserById(userId);
        if (!user) {
            cout << "User not found." << endl;
            return;
        }

        double totalFine = 0.0;
        time_t now = time(0);

        for (const auto &transaction : transactions) {
            if (transaction.userId == userId && transaction.returnDate == 0) {
                double days = difftime(now, transaction.checkoutDate) / (60 * 60 * 24);
                if (days > 14) {  // Assume 14 days is the allowed borrowing period
                    totalFine += (days - 14) * finePerDay;
                }
            }
        }

        cout << "Total fine for user " << user->name << " is: $" << totalFine << endl;
    }
};

void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Search Book" << endl;
    cout << "4. Checkout Book" << endl;
    cout << "5. Return Book" << endl;
    cout << "6. Calculate Fine" << endl;
    cout << "7. Exit" << endl;
}

int main() {
    Library library;
    int choice, id;
    string title, author, name, isbn, keyword;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                cout << "Enter Book ISBN: ";
                getline(cin, isbn);
                library.addBook(id, title, author, isbn);
                break;

            case 2:
                cout << "Enter User ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter User Name: ";
                getline(cin, name);
                library.addUser(id, name);
                break;

            case 3:
                cout << "Enter keyword (Title, Author, or ISBN) to Search: ";
                cin.ignore();
                getline(cin, keyword);
                library.searchBook(keyword);
                break;

            case 4:
                cout << "Enter User ID: ";
                cin >> id;
                int bookId;
                cout << "Enter Book ID: ";
                cin >> bookId;
                library.checkoutBook(id, bookId);
                break;

            case 5:
                cout << "Enter User ID: ";
                cin >> id;
                cout << "Enter Book ID: ";
                cin >> bookId;
                library.returnBook(id, bookId);
                break;

            case 6:
                cout << "Enter User ID: ";
                cin >> id;
                library.calculateFine(id);
                break;

            case 7:
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}