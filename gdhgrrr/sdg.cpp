#include <bits/stdc++.h>
#include <conio.h>

using namespace std;

unordered_map<string, string> readUserDatafromfilelogin(const string& filename) {
    unordered_map<string, string> a;
    fstream infile(filename, ios::in);
    string username, password;
    if (infile.is_open()) {
        while (infile >> username >> password) {
            a[username] = password;
        }
        infile.close();
    } else {
        cout << "Error opening file for reading!" << endl;
    }
    return a;
}

void writeUserDatatofilelogin(const string& filename, const unordered_map<string, string>& a) {
    fstream outfile(filename, ios::out);
    if (outfile.is_open()) {
        for (const auto& pair : a) {
            outfile << pair.first << " " << pair.second << "\n";
        }
        outfile.close();
    } else {
        cout << "Error opening file for writing!" << endl;
    }

}
struct Student {
    int rollNumber;
    char name[50];
    float cgpa;
    char gender;
    struct Student *next;
};

int boysCount = 0;
int girlsCount = 0;

void writeStudentsToFile(struct Student *head) {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    struct Student *current = head;
    while (current != NULL) {
        fprintf(file, "%d %s %.2f %c\n", current->rollNumber, current->name, current->cgpa, current->gender);
        current = current->next;
    }
    fclose(file);
}

