#include <iostream>
#include <string>
using namespace std;


class Wallet 
{
public:
    double btc;
    double eth;
    double doge;
    double usdt;

    Wallet() 
    {
        btc = 0;
        eth = 0;
        doge = 0;
        usdt = 0;
    }

    void showBalance() 
    {
        cout << "\n----- WALLET BALANCE -----\n";
        cout << "BTC: " << btc << endl;
        cout << "ETH: " << eth << endl;
        cout << "DOGE: " << doge << endl;
        cout << "USDT: " << usdt << endl;
    }

    void deposit(double amount) 
    {
        if (amount <= 0) 
        {
            cout << "Invalid amount!\n";
            return;
        }
        usdt += amount;
        cout << "Deposited " << amount << " USDT.\n";
    }

    void withdraw(double amount) 
    {
        if (amount <= 0) 
        {
            cout << "Invalid amount!\n";
            return;
        }
        if (amount > usdt) 
        {
            cout << "Not enough USDT!\n";
            return;
        }
        usdt -= amount;
        cout << "Withdrew " << amount << " USDT.\n";
    }
};


class User 
{
public:
    string username;
    string password;
    Wallet wallet;

    int orderIndexes[5];
    int orderCount = 0;

    User() 
    {
        username = "";
        password = "";
        for(int i=0;i<5;i++) orderIndexes[i] = -1;
    }
};


class Order 
{
public:
    int id;
    string username;
    string type;
    string currency;
    double amount;
    double price;
};

    
class Exchange 
{
public:
    User users[20];
    int userCount = 0;

    Order orders[50];
    int orderCount = 0;
    int nextOrderId = 1;

    bool usernameExists(string u) 
    {
        for (int i = 0; i < userCount; i++) 
        {
            if (users[i].username == u) return true;
        }
        return false;
    }

    bool isValidCurrency(string c) 
    {
        return (c == "BTC" || c == "ETH" || c == "DOGE");
    }

    bool isValidOrderType(string t) 
    {
        return (t == "Buy" || t == "Sell");
    }

    bool isPositive(double x) 
    {
        return (x > 0);
    }

    void registerUser() 
    {
        if (userCount >= 20) 
        {
            cout << "User limit reached!\n";
            return;
        }

        string u, p;
        cout << "Enter username: ";
        cin >> u;
        cout << "Enter password: ";
        cin >> p;

        if (u == "" || p == "") 
        {
            cout << "Username/Password cannot be empty!\n";
            return;
        }

        if (usernameExists(u)) 
        {
            cout << "This username already exists!\n";
            return;
        }

        users[userCount].username = u;
        users[userCount].password = p;
        userCount++;

        cout << "User registered successfully!\n";
    }

    int loginUser() 
    {
        string u, p;
        cout << "Username: ";
        cin >> u;
        cout << "Password: ";
        cin >> p;

        for (int i = 0; i < userCount; i++) 
        {
            if (users[i].username == u && users[i].password == p) 
            {
                return i;
            }
        }

        cout << "Incorrect username or password.\n";
        return -1;
    }

    void placeOrder(int userIndex) 
    {
        if (orderCount >= 50) 
        {
            cout << "Order limit reached!\n";
            return;
        }

        if (users[userIndex].orderCount >= 5) 
        {
            cout << "You already have 5 orders!\n";
            return;
        }

        string type, curr;
        double amt, price;

        cout << "Order type (Buy/Sell): ";
        cin >> type;
        if (!isValidOrderType(type)) return;

        cout << "Currency (BTC/ETH/DOGE): ";
        cin >> curr;
        if (!isValidCurrency(curr)) return;

        cout << "Amount: ";
        cin >> amt;
        if (!isPositive(amt)) return;

        cout << "Price: ";
        cin >> price;
        if (!isPositive(price)) return;

        double cost = amt * price;

        if (type == "Buy") 
        {
            if (users[userIndex].wallet.usdt < cost) 
            {
                cout << "Not enough USDT!\n";
                return;
            }

            users[userIndex].wallet.usdt -= cost;
            if (curr == "BTC") users[userIndex].wallet.btc += amt;
            if (curr == "ETH") users[userIndex].wallet.eth += amt;
            if (curr == "DOGE") users[userIndex].wallet.doge += amt;

            cout << "Buy successful!\n";
        }

        if (type == "Sell") 
        {
            bool enough = false;

            if (curr == "BTC" && users[userIndex].wallet.btc >= amt) 
            {
                users[userIndex].wallet.btc -= amt;
                enough = true;
            }
            if (curr == "ETH" && users[userIndex].wallet.eth >= amt) 
            {
                users[userIndex].wallet.eth -= amt;
                enough = true;
            }
            if (curr == "DOGE" && users[userIndex].wallet.doge >= amt) 
            {
                users[userIndex].wallet.doge -= amt;
                enough = true;
            }

            if (!enough) 
            {
                cout << "Not enough coins!\n";
                return;
            }

            users[userIndex].wallet.usdt += cost;
            cout << "Sell successful!\n";
        }

        orders[orderCount].id = nextOrderId++;
        orders[orderCount].username = users[userIndex].username;
        orders[orderCount].type = type;
        orders[orderCount].currency = curr;
        orders[orderCount].amount = amt;
        orders[orderCount].price = price;

        users[userIndex].orderIndexes[users[userIndex].orderCount] = orderCount;
        users[userIndex].orderCount++;

        orderCount++;

        users[userIndex].wallet.showBalance();
    }

