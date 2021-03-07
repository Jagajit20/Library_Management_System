#include <bits/stdc++.h> 
using namespace std;
void mainMenu();
void returnMenu();
class book {
    string bookname;
    string bookid;
    string authorname;
    public:
    void createBook() {
        ifstream fi;
        string tempbook;
        string tempid;
        string tempauthor;
        int flag = 0;
        cout<<"Enter the bookname: ";
        cin>>this->bookname;
        cout<<"Enter the id to be assigned to the book: ";
        cin>>this->bookid;
        cout<<"Enter the author's name: ";
        cin>>this->authorname;
        fi.open("book.txt", ios::in);
        while(!fi.eof()) {
            getline(fi, tempbook, ',');
            getline(fi, tempid, ',');
            if(tempid == this->bookid) {
                flag = 1;
                cout<<"Book Already exists!\n";
                break;
            }
        }
        fi.close();
        ofstream fo;
        fo.open("book.txt", ios::app);
        if(flag != 1) {
            fo<<this->bookname<<','<<this->bookid<<','<<this->authorname<<'\n';
            cout<<"Book has been added to the library.\n";
        }
        fo.close();
    }
    void showBooks() {
        ifstream fi("book.txt");
        string tempbook;
        string tempid;
        string tempauthor;
        system("cls");
        cout<<"Record of books: \n\n";
        while(!fi.eof()) {
            getline(fi, tempbook, ',');
            getline(fi, tempid, ',');
            getline(fi, tempauthor, '\n');
            cout<<"Name of the book: "<<tempbook<<endl;
            cout<<"Id of the book: "<<tempid<<endl;
            cout<<"Author of the book: "<<tempauthor<<endl;
            cout<<endl;
        }
        fi.close();
        system("pause");
    }
    bool getBook(string bkid) {
        ifstream fi("book.txt");
        string tempbook;
        string tempid;
        string tempauthor;
        while(!fi.eof()) {
            getline(fi, tempbook, ',');
            getline(fi, tempid, ',');
            getline(fi, tempauthor, '\n');
            if(tempid == bkid) {
                return true;
            }
        }
        fi.close();
        return false;
    }
    void deletebook() {
        cout<<"Enter the id of the book you want to delete: ";
        cin>>bookid;
        int flag = 0;
        ifstream fi("book.txt");
        ofstream file_r("book2.txt", ios::app);
        string tempbook;
        string tempid;
        string tempauthor;
        while(!fi.eof()) {
            getline(fi, tempbook, ',');
            if(tempbook == "\n")
                break;
            getline(fi, tempid, ',');
            fi>>tempauthor;
            if(tempid != bookid) {
                file_r<<tempbook<<','<<tempid<<','<<tempauthor;
            }
            else {
                flag = 1;
            }
        }
        file_r<<'\n';
        file_r.close();
        fi.close();
        if(flag == 0)
            cout<<"Book not found! Check the book id again.\n";
        remove("book.txt");
        rename("book2.txt", "book.txt");
    }
};
class student {
    string studentname;
    string studentid;
    int booksIssued;
    public:
    bool verifyStudent(string stuid) {
        ifstream fi;
        fi.open("student.txt", ios::in);
        //string buffer_name;
        string buffer_id;  // stores required student id
        string buffer;   // stores unwanted data
        bool flag = false;
        while(!fi.eof()) {
            getline(fi, buffer, ',');
            getline(fi, buffer_id, ',');
            getline(fi, buffer, '\n');
            if(buffer_id == stuid) {
                flag = true;
                break;
            }
        }
        return flag;
    }
    void createRecord() {
        cout<<"Enter name of the student: ";
        cin>>this->studentname;
        cout<<"Enter student id: ";
        cin>>this->studentid;
        this->booksIssued = 0;
        if(verifyStudent(this->studentid) == true) {
            cout<<"RECORD ALREADY EXISTS.";
        }
        else {
            ofstream fio("student.txt", ios::app);
            if(fio) {
                fio<<this->studentname<<','<<this->studentid<<','<<this->booksIssued<<'\n';
            }
            else {
                cout<<"FILE DOESN'T EXIST!\n";
            }
            fio.close();
        }
    }
    int numberOfBooksIssued(string stuid) {
        ifstream fi("student.txt");
        string buffer_num;
        string buffer_id;
        int found = 1;
        while(!fi.eof()) {
            getline(fi, buffer_id, ',');
            getline(fi, buffer_id, ',');
            getline(fi, buffer_num, '\n');
            if(buffer_id == stuid) {
                if(buffer_num == "0") {
                    found = 0;
                }
                break;
            }
        }
        fi.close();
        return found;
    }
    void issueBook() {
        // student obj;
        // string stuId;
        cout<<"Enter student Id: ";
        cin>>studentid;
        if(verifyStudent(studentid) == false) {
            cout<<"Student record doesnt exist.\n";
        }
        else { 
            book bk;
            string bookid;
            cout<<"Enter book id: ";
            cin>>bookid;
            if(bk.getBook(bookid) == false) {
                cout<<"Book doesn't exist!";
                return;
            }
            if(numberOfBooksIssued(studentid) == 0) {
                fstream fio("student.txt");
                fstream file_r("student2.txt", ios::app);
                string buffer_num;
                string buffer_name;
                string buffer_id;
                while(!fio.eof()) {
                    getline(fio, buffer_name, ',');
                    if(buffer_name == "\n")
                        break;
                    file_r<<buffer_name<<',';
                    getline(fio, buffer_id, ',');
                    file_r<<buffer_id<<',';
                    fio>>buffer_num;
                    if(buffer_id == studentid) {
                        file_r<<"1";
                        cout<<buffer_name<<", you can get the book now! Return it within the next 15 days";
                        //break;
                    }
                    else {
                        file_r<<buffer_num;
                    }
                }

                file_r<<'\n';
                fio.close();
                file_r.close();
                char oldname[] = "student2.txt";
                char newname[] = "student.txt";
                remove(newname);
                rename(oldname, newname);
            }
            else {
                cout<<"Already a book is issued! Return the book to get another book!\n";
            }
        }
    }
    void returnBook() {
        cout<<"Enter your student Id: ";
        cin>>studentid;
        if(verifyStudent(studentid) == false) {
            cout<<"Student record doesnt exist.\n";
        }
        else {
            if(numberOfBooksIssued(studentid) == 1) {
                fstream fio("student.txt");
                fstream file_r("student2.txt", ios::app);
                string buffer_num;
                string buffer_name;
                string buffer_id;
                while(!fio.eof()) {
                    getline(fio, buffer_name, ',');
                    if(buffer_name == "\n")
                        break;
                    file_r<<buffer_name<<',';
                    getline(fio, buffer_id, ',');
                    file_r<<buffer_id<<',';
                    fio>>buffer_num;
                    if(buffer_id == studentid) {
                        file_r<<"0";
                        //break;
                    }
                    else {
                        file_r<<buffer_num;
                    }
                }
                file_r<<'\n';
                fio.close();
                file_r.close();
                char oldname[] = "student2.txt";
                char newname[] = "student.txt";
                remove(newname);
                rename(oldname, newname);
            }
            else {
                cout<<"No book has been issued! Check again.\n";
            }
        }
    }
};
void returnMenu() {
    cout<<"\nEnter your choice: \n";
    cout<<"1. Main menu\n";
    cout<<"2. Exit\n";
    cout<<"Your Choice: ";
    char ch;
    cin>>ch;
    switch (ch)
    {
        case '1':
            mainMenu();
            break;
        case '2':
            exit(0);
    }
}
/*
void adminLogin() {
    book addbook;
    string ch;
    do {
        addbook.createBook();
        cout<<"Do you want to add another book? ";
        cin>>ch;
    } while(ch == "yes" || ch == "Yes" || ch == "YES");
    returnMenu();
}
*/
class admin {
    string adminid;
    string adminpassword;
    string adminname;
    //static bool login_flag;
    public:
        void login() {
            int flagId = 0, flagPass = 0;
            cout<<"Enter your admin Id: ";
            cin>>adminid;
            cout<<"Enter your password: ";
            cin>>adminpassword;
            ifstream fio("admin.txt", ios::in);
            string tempid, temppass, tempname;
            while(!fio.eof()) {
                getline(fio, tempid, ',');
                getline(fio, tempname, ',');
                getline(fio, temppass, '\n');
                if(tempid == adminid) {
                    flagId = 1;
                    if(temppass == adminpassword) {
                        flagPass = 1;
                    }
                    break;
                }
            }
            if(flagId == 1) {
                if(flagPass == 1) {
                    system("cls");
                    cout<<"Welcome back "<<tempname<<"!\n\n";
                    // login_flag = true;
                    adminMenu();
                }
                else {
                    cout<<"Login failed. Incorrect password!\n";
                    cout<<"1. Sign in\n";
                    cout<<"2. Main Menu\n";
                    char ch;
                    cin>>ch;
                    switch(ch) {
                        case '1': login();
                                  break;
                        case '2': mainMenu();
                                  break;
                    }
                }
            }
            else {
                cout<<"The id entered is incorrect. Try again.\n";
            }
        }
        void adminMenu() {
            cout<<"1. Issue book to students\n";
            cout<<"2. Retrieve book from students\n";
            cout<<"3. Add new student to the student record\n";
            cout<<"4. Add new book to the book record\n";
            cout<<"5. Main Menu\n";
            cout<<"6. Add new admin\n";
            cout<<"7. Delete book\n";
            cout<<"Your choice: ";
            char ch;
            cin>>ch;
            book bk;
            student st;
            switch(ch) {
                case '1':   st.issueBook();
                            break;
                case '2':   st.returnBook();
                            break;
                case '3':   st.createRecord();
                            break;
                case '4':   bk.createBook();
                            break;
                case '5':   mainMenu;
                            break;
                case '6':   addAdmin();
                            break;
                case '7':   bk.deletebook();
                            break;
            }
            system("pause");
        }
        void addAdmin() {
            ifstream fi("admin.txt", ios::in);
            ofstream fo("admin.txt", ios::app);
            cout<<"Enter the name of admin: ";
            cin>>adminname;
            cout<<"Enter the id to be assigned to the admin: ";
            cin>>adminid;
            cout<<"Enter the password for the new admin: ";
            cin>>adminpassword;
            string tempid, temppass, tempname;
            while(!fi.eof()) {
                getline(fi, tempid, ',');
                getline(fi, tempname, ',');
                getline(fi, temppass, '\n');
                if(tempid == adminid) {
                    cout<<"Admin details already exist!\n";
                    return;
                }
            }
            fo<<adminid<<','<<adminname<<','<<adminpassword<<'\n';
            fo.close();
            fi.close();
        }        

};
void registerStudent() {
    student addstudent;
    addstudent.createRecord();
}
void studentMenu() {
    system("cls");
    student st;
    cout<<"ENTER YOUR CHOICE: \n";
    cout<<"1. ISSUE BOOK\n";
    cout<<"2. RETURN BOOK\n";
    cout<<"3. REGISTER FOR ISSUING/RETURNING BOOK\n";
    cout<<"4. GO BACK TO MAIN MENU\n";
    cout<<"YOUR CHOICE: ";
    char ch;
    cin>>ch;
    switch(ch) {
        case '1':
            st.issueBook();
            break;
        case '2':
            st.returnBook();
            break;
        case '3':
            registerStudent();
            break;
        case '4': mainMenu();
            break;
    }
}

void mainMenu() {
    while(true) {
        book bk;
        admin ad;
        system("cls");
        cout<<"WELCOME TO THE LIBRARY MANAGEMENT SYSTEM\n";
        cout<<"ENTER YOUR CHOICE: \n";
        cout<<"1. STUDENT MENU\n";
        cout<<"2. SHOW BOOKS\n";
        cout<<"3. ADMIN LOGIN\n";
        cout<<"4. EXIT\n";
        cout<<"Your Choice: ";
        char ch;
        cin>>ch;
        switch(ch) {
        case '1':
            studentMenu();
            break;
        case '2':
            bk.showBooks();
            break;
        case '3':
            ad.login();
            break;
        case '4':
            exit(0); 
            break;
        }
    }
}

int main() {
    mainMenu();
    return 0;
}