#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure Definitions
typedef struct {
    int id;
    char name[50];
    char designation[50];
    float salary;
    int projectCount;
    char projects[10][50];
    char projectDates[10][20];
} Employee;

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Inventory;

typedef struct {
    int id;
    char name[50];
    float budget;
    float expenses;
} Project;

// Global Variables
Employee employees[100];
Inventory inventory[100];
Project projects[100];
int employeeCount = 0, inventoryCount = 0, projectCount = 0;

// Function Prototypes
void addEmployee();
void assignProjectToEmployee();
void editEmployee();
void displayEmployeeDetails();
void addInventoryItem();
void updateInventoryItem();
void displayInventory();
void addProject();
void assignInventoryToProject();
void displayProjectDetails();
void calculateProfitOrLoss();
void displayMenu();

int main() {
    displayMenu();
    return 0;
}

// Menu Display
void displayMenu() {
    int choice;
    while (1) {
        printf("\n--- Business Management System ---\n");
        printf("1. Add Employee\n");
        printf("2. Assign Project to Employee\n");
        printf("3. Edit Employee\n");
        printf("4. Display Employee Details\n");
        printf("5. Add Inventory Item\n");
        printf("6. Update Inventory Item\n");
        printf("7. Display Inventory\n");
        printf("8. Add Project\n");
        printf("9. Assign Inventory to Project\n");
        printf("10. Display Project Details\n");
        printf("11. Calculate Profit or Loss\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: assignProjectToEmployee(); break;
            case 3: editEmployee(); break;
            case 4: displayEmployeeDetails(); break;
            case 5: addInventoryItem(); break;
            case 6: updateInventoryItem(); break;
            case 7: displayInventory(); break;
            case 8: addProject(); break;
            case 9: assignInventoryToProject(); break;
            case 10: displayProjectDetails(); break;
            case 11: calculateProfitOrLoss(); break;
            case 12: exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function Implementations
void addEmployee() {
    Employee emp;
    printf("\nEnter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", emp.name);
    printf("Enter Designation: ");
    scanf(" %[^\n]", emp.designation);
    printf("Enter Salary: ");
    scanf("%f", &emp.salary);
    emp.projectCount = 0;
    employees[employeeCount++] = emp;
    printf("Employee added successfully!\n");
}

void assignProjectToEmployee() {
    int empId, projId, i;
    char date[20];
    printf("\nEnter Employee ID: ");
    scanf("%d", &empId);
    printf("Enter Project ID: ");
    scanf("%d", &projId);
    printf("Enter Date (DD/MM/YYYY): ");
    scanf(" %[^\n]", date);

    for (i = 0; i < employeeCount; i++) {
        if (employees[i].id == empId) {
            strcpy(employees[i].projects[employees[i].projectCount], projects[projId].name);
            strcpy(employees[i].projectDates[employees[i].projectCount], date);
            employees[i].projectCount++;
            printf("Project assigned successfully!\n");
            return;
        }
    }
    printf("Employee not found.\n");
}

void editEmployee() {
    int empId, i;
    printf("\nEnter Employee ID to Edit: ");
    scanf("%d", &empId);
    for (i = 0; i < employeeCount; i++) {
        if (employees[i].id == empId) {
            printf("Editing details for %s\n", employees[i].name);
            printf("Enter New Name: ");
            scanf(" %[^\n]", employees[i].name);
            printf("Enter New Designation: ");
            scanf(" %[^\n]", employees[i].designation);
            printf("Enter New Salary: ");
            scanf("%f", &employees[i].salary);
            printf("Employee updated successfully!\n");
            return;
        }
    }
    printf("Employee not found.\n");
}

void displayEmployeeDetails() {
    int i, j;
    printf("\n--- Employee Details ---\n");
    for (i = 0; i < employeeCount; i++) {
        printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n", employees[i].id, employees[i].name, employees[i].designation, employees[i].salary);
        printf("Projects Worked:\n");
        for (j = 0; j < employees[i].projectCount; j++) {
            printf("  %s on %s\n", employees[i].projects[j], employees[i].projectDates[j]);
        }
    }
}

void addInventoryItem() {
    Inventory inv;
    printf("\nEnter Item ID: ");
    scanf("%d", &inv.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", inv.name);
    printf("Enter Quantity: ");
    scanf("%d", &inv.quantity);
    printf("Enter Price: ");
    scanf("%f", &inv.price);
    inventory[inventoryCount++] = inv;
    printf("Inventory item added successfully!\n");
}

void updateInventoryItem() {
    int itemId, i, newQuantity;
    printf("\nEnter Item ID to Update: ");
    scanf("%d", &itemId);
    for (i = 0; i < inventoryCount; i++) {
        if (inventory[i].id == itemId) {
            printf("Current Quantity: %d\n", inventory[i].quantity);
            printf("Enter New Quantity: ");
            scanf("%d", &newQuantity);
            inventory[i].quantity = newQuantity;
            printf("Inventory updated successfully!\n");
            return;
        }
    }
    printf("Item not found.\n");
}

void displayInventory() {
    int i;
    printf("\n--- Inventory Details ---\n");
    for (i = 0; i < inventoryCount; i++) {
        printf("ID: %d, Name: %s, Quantity: %d, Price: %.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}

void addProject() {
    Project proj;
    printf("\nEnter Project ID: ");
    scanf("%d", &proj.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", proj.name);
    printf("Enter Budget: ");
    scanf("%f", &proj.budget);
    proj.expenses = 0;
    projects[projectCount++] = proj;
    printf("Project added successfully!\n");
}

void assignInventoryToProject() {
    int projId, itemId, quantity, i;
    printf("\nEnter Project ID: ");
    scanf("%d", &projId);
    printf("Enter Item ID: ");
    scanf("%d", &itemId);
    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    for (i = 0; i < inventoryCount; i++) {
        if (inventory[i].id == itemId && inventory[i].quantity >= quantity) {
            inventory[i].quantity -= quantity;
            projects[projId].expenses += quantity * inventory[i].price;
            printf("Inventory assigned to project successfully!\n");
            return;
        }
    }
    printf("Insufficient inventory or item not found.\n");
}

void displayProjectDetails() {
    int i;
    printf("\n--- Project Details ---\n");
    for (i = 0; i < projectCount; i++) {
        printf("ID: %d, Name: %s, Budget: %.2f, Expenses: %.2f\n", projects[i].id, projects[i].name, projects[i].budget, projects[i].expenses);
    }
}

void calculateProfitOrLoss() {
    float totalExpenses = 0, totalBudget = 0;
    int i;

    for (i = 0; i < projectCount; i++) {
        totalBudget += projects[i].budget;
        totalExpenses += projects[i].expenses;
    }

    printf("\n--- Financial Summary ---\n");
    printf("Total Budget: %.2f\n", totalBudget);
    printf("Total Expenses: %.2f\n", totalExpenses);

    if (totalBudget > totalExpenses) {
        printf("Profit: %.2f\n", totalBudget - totalExpenses);
    } else if (totalBudget < totalExpenses) {
        printf("Loss: %.2f\n", totalExpenses - totalBudget);
    } else {
        printf("Break-even: No profit or loss.\n");
    }
}
