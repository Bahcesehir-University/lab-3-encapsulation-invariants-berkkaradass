// ============================================================
// CMP1002 - Lab: Encapsulation and Invariants
// Student Version - MainProgram.cpp
// ============================================================

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm> // Added for any character checking if needed

using namespace std;

// ================================
// CLASS DEFINITIONS
// ================================

// --------------------------------------------------
// Class: Temperature
// --------------------------------------------------
class Temperature {
private:
    double celsius_;

public:
    explicit Temperature(double celsius) {
        setCelsius(celsius);
    }

    double getCelsius() const {
        return celsius_;
    }

    double getFahrenheit() const {
        return (celsius_ * 9.0 / 5.0) + 32.0;
    }

    void setCelsius(double celsius) {
        if (celsius < -273.15) {
            throw invalid_argument("Temperature cannot be below absolute zero (-273.15 C).");
        }
        celsius_ = celsius;
    }
};

// --------------------------------------------------
// Class: BankAccount
// --------------------------------------------------
class BankAccount {
private:
    string owner_;
    double balance_;

public:
    BankAccount(const string& owner, double initialBalance) {
        if (owner.empty()) {
            throw invalid_argument("Owner name cannot be empty.");
        }
        if (initialBalance < 0) {
            throw invalid_argument("Initial balance cannot be negative.");
        }
        owner_ = owner;
        balance_ = initialBalance;
    }

    string getOwner() const {
        return owner_;
    }

    double getBalance() const {
        return balance_;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Deposit amount must be positive.");
        }
        balance_ += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Withdrawal amount must be positive.");
        }
        if (amount > balance_) {
            throw runtime_error("Insufficient funds for withdrawal.");
        }
        balance_ -= amount;
    }

    void transfer(BankAccount& other, double amount) {
        // Validation of amount is handled by withdraw/deposit
        this->withdraw(amount);
        other.deposit(amount);
    }
};

// --------------------------------------------------
// Class: Password
// --------------------------------------------------
class Password {
private:
    string password_;

    static bool hasDigit(const string& s) {
        for (char ch : s) {
            if (isdigit(ch)) return true;
        }
        return false;
    }

    static void validate(const string& pwd) {
        if (pwd.length() < 8) {
            throw invalid_argument("Password must be at least 8 characters long.");
        }
        if (!hasDigit(pwd)) {
            throw invalid_argument("Password must contain at least one digit.");
        }
    }

public:
    explicit Password(const string& pwd) {
        validate(pwd);
        password_ = pwd;
    }

    void change(const string& oldPassword, const string& newPassword) {
        if (password_ != oldPassword) {
            throw invalid_argument("Current password does not match.");
        }
        validate(newPassword);
        password_ = newPassword;
    }

    bool matches(const string& attempt) const {
        return password_ == attempt;
    }

    size_t getLength() const {
        return password_.length();
    }
};

// ================================
// MAIN FUNCTION
// ================================
int main() {
    cout << "=== Encapsulation and Invariants Lab ===" << endl;
    cout << endl;

    // --- Temperature Demo ---
    cout << "--- Temperature ---" << endl;
    try {
        Temperature t(100.0);
        cout << "Celsius: " << t.getCelsius() << endl;
        cout << "Fahrenheit: " << t.getFahrenheit() << endl;
        t.setCelsius(-40.0);
        cout << "Updated Celsius: " << t.getCelsius() << endl;
        cout << "Updated Fahrenheit: " << t.getFahrenheit() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        Temperature bad(-300.0);
        cout << "This should not print!" << endl;
    } catch (const invalid_argument& e) {
        cout << "Caught expected error: " << e.what() << endl;
    }
    cout << endl;

    // --- BankAccount Demo ---
    cout << "--- BankAccount ---" << endl;
    try {
        BankAccount alice("Alice", 1000.0);
        BankAccount bob("Bob", 500.0);
        cout << alice.getOwner() << " balance: " << alice.getBalance() << endl;

        alice.deposit(200.0);
        cout << "After deposit: " << alice.getBalance() << endl;

        alice.transfer(bob, 300.0);
        cout << "After transfer:" << endl;
        cout << "  Alice: " << alice.getBalance() << endl;
        cout << "  Bob:   " << bob.getBalance() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    // --- Password Demo ---
    cout << "--- Password ---" << endl;
    try {
        Password pw("Secure99");
        cout << "Password length: " << pw.getLength() << endl;
        cout << "Matches 'wrong': " << (pw.matches("wrong") ? "Yes" : "No") << endl;
        cout << "Matches 'Secure99': " << (pw.matches("Secure99") ? "Yes" : "No") << endl;
        pw.change("Secure99", "NewPass1");
        cout << "Password changed successfully." << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << endl;
    cout << "=== Lab Complete ===" << endl;
    return 0;
}

