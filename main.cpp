#include <iostream>
#include <memory.h>
#include <fstream>

using namespace std;

struct student_info {
    string first_name;
    string last_name;
    string course;
    string group;
};

struct book_info {
    string title;
    string author;
    double price = 0.0;
};


int write_info_to_file();

int backup_library();

int main() {
    if (write_info_to_file() >= 0) {
        backup_library();
    } else {
        return -1;
    }
}

int write_info_to_file() {

    student_info student;
    student_info *student_pointer;
    student_pointer = &student;

    book_info book;
    book_info *book_pointer;
    book_pointer = &book;

    cout << "Please enter first name" << endl;
    getline(cin, student_pointer->first_name);

    cout << "Please enter last name" << endl;
    getline(cin, student_pointer->last_name);

    cout << "Please enter course" << endl;
    getline(cin, student_pointer->course);

    cout << "Please enter group" << endl;
    getline(cin, student_pointer->group);

    cout << "Book bought by student" << endl;
    cout << "Enter title of book" << endl;
    getline(cin, book_pointer->title);

    cout << "Enter author of book" << endl;
    getline(cin, book_pointer->author);

    string price_text;
    cout << "Enter book price" << endl;
    cin >> price_text;

    double price;
    try {
        price = stod(price_text);
    } catch (int i) {
        cout << "Wrong price number format! Please enter valid parameters - number!\n>";
        return -1;
    }

    book_pointer->price = price;

//    fstream binary_file("library.bin", ios::out | ios::binary | ios::app);
//    binary_file << student_pointer << book_pointer;
//    binary_file.close();

    ofstream library_file;
    library_file.open("library.txt", ios::app);
    library_file << (*student_pointer).first_name;
//    library_file << student_pointer->last_name;
//    library_file << student_pointer->group;
    library_file.close();

    return 0;
}

int backup_library() {

    char *source_file_path = "library.bin";
    char *dest_file_path = "library_backup.bin";

    char buf[BUFSIZ];
    size_t size;

    FILE *source = fopen(source_file_path, "rb");
    if (source == NULL) {
        cout << "Failed to open source file for path - " << source_file_path << endl;
        return -1;
    }
    FILE *dest = fopen(dest_file_path, "wb");
    if (dest == NULL) {
        cout << "Failed to open destination file for path - " << dest_file_path << endl;
        return -1;
    }

    // feof(FILE* dest_file_path)
    while (size = fread(buf, 1, BUFSIZ, source)) {
        fwrite(buf, 1, size, dest);
    }

    fclose(source);
    fclose(dest);

    return 0;
}