void addStudent(struct Student **head, int rollNumber, const char *name, float cgpa, char gender) {
    while (1) {
        int isDuplicate = 0;
        for (struct Student *current = *head; current != NULL; current = current->next) {
            if (current->rollNumber == rollNumber) {
                printf("Error: Roll number %d already exists. Please enter a unique roll number.\n", rollNumber);
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            break;
        }

        printf("Enter a new roll number: ");
        if (scanf("%d", &rollNumber) != 1 || rollNumber <= 0) {
            printf("Invalid input. Roll number must be a positive integer.\n");
            while (getchar() != '\n');
        }
    }

    struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newStudent->rollNumber = rollNumber;
    strncpy(newStudent->name, name, sizeof(newStudent->name) - 1);
    newStudent->name[sizeof(newStudent->name) - 1] = '\0';
    newStudent->cgpa = cgpa;
    newStudent->gender = gender;

    if (gender == 'M' || gender == 'm') {
        boysCount++;
    } else if (gender == 'F' || gender == 'f') {
        girlsCount++;
    }

    newStudent->next = *head;
    *head = newStudent;

    writeStudentsToFile(*head);

    printf("Student added successfully.\n");
}

void findStudentByRollNumber(struct Student *head, int rollNumber) {
    while (head != NULL) {
        if (head->rollNumber == rollNumber) {
            printf("\nStudent found:\n");
            printf("Roll Number: %d, Name: %s, CGPA: %.2f, Gender: %c\n", head->rollNumber, head->name, head->cgpa, head->gender);
            return;
        }
        head = head->next;
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

int countStudents(struct Student *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

void deleteStudent(struct Student **head, int rollNumber) {
    struct Student *current = *head;
    struct Student *prev = NULL;

    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            if (current->gender == 'M' || current->gender == 'm') {
                if (boysCount > 0) {
                    boysCount--;
                }
            } else if (current->gender == 'F' || current->gender == 'f') {
                if (girlsCount > 0) {
                    girlsCount--;
                }
            }
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Student with roll number %d deleted successfully.\n", rollNumber);

            writeStudentsToFile(*head);

            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

void updateStudent(struct Student **head, int rollNumber) {
    int found = 0;
    struct Student *current = *head;

    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            found = 1;
            int choice;
            printf("\nUpdate Menu:\n");
            printf("1. Update Name\n");
            printf("2. Update CGPA\n");
            printf("3. Update Gender\n");
            printf("4. Exit\n");
            printf("Enter your choice: ");

            if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                while (getchar() != '\n');
                continue;
            }

            switch (choice) {
                case 1:
                    printf("Enter new name: ");
                    cin.ignore();  // Ignore any leftover newline character from previous input
                    cin.getline(current->name, sizeof(current->name));
                    break;
                case 2:
                    do {
                        printf("Enter new CGPA: ");
                        if (scanf("%f", &current->cgpa) != 1 || current->cgpa < 0 || current->cgpa > 4) {
                            printf("Invalid input. CGPA should be between 0 and 4.\n");
                            while (getchar() != '\n');
                        } else {
                            break;
                        }
                    } while (1);
                    break;
                case 3:
                    do {
                        printf("Enter new gender (M/F): ");
                        scanf(" %c", &current->gender);
                        if (current->gender != 'M' && current->gender != 'm' && current->gender != 'F' && current->gender != 'f') {
                            printf("Invalid input. Please enter 'M' or 'F'.\n");
                            while (getchar() != '\n');
                        } else {
                            break;
                        }
                    } while (1);
                    break;
                case 4:
                    break;
            }

            writeStudentsToFile(*head);
            printf("Student with roll number %d updated successfully.\n", rollNumber);
            return;
        }
        current = current->next;
    }

    if (!found) {
        printf("Student with roll number %d not found.\n", rollNumber);
    }
}

void printGenderCounts() {
    printf("\nCount of Students:\n");
    printf("Boys: %d\n", boysCount);
    printf("Girls: %d\n", girlsCount);
}

void printStudents(struct Student *head) {
    printf("\nList of Students:\n");
    struct Student *current = head;
    while (current != NULL) {
        printf("Roll Number: %d, Name: %s, CGPA: %.2f, Gender: %c\n", current->rollNumber, current->name, current->cgpa, current->gender);
        current = current->next;
    }
}

void freeList(struct Student *head) {
    while (head != NULL) {
        struct Student *temp = head;
        head = head->next;
        free(temp);
    }
}

void loadStudentsFromFile(struct Student **head) {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    struct Student *newStudent;
    while (!feof(file)) {
        newStudent = (struct Student *)malloc(sizeof(struct Student));
        if (newStudent == NULL) {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        if (fscanf(file, "%d %49s %f %c", &newStudent->rollNumber, newStudent->name, &newStudent->cgpa, &newStudent->gender) == 4) {
            newStudent->next = *head;
            *head = newStudent;

            if (newStudent->gender == 'M' || newStudent->gender == 'm') {
                boysCount++;
            } else if (newStudent->gender == 'F' || newStudent->gender == 'f') {
                girlsCount++;
            }
        } else {
            free(newStudent);
        }
    }
    fclose(file);
}

void menu() {
    struct Student *head = NULL;
    loadStudentsFromFile(&head);

    int rollNumber, choice;
    char name[50], gender;
    float cgpa;

    do {
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Find Student by Roll Number\n");
        printf("3. Count of Students\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Print Gender Counts\n");
        printf("7. Print Students\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                do {
                    printf("Enter student data:\n");
                    printf("Roll Number: ");
                    if (scanf("%d", &rollNumber) != 1 || rollNumber <= 0) {
                        printf("Invalid input. Roll number must be a positive integer.\n");
                        while (getchar() != '\n'); // Clear input buffer
                    } else {
                        break;
                    }
                } while (1);

                printf("Name: ");
                while (getchar() != '\n'); // clear newline character left in buffer
                cin.getline(name, sizeof(name));

                do {
                    printf("CGPA: ");
                    if (scanf("%f", &cgpa) != 1 || cgpa < 0 || cgpa > 4) {
                        printf("Invalid input. CGPA should be between 0 and 4.\n");
                        while (getchar() != '\n'); // Clear input buffer
                    } else {
                        break;
                    }
                } while (1);

                do {
                    printf("Gender (M/F): ");
                    scanf(" %c", &gender);
                    if (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f') {
                        printf("Invalid input. Gender should be 'M' or 'F'.\n");
                        while (getchar() != '\n'); 
                    } else {
                        break;
                    }
                } while (1);

                addStudent(&head, rollNumber, name, cgpa, gender);
                break;

            case 2:
                printf("Enter roll number to find: ");
                if (scanf("%d", &rollNumber) != 1 || rollNumber <= 0) {
                    printf("Invalid input. Roll number must be a positive integer.\n");
                    break;
                }
                findStudentByRollNumber(head, rollNumber);
                break;

            case 3:
                printf("Total number of students: %d\n", countStudents(head));
                break;

            case 4:
                printf("Enter roll number to delete: ");
                if (scanf("%d", &rollNumber) != 1 || rollNumber <= 0) {
                    printf("Invalid input. Roll number must be a positive integer.\n");
                    break;
                }
                deleteStudent(&head, rollNumber);
                break;

            case 5:
                printf("Enter roll number to update: ");
                if (scanf("%d", &rollNumber) != 1 || rollNumber <= 0) {
                    printf("Invalid input. Roll number must be a positive integer.\n");
                    break;
                }
                updateStudent(&head, rollNumber);
                break;

            case 6:
                printGenderCounts();
                break;

            case 7:
                printStudents(head);
                break;

            case 8:
                freeList(head);
                printf("Program exited.\n");
                return;

            default:
                printf("Invalid choice. Please enter a valid option (1 to 8).\n");
        }

    } while (1);
}

int main() {
    string filename = "userdata.txt";
    unordered_map<string, string> a = readUserDatafromfilelogin(filename);

    int attempt_count = 0;
    int invalid_option_count = 0;
    int existing_username_count = 0;

    while (true) {
        cout << "1. Login\n2. Register\n3. Exit\nEnter option: ";
        string option;
        cin >> option;

        if (option == "1") {
            invalid_option_count = 0;
            existing_username_count = 0;
            if (attempt_count >= 5) {
                cout << "You have tried 5 times and you cannot try anymore.\n";
                break;
            }

            cout << "Enter username: ";
            string username;
            cin >> username;

            if (a.find(username) == a.end()) {
                cout << "Invalid username\n";
                attempt_count++;
                if (attempt_count >= 3 && attempt_count < 5) {
                    cout << "Attempt " << attempt_count << " failed. " << 5 - attempt_count << " attempt(s) left.\n";
                }
                continue;
            }

            cout << "Enter password: ";
            string password;
            char ch;
            while ((ch = _getch()) != '\r') { // '\r' is carriage return (Enter key)
                if (ch == '\b') { // Handle backspace
                    if (!password.empty()) {
                        cout << "\b \b";
                        password.pop_back();
                    }
                } else {
                    password.push_back(ch);
                    cout << '*';
                }
            }
            cout << endl;

            if (a[username] == password) {
                cout << "Login successful\n";
                menu(); // Call menu function after successful login
                break;  // Exit the loop after menu completes
            } else {
                cout << "Invalid password\n";
                attempt_count++;
                if (attempt_count >= 3 && attempt_count < 5) {
                    cout << "Attempt " << attempt_count << " failed. " << 5 - attempt_count << " attempt(s) left.\n";
                }
            }
        } else if (option == "2") {
            invalid_option_count = 0;
            cout << "Enter new username: ";
            string username;
            cin >> username;

            if (a.find(username) == a.end()) {
                existing_username_count = 0;
                cout << "Enter new password: ";
                string password;
                char ch;
                while ((ch = _getch()) != '\r') { // '\r' is carriage return (Enter key)
                    if (ch == '\b') { // Handle backspace
                        if (!password.empty()) {
                            cout << "\b \b";
                            password.pop_back();
                        }
                    } else {
                        password.push_back(ch);
                        cout << '*';
                    }
                }
                cout << endl;

                a[username] = password;
                writeUserDatatofilelogin(filename, a);
                cout << "Registration successful\n";
            } else {
                cout << "Username already exists\n";
                existing_username_count++;
                if (existing_username_count >= 3 && existing_username_count < 5) {
                    cout << "Attempt " << existing_username_count << " failed. " << 5 - existing_username_count << " attempt(s) left.\n";
                } else if (existing_username_count >= 5) {
                    cout << "You have entered existing username 5 times. You cannot register anymore.\n";
                    break;
                }
            }
        } else if (option == "3") {
            invalid_option_count = 0;
            existing_username_count = 0;
            cout << "Exiting\n";
            break;
        } else {
            invalid_option_count++;
            cout << "Invalid option, please try again\n";
            if (invalid_option_count >= 3 && invalid_option_count < 5) {
                cout << "Attempt " << invalid_option_count << " failed. " << 5 - invalid_option_count << " attempt(s) left.\n";
            } else if (invalid_option_count >= 5) {
                cout << "You have entered invalid options 5 times. You cannot choose anymore.\n";
                break;
            }
        }
    }

    return 0;
}
