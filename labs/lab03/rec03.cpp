/*
  Author: Shounak Ghosh
  rec03.cpp
  Feb 10 2023
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account
{
  /* data */
  string name;
  int accNum;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class AccountClass {
private:
  /* data */
  string name;
  int accNum;
public:
  AccountClass(const string& n, int a) {
    name = n;
    accNum = a;
  }

  const string& getName() const {
    return name;
  }

  int getAccNum() const {
    return accNum;
  }

  friend ostream& operator<<(ostream& os, const AccountClass& acc);

};

ostream& operator<<(ostream& os, const AccountClass& acc) {
  // os << acc.getName() << " " << acc.getAccNum();
  os << acc.name << " " << acc.accNum;
  return os;
}

// Task 3
// Define an Account (use a different name than in Task 1&2) and
// Transaction classes
class Transaction {
private:
  /* data */
  string type;
  int amount;
public:
  Transaction(const string& t, int a) {
    type = t;
    amount = a;
  }

  const string& getType() const {
    return type;
  }

  int getAmount() const {
    return amount;
  }

  friend ostream& operator<<(ostream& os, const Transaction& acc);

};

ostream& operator<<(ostream& os, const Transaction& trans) {
  os << trans.type << " " << trans.amount;
  return os;
}

class AccountClassTrans {
private:
  string name;
  int accNum;
  vector<Transaction> transactions;
  int balance;
public:
  AccountClassTrans(const string& n, int a) {
    name = n;
    accNum = a;
    balance = 0;
  }

  const string& getName() const {
    return name;
  }

  int getAccNum() const {
    return accNum;
  }

  int getBalance() const {
    return balance;
  }

  void deposit(int amount) {
    balance += amount;
    transactions.push_back(Transaction{ "deposit", amount });
  }

  void withdraw(int amount) {
    if (amount > balance) {
      cout << "Insufficient funds\n";
    }
    else {
      balance -= amount;
      transactions.push_back(Transaction{ "withdraw", amount });
    }
  }

  friend ostream& operator<<(ostream& os, const AccountClassTrans& acc);

};

ostream& operator<<(ostream& os, const AccountClassTrans& acc) {
  os << acc.name << " " << acc.accNum << " " << acc.balance;
  if (acc.transactions.size() == 0) {
    os << "\nNo transactions";
  }
  else {
    os << "\nTransactions History:\n";
    for (size_t i = 0; i < acc.transactions.size(); i++) {
      os << acc.transactions[i] << endl;
    }
  }

  return os;
}

// Task 4
// Define an Account with a nested public Transaction class
// (use different names than in the previous Tasks)
class AccountClassTransNested {
  public:
  class NestedTransaction {
  private:
    /* data */
    string type;
    int amount;
  public:
    NestedTransaction(const string& t, int a) {
      type = t;
      amount = a;
    }

    const string& getType() const {
      return type;
    }

    int getAmount() const {
      return amount;
    }

    friend ostream& operator<<(ostream& os, const NestedTransaction& acc);

  };
private:
  string name;
  int accNum;
  int balance;
  vector<NestedTransaction> transactions;
public:
  AccountClassTransNested(const string& n, int a) {
    name = n;
    accNum = a;
    balance = 0;
  }

  string getName() const {
    return name;
  }

  int getAccNum() const {
    return accNum;
  }

  int getBalance() const {
    return balance;
  }

  void deposit(int amount) {
    balance += amount;
    transactions.push_back(NestedTransaction{ "deposit", amount });
  }

  void withdraw(int amount) {
    if (amount > balance) {
      cout << "Insufficient funds\n";
    }
    else {
      balance -= amount;
      transactions.push_back(NestedTransaction{ "withdraw", amount });
    }
  }

  friend ostream& operator<<(ostream& os, const AccountClassTransNested& acc);

};

ostream& operator<<(ostream& os, const AccountClassTransNested::NestedTransaction& acc) {
  os << acc.type << " " << acc.amount;
  return os;
}

ostream& operator<<(ostream& os, const AccountClassTransNested& acc) {
  os << acc.name << " " << acc.accNum << " " << acc.balance;
  if (acc.transactions.size() == 0) {
    os << "\nNo transactions";
  }
  else {
    os << "\nTransactions History:\n";
    for (size_t i = 0; i < acc.transactions.size(); i++) {
      os << acc.transactions[i] << endl;
    }
  }

  return os;
}

//TODO: Task 5
// Define an Account with a nested private Transaction class
// (use different names than in the previous Tasks)

