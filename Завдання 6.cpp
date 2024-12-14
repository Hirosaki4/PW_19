#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

// Клас для водіїв
class Driver {
private:
    string name;
    string car;
    double rating;
    int trips;

public:
    Driver(string name, string car, double rating = 5.0, int trips = 0)
        : name(name), car(car), rating(rating), trips(trips) {}

    string getName() const { return name; }
    string getCar() const { return car; }
    double getRating() const { return rating; }
    int getTrips() const { return trips; }

    void updateRating(double newRating) {
        rating = (rating * trips + newRating) / (trips + 1);
        trips++;
    }

    void displayInfo() const {
        cout << "\nВодій: " << name << "\nАвтомобіль: " << car
            << "\nРейтинг: " << fixed << setprecision(1) << rating
            << "\nКількість поїздок: " << trips << "\n";
    }
};

// Клас для сервісу таксі
class TaxiService {
private:
    vector<Driver> drivers;

public:
    void addDriver(const Driver& driver) {
        drivers.push_back(driver);
    }

    void listDrivers() const {
        if (drivers.empty()) {
            cout << "\nНемає зареєстрованих водіїв.\n";
            return;
        }

        cout << "\nСписок водіїв:\n";
        for (const auto& driver : drivers) {
            driver.displayInfo();
        }
    }

    void bookRide(const string& clientName) {
        if (drivers.empty()) {
            cout << "\nВибачте, наразі немає доступних водіїв.\n";
            return;
        }

        cout << "\nПоїздка замовлена клієнтом: " << clientName << "\n";
        cout << "Доступні водії:\n";

        for (size_t i = 0; i < drivers.size(); ++i) {
            cout << i + 1 << ". " << drivers[i].getName() << " (" << drivers[i].getCar() << ")" << endl;
        }

        cout << "\nОберіть номер водія: ";
        int choice;
        cin >> choice;

        if (choice < 1 || choice > drivers.size()) {
            cout << "Неправильний вибір. Спробуйте ще раз.\n";
            return;
        }

        double rating;
        cout << "\nОцініть поїздку (1-5): ";
        cin >> rating;
        rating = max(1.0, min(5.0, rating));

        drivers[choice - 1].updateRating(rating);

        cout << "\nДякуємо за користування сервісом!\n";
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    TaxiService service;

    service.addDriver(Driver("Олексій", "Toyota Camry"));
    service.addDriver(Driver("Марія", "Honda Civic"));
    service.addDriver(Driver("Іван", "Ford Focus"));

    int option;

    do {
        cout << "\n=== Таксі-Сервіс ===\n";
        cout << "1. Переглянути список водіїв\n";
        cout << "2. Замовити поїздку\n";
        cout << "3. Вихід\n";
        cout << "Оберіть опцію: ";
        cin >> option;

        switch (option) {
        case 1:
            service.listDrivers();
            break;
        case 2: {
            string clientName;
            cout << "\nВведіть ваше ім'я: ";
            cin >> clientName;
            service.bookRide(clientName);
            break;
        }
        case 3:
            cout << "\nДякуємо за користування нашим сервісом!\n";
            break;
        default:
            cout << "\nНеправильний вибір. Спробуйте ще раз.\n";
        }

    } while (option != 3);

    return 0;
}
