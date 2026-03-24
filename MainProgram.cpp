#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

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
        if (celsius < -273.15) {
            throw invalid_argument("Sıcaklık mutlak sıfırın (-273.15) altında olamaz!");
        }
        celsius_ = celsius;
    }

    double getCelsius() const {
        return celsius_;
    }

    double getFahrenheit() const {
        return celsius_ * 9.0 / 5.0 + 32.0;
    }

    void setCelsius(double celsius) {
        if (celsius < -273.15) {
            throw invalid_argument("Sıcaklık mutlak sıfırın (-273.15) altında olamaz!");
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
            throw invalid_argument("Sahip ismi bos olamaz!");
        }
        if (initialBalance < 0) {
            throw invalid_argument("Baslangic bakiyesi negatif olamaz!");
        }
        owner_ = owner;
        balance_ = initialBalance;
    }

    string getOwner() const {
        return owner_; // "owner_" stringini değil, değişkenin kendisini döndürüyoruz
    }

    double getBalance() const {
        return balance_;
    }

    void deposit(double amount) {
        if (amount <= 0) { // Yatırılan tutar 0 veya negatif olamaz
            throw invalid_argument("Yatirilacak miktar pozitif olmalidir!");
        }
        balance_ += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Cekilecek miktar pozitif olmalidir!");
        }
        if (amount > balance_) {
            throw runtime_error("Yetersiz bakiye!");
        }
        balance_ -= amount;
    }

    void transfer(BankAccount& other, double amount) {
        // withdraw zaten tutar kontrolü ve bakiye kontrolü yapıyor
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

    // Helper: Bir string içinde rakam olup olmadığını kontrol eder
    static bool hasDigit(const string& s) {
        for (char c : s) {
            if (c >= '0' && c <= '9') {
                return true;
            }
        }
        return false;
    }

    // Helper: Kuralları doğrular
    static void validate(const string& pwd) {
        if (pwd.length() < 8) {
            throw invalid_argument("Sifre en az 8 karakter olmalidir!");
        }
        if (!hasDigit(pwd)) {
            throw invalid_argument("Sifre en az bir rakam icermelidir!");
        }
    }

public:
    explicit Password(const string& pwd) {
        validate(pwd);
        password_ = pwd;
    }

    void change(const string& oldPassword, const string& newPassword) {
        if (password_ != oldPassword) {
            throw invalid_argument("Eski sifre hatali!");
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
    cout << "=== Encapsulation and Invariants Lab ===" << endl << endl;

    // --- Temperature Demo ---
    cout << "--- Temperature ---" << endl;
    try {
        Temperature t(100.0);
        cout << "Celsius: " << t.getCelsius() << endl;
        cout << "Fahrenheit: " << t.getFahrenheit() << endl;
        t.setCelsius(-40.0);
        cout << "Updated Celsius: " << t.getCelsius() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    // --- BankAccount Demo ---
    cout << "\n--- BankAccount ---" << endl;
    try {
        BankAccount alice("Alice", 1000.0);
        BankAccount bob("Bob", 500.0);
        cout << alice.getOwner() << " balance: " << alice.getBalance() << endl;

        alice.deposit(200.0);
        alice.transfer(bob, 300.0);
        cout << "After transfer - Alice: " << alice.getBalance() << ", Bob: " << bob.getBalance() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    // --- Password Demo ---
    cout << "\n--- Password ---" << endl;
    try {
        Password pw("Secure99");
        cout << "Password length: " << pw.getLength() << endl;
        cout << "Matches 'Secure99': " << (pw.matches("Secure99") ? "Yes" : "No") << endl;
        pw.change("Secure99", "NewPass123");
        cout << "Password changed successfully." << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\n=== Lab Complete ===" << endl;
    return 0;
}