    void cancelLastOrder(int userIndex) 
    {
        if (users[userIndex].orderCount == 0) 
        {
            cout << "No orders to cancel!\n";
            return;
        }

        int orderIndex = users[userIndex].orderIndexes[users[userIndex].orderCount - 1];
        Order &o = orders[orderIndex];

        double refund = o.amount * o.price;

        if (o.type == "Buy") 
        {
            users[userIndex].wallet.usdt += refund;

            if (o.currency == "BTC") users[userIndex].wallet.btc -= o.amount;
            if (o.currency == "ETH") users[userIndex].wallet.eth -= o.amount;
            if (o.currency == "DOGE") users[userIndex].wallet.doge -= o.amount;
        }

        if (o.type == "Sell") 
        {
            users[userIndex].wallet.usdt -= refund;

            if (o.currency == "BTC") users[userIndex].wallet.btc += o.amount;
            if (o.currency == "ETH") users[userIndex].wallet.eth += o.amount;
            if (o.currency == "DOGE") users[userIndex].wallet.doge += o.amount;
        }

        users[userIndex].orderCount--;

        cout << "Last order canceled with refund!\n";
        users[userIndex].wallet.showBalance();
    }

    void showMyOrders(int userIndex) 
    {
        cout << "\n----- YOUR ORDERS -----\n";

        if (users[userIndex].orderCount == 0) 
        {
            cout << "You have no orders.\n";
            return;
        }

        for (int i = 0; i < users[userIndex].orderCount; i++) 
        {
            int idx = users[userIndex].orderIndexes[i];
            Order &o = orders[idx];

            cout << "ID: " << o.id << " | "
                 << o.type << " " << o.amount
                 << " " << o.currency
                 << " @ " << o.price << endl;
        }
    }
};


int main() 
{
    Exchange ex;
    int choice;

    while (true) 
    {
        cout << "\n===== CRYPTO SYSTEM =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cin >> choice;

        if (choice == 1) ex.registerUser();

        else if (choice == 2) 
        {
            int index = ex.loginUser();

            while (index != -1) 
            {
                int c2;
                cout << "\n--- USER MENU ---\n";
                cout << "1. Show Wallet\n";
                cout << "2. Deposit USDT\n";
                cout << "3. Withdraw USDT\n";
                cout << "4. Place Order\n";
                cout << "5. View My Orders\n";
                cout << "6. Cancel Last Order\n";
                cout << "7. Logout\n";
                cin >> c2;

                if (c2 == 1) ex.users[index].wallet.showBalance();
                else if (c2 == 2) 
                {
                    double amt;
                    cout << "Enter amount: ";
                    cin >> amt;
                    ex.users[index].wallet.deposit(amt);
                }
                else if (c2 == 3) 
                {
                    double amt;
                    cout << "Enter amount: ";
                    cin >> amt;
                    ex.users[index].wallet.withdraw(amt);
                }
                else if (c2 == 4) 
                { ex.placeOrder(index); }
                else if (c2 == 5) 
                { ex.showMyOrders(index); }
                else if (c2 == 6) 
                { 
                    ex.cancelLastOrder(index); 
                }
                else if (c2 == 7) 
                { 
                    index = -1; 
                }
                else 
                {
                    cout << "Invalid choice!\n";
                }
            }
        }

        else if (choice == 3) break;
    }

    return 0;
}