int main() {

  // Task 1: account as struct
  //      1a
  cout << "Task1a:\n";
  cout << "Filling vector of struct objects, using local struct object:\n";
  vector<Account> accounts;

  ifstream ifs("accounts.txt");
  if (!ifs) {
    cerr << "Could not open accounts.txt\n";
    exit(1);
  }

  string name;
  int accNum;

  while (ifs >> name >> accNum) {
    Account acc;
    acc.name = name;
    acc.accNum = accNum;
    accounts.push_back(acc);
  }
  ifs.close();

  for (const Account& acc : accounts) {
    cout << acc.name << " " << acc.accNum << endl;
  }

  accounts.clear();

  //      1b
  cout << "\nTask1b:\n";
  cout << "Filling vector of struct objects, using {} initialization:\n";
  ifs.open("accounts.txt");
  if (!ifs) {
    cerr << "Could not open accounts.txt\n";
    exit(1);
  }

  while (ifs >> name >> accNum) {
    accounts.push_back(Account{ name, accNum });
  }
  ifs.close();

  for (const Account& acc : accounts) {
    cout << acc.name << " " << acc.accNum << endl;
  }

  //==================================
  // Task 2: account as class

  //      2a
  cout << "==============\n";
  cout << "Task2a:";
  cout << "\nFilling vector of class objects, using local class object:\n";
  vector<AccountClass> accountsClass;

  ifs.open("accounts.txt");
  if (!ifs) {
    cerr << "Could not open accounts.txt\n";
    exit(1);
  }

  while (ifs >> name >> accNum) {
    AccountClass acc(name, accNum);
    accountsClass.push_back(acc);
  }
  ifs.close();

  for (const AccountClass& acc : accountsClass) {
    cout << acc.getName() << " " << acc.getAccNum() << endl;
  }


  cout << "\nTask2b:\n";
  cout << "output using output operator with getters\n";

  for (size_t i = 0; i < accountsClass.size(); i++) {
    cout << accountsClass[i].getName() << " " << accountsClass[i].getAccNum() << endl;
  }
  cout << "\nTask2c:\n";
  cout << "output using output operator as friend without getters\n";

  for (size_t i = 0; i < accountsClass.size(); i++) {
    cout << accountsClass[i] << endl;
  }

  cout << "\nTask2d:\n";
  cout << "Filling vector of class objects, using temporary class object:\n";

  accountsClass.clear();
  ifs.open("accounts.txt");
  if (!ifs) {
    cerr << "Could not open accounts.txt\n";
    exit(1);
  }

  while (ifs >> name >> accNum) {
    accountsClass.push_back(AccountClass(name, accNum));
  }
  ifs.close();

  for (const AccountClass& acc : accountsClass) {
    cout << acc << endl;
  }

  cout << "\nTask2e:\n";
  cout << "Filling vector of class objects, using emplace_back:\n";

  accountsClass.clear();
  ifs.open("accounts.txt");
  if (!ifs) {
    cerr << "Could not open accounts.txt\n";
    exit(1);
  }

  while (ifs >> name >> accNum) {
    accountsClass.emplace_back(name, accNum);
  }
  ifs.close();

  for (const AccountClass& acc : accountsClass) {
    cout << acc << endl;
  }

  cout << "==============\n";
  cout << "Task 3:\nAccounts and Transaction:\n";

  vector<AccountClassTrans> accountsClassTrans;
  ifs.open("transactions.txt");
  if (!ifs) {
    cerr << "Could not open transactions.txt\n";
    exit(1);
  }

  string command;

  while (ifs >> command) {
    if (command == "Account") {
      ifs >> name >> accNum;
      accountsClassTrans.push_back(AccountClassTrans(name, accNum));
    }
    else if (command == "Deposit") {
      int accNum;
      int amount;
      ifs >> accNum >> amount;

      for (AccountClassTrans& acc : accountsClassTrans) {
        if (acc.getAccNum() == accNum) {
          acc.deposit(amount);
        }
      }
    }
    else if (command == "Withdraw") {
      int accNum;
      int amount;
      ifs >> accNum >> amount;

      for (AccountClassTrans& acc : accountsClassTrans) {
        if (acc.getAccNum() == accNum) {
          acc.withdraw(amount);
        }
      }
    }
    else {
      cerr << "Unknown command: " << command << endl;
    }
  }
  ifs.close();

  for (const AccountClassTrans& acc : accountsClassTrans) {
    cout << acc << endl;
  }

  cout << "==============\n";
  cout << "Task 4:\nTransaction nested in public section of Account:\n";
  
  vector<AccountClassTransNested> accountsClassTransNested;
  ifs.open("transactions.txt");
  if (!ifs) {
    cerr << "Could not open transactions.txt\n";
    exit(1);
  }

  while (ifs >> command) {
    if (command == "Account") {
      ifs >> name >> accNum;
      accountsClassTransNested.push_back(AccountClassTransNested(name, accNum));
    }
    else if (command == "Deposit") {
      int accNum;
      int amount;
      ifs >> accNum >> amount;

      for (AccountClassTransNested& acc : accountsClassTransNested) {
        if (acc.getAccNum() == accNum) {
          acc.deposit(amount);
        }
      }
    }
    else if (command == "Withdraw") {
      int accNum;
      int amount;
      ifs >> accNum >> amount;

      for (AccountClassTransNested& acc : accountsClassTransNested) {
        if (acc.getAccNum() == accNum) {
          acc.withdraw(amount);
        }
      }
    }
    else {
      cerr << "Unknown command: " << command << endl;
    }
  }
  ifs.close();

  for (const AccountClassTransNested& acc : accountsClassTransNested) {
    cout << acc << endl;
  }

  cout << "==============\n";
  cout << "Task 5:\nTransaction nested in private section of Account:\n"; 


}
