#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employee_data.dat"
#define MAX_EMPLOYEES 100

// Structure to represent an employee
struct Employee {
    int id;
    char name[50];
    float salary;
};

// Function prototypes
void addEmployee();
void searchEmployee(int id);
void updateEmployee(int id);
void deleteEmployee(int id);
void displayAllEmployees();

int main() {
    int choice;
    while (1) {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Search Employee\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Display All Employees\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2: {
                int id;
                printf("Enter employee ID to search: ");
                scanf("%d", &id);
                searchEmployee(id);
                break;
            }
            case 3: {
                int id;
                printf("Enter employee ID to update: ");
                scanf("%d", &id);
                updateEmployee(id);
                break;
            }
            case 4: {
                int id;
                printf("Enter employee ID to delete: ");
                scanf("%d", &id);
                deleteEmployee(id);
                break;
            }
            case 5:
                displayAllEmployees();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Function to add a new employee
void addEmployee() {
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Employee emp;
    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter employee name: ");
    scanf("%s", emp.name);
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(struct Employee), 1, file);
    fclose(file);
}

// Function to search for an employee by ID
void searchEmployee(int id) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Employee emp;
    int found = 0;

    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        if (emp.id == id) {
            printf("Employee found:\n");
            printf("ID: %d\nName: %s\nSalary: %.2f\n", emp.id, emp.name, emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found!\n", id);
    }

    fclose(file);
}

// Function to update employee details
void updateEmployee(int id) {
    FILE *file = fopen(FILENAME, "r+b");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Employee emp;
    int found = 0;

    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        if (emp.id == id) {
            printf("Enter new name: ");
            scanf("%s", emp.name);
            printf("Enter new salary: ");
            scanf("%f", &emp.salary);

            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&emp, sizeof(struct Employee), 1, file);
            found = 1;
            printf("Employee details updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found!\n", id);
    }

    fclose(file);
}

// Function to delete an employee
void deleteEmployee(int id) {
    FILE *file = fopen(FILENAME, "r+b");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Employee emp;
    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(file);
        return;
    }

    int found = 0;

    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        if (emp.id == id) {
            printf("Employee deleted successfully.\n");
            found = 1;
        } else {
            fwrite(&emp, sizeof(struct Employee), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (!found) {
        printf("Employee with ID %d not found!\n", id);
    }
}

// Function to display all employees
void displayAllEmployees() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Employee emp;
    printf("Employee Details:\n");
    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
    }

    fclose(file);
}

