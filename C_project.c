#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an expense
struct Expense {
    char category[50];
    char description[100];
    float amount;
};

// Function to add an expense
float Sum = 0;
void addExpense(struct Expense expenses[], int *numExpenses) {
    printf("Enter the category: ");
     scanf("%s", expenses[*numExpenses].category);

    printf("Enter the description: ");
     scanf("%s", expenses[*numExpenses].description);

    printf("Enter the amount: ");
    scanf("%f", &expenses[*numExpenses].amount);
    Sum = Sum + expenses[*numExpenses].amount;

    (*numExpenses)++;
}

// Function to view all expenses
void viewAllExpenses(float income,struct Expense expenses[], int numExpenses) {
    if (numExpenses == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    printf("\nAll Expenses:\n");
    printf("Category\tExpense\t\tAmount\n");
    for (int i = 0; i < numExpenses; i++) {
        printf("%-20s%-20s%-10.2f\n", expenses[i].category, expenses[i].description, expenses[i].amount);
    }

    printf("Total Income:%.2f\n",income);
    printf("Total Expenditure: %.2f\n\n", Sum);
    printf("Amount left: %.2f\n",income-Sum);
}

// Function to view expenses by category
void viewExpensesByCategory(struct Expense expenses[], int numExpenses) {
    if (numExpenses == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    char targetCategory[50];
    printf("Enter the category to view expenses: ");
    scanf("%s", targetCategory);

    float SUM = 0;
    printf("\nExpenses in Category '%s':\n", targetCategory);
    for (int i = 0; i < numExpenses; i++) {
        if (strcmp(expenses[i].category, targetCategory) == 0) {
            printf("%s: %.2f\n", expenses[i].description, expenses[i].amount);
            SUM = SUM + expenses[i].amount;
        }
    }
    printf("\nTotal for %s category is %.2f", targetCategory, SUM);
}

int main() {
    struct Expense expenses[100]; // Assume a maximum of 100 expenses
    int numExpenses = 0;
    int choice;
    float income;
    
    printf("Enter your income: ");
    scanf("%f",&income);
    do {
        printf("\nExpense Tracker Menu:\n");
        printf("1. Add Expense\n");
        printf("2. View All Expenses\n");
        printf("3. View Expenses by Category\n");
        printf("4. Plot\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense(expenses, &numExpenses);
                break;
            case 2:
                viewAllExpenses(income,expenses, numExpenses);
                break;
            case 3:
                viewExpensesByCategory(expenses, numExpenses);
                break;
            case 5:
                printf("\nExiting the Expense Tracker.\n");
                break;
            case 4:
                FILE *file = fopen("totals.txt", "w");
                if (file == NULL) {
                    printf("Error opening file!\n");
                return 1;
                }
                char categories[100][50];  // an array to store unique categories
                int num_categories = 0;  // the number of unique categories
                for (int i = 0; i < numExpenses; i++) {
        // Check if this category is already in the categories array
        int j;
        for (j = 0; j < num_categories; j++) {
            if (strcmp(expenses[i].category, categories[j]) == 0) {
                break;
            }
        }

        // If the category was not found in the categories array, add it
        if (j == num_categories) {
            strcpy(categories[num_categories], expenses[i].category);
            num_categories++;
            }
    }

  
    // For each unique category, calculate the total amount and write to the file
    for (int i = 0; i < num_categories; i++) {
        float total = 0;
        for (int j = 0; j < numExpenses; j++) {
            if (strcmp(expenses[j].category, categories[i]) == 0) {
                total += expenses[j].amount;
            }
        }
              
        fprintf(file, "%s: %.2f\n", categories[i], total);
    }

    fclose(file);
printf("Totals written to totals.txt\n");
FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "set title 'Expenses by Category'\n");
        fprintf(gnuplotPipe, "set xlabel 'Categories'\n");
        fprintf(gnuplotPipe, "set ylabel 'Amount'\n");
        fprintf(gnuplotPipe, "set style fill solid\n");
        fprintf(gnuplotPipe, "set boxwidth 0.5\n");
        fprintf(gnuplotPipe, "set xtics rotate by -45\n");
        fprintf(gnuplotPipe, "set yrange[0:*]\n");
        fprintf(gnuplotPipe, "plot 'totals.txt' using 2:xtic(1) with boxes\n");
        fprintf(gnuplotPipe, "set terminal png\n");
        fprintf(gnuplotPipe, "set output 'expenses.png'\n");
        fprintf(gnuplotPipe, "replot\n");
        fprintf(gnuplotPipe, "exit\n");
        pclose(gnuplotPipe);
    }

     FILE *file1 = fopen("expenses.txt", "w");
                if (file1 == NULL) {
                    printf("Error opening file!\n");
                return 1;
                }
     


    // For each unique category, calculate the total amount and write to the file
   float total = 0;
      for (int i = 0; i < numExpenses ; i++) {
                total += expenses[i].amount;
            }        
        fprintf(file1, "Income %.2f\n", income);
        fprintf(file1, "Expenditure %.2f\n", total);
           

    fclose(file1);
printf("Expenditure written to expenses.txt\n");
FILE *gnuplotPipe1 = popen("gnuplot -persistent", "w");
    if (gnuplotPipe1) {
        fprintf(gnuplotPipe1, "set title 'Expenses v/s Income'\n");
        fprintf(gnuplotPipe1, "set xlabel 'Categories'\n");
        fprintf(gnuplotPipe1, "set ylabel 'Amount'\n");
        fprintf(gnuplotPipe1, "set style fill solid\n");
        fprintf(gnuplotPipe1, "set boxwidth 0.5\n");
        fprintf(gnuplotPipe1, "set xtics rotate by -45\n");
        fprintf(gnuplotPipe1, "set yrange[0:*]\n");
        fprintf(gnuplotPipe1, "plot 'expenses.txt' using 2:xtic(1) with boxes\n");
        fprintf(gnuplotPipe1, "set terminal png\n");
        fprintf(gnuplotPipe1, "set output 'expenses1.png'\n");
        fprintf(gnuplotPipe1, "exit\n");
        pclose(gnuplotPipe1);
    }
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}