#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For sorting
using namespace std;

class dateType {
public:
    dateType() : month(0), day(0), year(0) {} // Default constructor added

    dateType(int month, int day, int year) {
        setDate(month, day, year);
    }

    void setDate(int month, int day, int year) {
        if (isValidDate(month, day, year)) {
            this->month = month;
            this->day = day;
            this->year = year;
        } else {
            cout << "Invalid date. Please enter a valid date." << endl;
        }
    }

    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

private:
    bool isValidDate(int month, int day, int year) const {
        if (year < 0 || month < 1 || month > 12)
            return false;

        const int daysInMonth[] = {31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return day >= 1 && day <= daysInMonth[month - 1];
    }

    int month;
    int day;
    int year;
};

class addressType {
public:
    addressType() {} // Default constructor added

    addressType(const string& street, const string& city, const string& state, const string& zip)
        : street(street), city(city), state(state), zip(zip) {}

    void printAddress() const {
        cout << street << ", " << city << ", " << state << " " << zip << endl;
    }

private:
    string street;
    string city;
    string state;
    string zip;
};


class personType {
public:
    personType(const string& firstName, const string& lastName)
        : firstName(firstName), lastName(lastName) {}

    string getLastName() const { return lastName; }

    void printName() const {
        cout << firstName << " " << lastName << endl;
    }

private:
    string firstName;
    string lastName;
};

class extPersonType : public personType {
public:
    extPersonType(const string& firstName, const string& lastName, const string& phone, const string& relation)
        : personType(firstName, lastName), phone(phone), relation(relation) {}

    void setDetails(const string& phone, const string& relation, const dateType& dob, const addressType& addr) {
        this->phone = phone;
        this->relation = relation;
        this->dob = dob;
        this->address = addr;
    }

    void printDetails() const {
        cout << "Name: ";
        printName();
        cout << "Phone: " << phone << endl;
        cout << "Address: ";
        address.printAddress();
        cout << "Date of Birth: " << dob.getDay() << "/" << dob.getMonth() << "/" << dob.getYear() << endl;
    }

    string getRelation() const { return relation; }
    dateType getDob() const { return dob; }

private:
    string phone;
    string relation;
    dateType dob;
    addressType address;
};

class addressBookType {
public:
    void addPerson(const extPersonType& person) {
        addressBook.push_back(person);
    }

    void sortByLastName() {
        sort(addressBook.begin(), addressBook.end(), [](const extPersonType& a, const extPersonType& b) {
            return a.getLastName() < b.getLastName();
        });
    }

    void searchLastName(const string& lastName) {
        for (const auto& person : addressBook) {
            if (person.getLastName() == lastName) {
                cout << "Person found: " << endl;
                person.printDetails();
                return;
            }
        }
        cout << "Person with last name " << lastName << " not found." << endl;
    }

    void printBirthdaysInMonth(int month) {
        cout << "Birthdays in month " << month << ":" << endl;
        for (const auto& person : addressBook) {
            if (person.getDob().getMonth() == month) {
                person.printName();
            }
        }
    }

    void printNamesBetweenLastNames(const string& lastName1, const string& lastName2) {
        cout << "Names between " << lastName1 << " and " << lastName2 << ":" << endl;
        bool foundFirst = false;
        bool foundSecond = false;
        for (const auto& person : addressBook) {
            if (person.getLastName() == lastName1) {
                foundFirst = true;
            }
            if (foundFirst && !foundSecond) {
                person.printName();
            }
            if (person.getLastName() == lastName2) {
                foundSecond = true;
                break;
            }
        }
        if (!foundFirst || !foundSecond) {
            cout << "One or both of the last names not found." << endl;
        }
    }

    void printByRelation(const string& relation) {
        cout << "People with relation '" << relation << "':" << endl;
        for (const auto& person : addressBook) {
            if (person.getRelation() == relation) {
                person.printName();
            }
        }
    }

private:
    vector<extPersonType> addressBook;
};

int main() {
    addressBookType addressBook;

    // Adding sample data
    extPersonType person1("John", "Doe", "123-456-7890", "Family");
    person1.setDetails("123-456-7890", "Family", dateType(10, 15, 1980), addressType("123 Main St", "Springfield", "IL", "12345"));

    extPersonType person2("Jane", "Smith", "987-654-3210", "Friend");
    person2.setDetails("987-654-3210", "Friend", dateType(5, 20, 1990), addressType("456 Oak St", "Chicago", "IL", "54321"));

    extPersonType person3("David", "Johnson", "555-555-5555", "Business Associate");
    person3.setDetails("555-555-5555", "Business Associate", dateType(3, 25, 1975), addressType("789 Elm St", "New York", "NY", "67890"));

    extPersonType person4("Emily", "Brown", "222-333-4444", "Family");
    person4.setDetails("222-333-4444", "Family", dateType(8, 10, 1985), addressType("101 Pine St", "Los Angeles", "CA", "98765"));

    addressBook.addPerson(person1);
    addressBook.addPerson(person2);
    addressBook.addPerson(person3);
    addressBook.addPerson(person4);

    // Sort by last name
    addressBook.sortByLastName();

    // Test functionalities
    addressBook.searchLastName("Smith");
    addressBook.printBirthdaysInMonth(5);
    addressBook.printNamesBetweenLastNames("Doe", "Johnson");
    addressBook.printByRelation("Family");

    return 0;
}

  