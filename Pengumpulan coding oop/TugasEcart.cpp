#include <iostream>
#include <string>
using namespace std;

const int MAX_ITEMS = 100;

class Product {
private:
    string name;
    double price;
    int stock;

public:
    Product(string n = "", double p = 0, int s = 0) : name(n), price(p), stock(s) {}

    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    void setName(const string& n) { name = n; }
    void setPrice(double p) { price = p; }
    void setStock(int s) { stock = s; }
};

class CartItem {
private:
    Product* product;
    int quantity;

public:
    CartItem(Product* p = nullptr, int q = 0) : product(p), quantity(q) {}

    Product* getProduct() const { return product; }
    int getQuantity() const { return quantity; }

    void setQuantity(int q) { quantity = q; }
    double getTotalPrice() const { return product ? product->getPrice() * quantity : 0; }
};

class Cart {
private:
    CartItem items[MAX_ITEMS];
    int itemCount;

public:
    Cart() : itemCount(0) {}

    void addProductToCart(Product* product, int quantity) {
        if (itemCount < MAX_ITEMS) {
            items[itemCount++] = CartItem(product, quantity);
        } else {
            cout << "Cart is full." << endl;
        }
    }

    void displayCart() const {
        if (itemCount == 0) {
            cout << "Cart is empty." << endl;
            return;
        }
        cout << "Items in Cart:" << endl;
        for (int i = 0; i < itemCount; i++) {
            cout << "- " << items[i].getProduct()->getName() << ", Quantity: " << items[i].getQuantity()
                 << ", Total Price: $" << items[i].getTotalPrice() << endl;
        }
    }

    void updateCartItem(Product* product, int quantity) {
        for (int i = 0; i < itemCount; i++) {
            if (items[i].getProduct() == product) {
                items[i].setQuantity(quantity);
                return;
            }
        }
        cout << "Product not found in cart." << endl;
    }

    void removeCartItem(Product* product) {
        for (int i = 0; i < itemCount; i++) {
            if (items[i].getProduct() == product) {
                for (int j = i; j < itemCount - 1; j++) {
                    items[j] = items[j + 1];
                }
                itemCount--;
                return;
            }
        }
        cout << "Product not found in cart." << endl;
    }
};

class Store {
private:
    Product products[MAX_ITEMS];
    int productCount;

public:
    Store() : productCount(0) {}

    void addProduct(const string& name, double price, int stock) {
        if (productCount < MAX_ITEMS) {
            products[productCount++] = Product(name, price, stock);
        } else {
            cout << "Store is full." << endl;
        }
    }

    void displayProducts() const {
        if (productCount == 0) {
            cout << "No products available." << endl;
            return;
        }
        cout << "Available Products:" << endl;
        for (int i = 0; i < productCount; i++) {
            cout << "- " << products[i].getName() << ", Price: $" << products[i].getPrice()
                 << ", Stock: " << products[i].getStock() << endl;
        }
    }

    Product* findProduct(const string& name) {
        for (int i = 0; i < productCount; i++) {
            if (products[i].getName() == name) {
                return &products[i];
            }
        }
        return nullptr;
    }

    void updateProduct(const string& name, double price, int stock) {
        Product* product = findProduct(name);
        if (product) {
            product->setPrice(price);
            product->setStock(stock);
        } else {
            cout << "Product not found." << endl;
        }
    }

    void removeProduct(const string& name) {
        for (int i = 0; i < productCount; i++) {
            if (products[i].getName() == name) {
                for (int j = i; j < productCount - 1; j++) {
                    products[j] = products[j + 1];
                }
                productCount--;
                return;
            }
        }
        cout << "Product not found." << endl;
    }
};


class User {
protected:
    string username;

public:
    User(const string& name) : username(name) {}
    string getUsername() const { return username; }

    void viewProducts(Store& store) {
        cout << username << " is viewing products:" << endl;
        store.displayProducts();
    }
};


class Admin : public User {
public:
    Admin(const string& name) : User(name) {}

    void addProduct(Store& store, const string& name, double price, int stock) {
        cout << "Admin " << username << " is adding product: " << name << endl;
        store.addProduct(name, price, stock);
    }

    void updateProduct(Store& store, const string& name, double price, int stock) {
        cout << "Admin " << username << " is updating product: " << name << endl;
        store.updateProduct(name, price, stock);
    }

    void removeProduct(Store& store, const string& name) {
        cout << "Admin " << username << " is removing product: " << name << endl;
        store.removeProduct(name);
    }
};

int main() {
    Store store;

    
    Admin admin("Alice");
    User user("Bob");

   
    admin.addProduct(store, "Laptop", 1200, 10);
    admin.addProduct(store, "Phone", 800, 20);

    
    user.viewProducts(store);

    
    admin.updateProduct(store, "Laptop", 1100, 8);

    
    user.viewProducts(store);

    
    admin.removeProduct(store, "Phone");

   
    user.viewProducts(store);

    return 0;
}
