#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
private:
    string Title;
    string Author;
    int PublicationYear;
    int BookID;
    bool b_IsBorrowed;
    
public:
    Book (string title, string author, int publicationYear, int bookID, bool isBorrowed) {
        Title = title;
        Author = author;
        PublicationYear = publicationYear;
        BookID = bookID;
        b_IsBorrowed = isBorrowed;
    }

    bool IsBorrowed() {
        return b_IsBorrowed;
    }

    void setBorrowed(bool isBorrowed) {
        b_IsBorrowed = isBorrowed;
    }

    string getTitle() {
        return Title;
    }
    string getAuthor() {
        return Author;
    }
    int getPublicationYear() {
        return PublicationYear;
    }
    int getBookID() {
        return BookID;
    }
    
}; 

class Novel:public Book {
public:
    string Genre;
    Novel(string title, string author, int publicationYear, int bookID, string genre):Book(title, author, publicationYear, bookID, false) {
        Genre = genre;
    }
};

class Textbook:public Book {
public:
    string Subject;
    Textbook(string title, string author, int publicationYear, int bookID, string subject):Book(title, author, publicationYear, bookID, false) {
        Subject = subject;
    }
};

class Library {
private:
    vector<Book*> books;
    public:
        void addBook (Book *book) {
            books.push_back(book);
        }

        void showAllbooks() {
            cout << "Books in the Library: " << endl;
            for (int i = 0; i < books.size(); i++) {
                cout << "Title:" << books[i]->getTitle() << ", Author:" << books[i]->getAuthor() << ", Year:" << books[i]->getPublicationYear() << ", ID:" << books[i]->getBookID() << endl;
            }
        }

        void borrowBook (int bookID) {
            for (int i =0; i < books.size(); i++) {
                if (books[i]->getBookID() == bookID) {
                    if (!books[i]->IsBorrowed()) {
                        books[i]->setBorrowed(true);
                        cout << "You have successfully borrowed the book: " << books[i]->getTitle() << endl;
                    }
                }
            }
        }

        void returnBook (int bookID) {
            for (int i =0; i < books.size(); i++) {
                if (books[i]->getBookID() == bookID) {
                    if (books[i]->IsBorrowed()) {
                        books[i]->setBorrowed(false);
                        cout << "You have successfully returned the book: " << books[i]->getTitle() << endl;
                    }
                }
            }
        }
};

int main() {

    Library library;

    library.addBook(new Novel("The Great Gatsby", "F. Scott Fitzgerald", 1925, 1, "Fiction"));
    library.addBook(new Textbook("Introduction to Algorithms", "Thomas H. Cormen", 2009, 2, "Computer Science"));
    library.addBook(new Novel("To Kill a Mockingbird", "Harper Lee", 1960, 3, "Fiction"));
    library.addBook(new Textbook("Physics for Scientists and Engineers", "Raymond A. Serway", 2013, 4, "Physics"));


    library.showAllbooks();

    
    bool programeRunning = true;
    while (programeRunning) {
    cout << "1. Borrow a book" << endl;
    cout << "2. Return a book" << endl;
    cout << "3. Exit" << endl;
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch(choice) {
        case 1:
            int bookID;
            cout << "Enter the Book ID you want to borrow: ";
            cin >> bookID;
            library.borrowBook(bookID);
            break;
        case 2:
            cout << "Enter the Book ID you want to return: ";
            cin >> bookID;
            library.returnBook(bookID);
            break;
        case 3:
            cout << "Exiting the program. Goodbye!" << endl;
            programeRunning = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
    }


    return 0;




}