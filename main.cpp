#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Transaction class to represent each transaction
class Transaction {
public:
    string category;
    double amount;
    string date;
    bool isCredit; // true for credit, false for debit

    // Constructor to initialize transaction
    Transaction(string cat, double amt, string d, bool credit) 
        : category(cat), amount(amt), date(d), isCredit(credit) {}
};

// Function to add a new transaction
void addTransaction(vector<Transaction>& transactions) {
    string category, date;
    double amount;
    char type;

    cout << "Enter category (e.g., Tuition, Rent, Food): ";
    cin >> category;
    cout << "Enter amount: ";
    cin >> amount;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;
    cout << "Is this a credit or debit? (c/d): ";
    cin >> type;

    bool isCredit = (type == 'c');
    transactions.push_back(Transaction(category, amount, date, isCredit));
    cout << "Transaction added successfully!" << endl;
}

// Function to display all transactions
void displayTransactions(const vector<Transaction>& transactions) {
    cout << "\n--- Transaction List ---\n";
    for (int i = 0; i < transactions.size(); ++i) {
        const auto& trans = transactions[i];
        cout << i + 1 << ". Category: " << trans.category
             << ", Amount: " << trans.amount
             << ", Date: " << trans.date
             << ", Type: " << (trans.isCredit ? "Credit" : "Debit") << endl;
    }
}

// Function to delete a transaction
void deleteTransaction(vector<Transaction>& transactions) {
    displayTransactions(transactions);

    if (transactions.empty()) {
        cout << "No transactions available to delete!" << endl;
        return;
    }

    int index;
    cout << "Enter the number of the transaction to delete: ";
    cin >> index;

    if (index > 0 && index <= transactions.size()) {
        transactions.erase(transactions.begin() + (index - 1));
        cout << "Transaction deleted successfully!" << endl;
    } else {
        cout << "Invalid transaction number!" << endl;
    }
}

// Function to save transactions to a file
void saveToFile(const vector<Transaction>& transactions, const string& filename) {
    ofstream file(filename);
    for (const auto& trans : transactions) {
        file << trans.category << " " << trans.amount << " " << trans.date << " " << (trans.isCredit ? "Credit" : "Debit") << endl;
    }
    file.close();
    cout << "Transactions saved to file!" << endl;
}

// Function to calculate total expenses
double calculateTotalExpenses(const vector<Transaction>& transactions) {
    double totalExpenses = 0;
    for (const auto& trans : transactions) {
        if (!trans.isCredit) {
            totalExpenses += trans.amount;
        }
    }
    return totalExpenses;
}

// Function to calculate total credits
double calculateTotalCredits(const vector<Transaction>& transactions) {
    double totalCredits = 0;
    for (const auto& trans : transactions) {
        if (trans.isCredit) {
            totalCredits += trans.amount;
        }
    }
    return totalCredits;
}

// Function to display the savings report
void displaySavings(double totalIncome, double totalExpenses, double savingsGoal, const vector<Transaction>& transactions) {
    double totalCredits = calculateTotalCredits(transactions);
    double savings = totalIncome + totalCredits - totalExpenses;
    double remaining = savingsGoal - savings;
    double progress = (savings / savingsGoal) * 100;

    cout << "\n--- Financial Summary ---\n";
    cout << "Total Income (Initial + Credits): $" << totalIncome + totalCredits << endl;
    cout << "Total Expenses: $" << totalExpenses << endl;
    cout << "Total Savings: $" << savings << endl;
    cout << "Savings Goal: $" << savingsGoal << endl;

    if (savings >= savingsGoal) {
        cout << "Congratulations! You've reached your savings goal!" << endl;
    } else {
        cout << "You have saved " << progress << "% of your goal." << endl;
        cout << "You need $" << remaining << " more to reach your goal." << endl;
    }
}

// Main menu function
void showMenu() {
    cout << "\n--- College Finance Tracker ---\n";
    cout << "1. Add Transaction\n";
    cout << "2. View Transactions\n";
    cout << "3. Set Savings Goal\n";
    cout << "4. View Financial Summary (Income, Expenses, Savings, Goal)\n";
    cout << "5. Delete Transaction\n";
    cout << "6. Save Transactions\n";
    cout << "7. Exit\n";
    cout << "Select an option: ";
}

int main() {
    vector<Transaction> transactions;
    string filename = "transactions.txt";
    int option;
    double totalIncome = 0;
    double savingsGoal = 0;

    // Ask for income first
    cout << "Enter total income or scholarship amount: ";
    cin >> totalIncome;
    cout << "Total income set to $" << totalIncome << endl;

    while (true) {
        showMenu();
        cin >> option;

        switch (option) {
        case 1:
            addTransaction(transactions);
            break;
        case 2:
            displayTransactions(transactions);
            break;
        case 3:
            cout << "Enter your savings goal: ";
            cin >> savingsGoal;
            cout << "Savings goal set to $" << savingsGoal << endl;
            break;
        case 4: {
            double totalExpenses = calculateTotalExpenses(transactions);
            displaySavings(totalIncome, totalExpenses, savingsGoal, transactions);
            break;
        }
        case 5:
            deleteTransaction(transactions);
            break;
        case 6:
            saveToFile(transactions, filename);
            break;
        case 7:
            cout << "Exiting program..." << endl;
            return 0;
        default:
            cout << "Invalid option, please try again!" << endl;
        }
    }
    return 0;
}


