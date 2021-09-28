#include <iostream>
#include <tuple>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

struct Person {
    std::string name;
    std::string second_name;
    std::string middle_name;

    friend std::ostream& operator<< (std::ostream& out, const Person& person);
    friend bool operator<(const Person& t1, const Person& t2);
    friend bool operator==(const Person& t1, const Person& t2);
};
std::ostream& operator<< (std::ostream& out, const Person& person) {
    out << "Second name: " << person.second_name << " " << "Name: " << person.name << " " << "Middle name: " << person.middle_name;
    return out;
}
bool operator<(const Person& person1, const Person& person2) {
    return tie(person1.second_name) <tie(person2.second_name);
}
bool operator==(const Person& person1, const Person& person2) {
    return tie(person1.second_name, person1.name, person1.middle_name) == tie(person2.second_name, person2.name, person2.middle_name);
}

struct PhoneNumber {
    int code_country = 0;
    int code_city = 0;
    std::string number;
    int extension_number = 0;

    friend std::ostream& operator<< (std::ostream& out, const PhoneNumber& p_num);
    friend bool operator<(const PhoneNumber& n1, const PhoneNumber& n2);

};

bool operator<(const PhoneNumber& n1, const PhoneNumber& n2) {
    return std::tie(n1.code_country) < std::tie(n2.code_country);
}
std::ostream& operator<< (std::ostream& out, const PhoneNumber& p_num) {
    out << "Number: " << "+" << p_num.code_country << "(" << p_num.code_city << ")" << p_num.number << " " << p_num.extension_number;
    return out;
}
bool CompareNumber(std::pair<Person, PhoneNumber> people1, std::pair<Person, PhoneNumber> people2){
    return people1.second < people2.second;
}
bool CompareName(std::pair<Person, PhoneNumber> people1, std::pair<Person, PhoneNumber> people2) {
    return people1.first < people2.first;
}

class PhoneBook {
private:
    std::vector<std::pair<Person, PhoneNumber >> people;
public:
    PhoneBook(std::ifstream& file) {
        Person person;
        PhoneNumber number;
        int flag = 0;
        int tmp = 0;
        std::string name;
        char a;

        while (!file.eof()) {
            file.get(a);

            if (a == ' ' || a == '-') { ++flag; }

            switch (flag)
            {
            case 1:
                if (flag == 1 && a == ' ') {
                    person.second_name = name;
                    name.clear();
                }
            case 2:
                if (flag == 2 && a == ' ') {
                    person.name = name;
 
                    name.clear();
                }
            case 3:
                if (flag == 3 && a == ' ') {
                    person.middle_name = name;
                    name.clear();
                }
            case 4:
                if (flag == 4 && a == ' ') {
                    tmp = std::atoi(name.c_str());
                    number.code_country = tmp;
                    name.clear();
                }
            case 5:
                if (flag == 5 && a == ' ') {
                    tmp = std::atoi(name.c_str());
                    number.code_city = tmp;
                    name.clear();
                }
            case 6:
                if (flag == 6 && a == ' ') {
                    number.number = name;
                    name.clear();
                }
            case 7:
                if (flag == 7 && a == '-') {
                    a = ' ';
                    flag = 0;
                    people.push_back(std::make_pair(person, number));
                    
                }
                else if (flag == 7 && a == ' ') {
                    tmp = std::atoi(name.c_str());
                    number.extension_number = tmp;
                    a = ' ';
                    flag = 0;
                    tmp = 0;
                    people.push_back(std::make_pair(person, number));
                }
            }
            if (a == ' ') {
                name.clear();
            }
            else if (a != '\n')name += a;
            
        }
    }

    void SortByNumber() {
        sort(people.begin(), people.end(), CompareNumber);
        for (const auto& [Person, PhoneNumber] : people) {
            std::cout << Person << " " << PhoneNumber << std::endl;
        }   
    }

    void SortByName() {
        sort(people.begin(), people.end(), CompareName);
        for (const auto& [Person, PhoneNumber] : people) {
            std::cout << Person << " " << PhoneNumber << std::endl;
        }
    }

    void ChangePhoneNumber(Person person, PhoneNumber number) {

        auto it = std::find_if(people.begin(), people.end(),
            [person, number](const auto& people) {
                if (people.first == person) {
                    people.second = number;
                }
            });
    }

    ~PhoneBook() {};
};



int main() {
    setlocale(LC_ALL, "Ru");
    std::ifstream file("PhoneBook.txt");
    if (!file.is_open()) {
        std::cerr << "File not found!" << std::endl;
        exit(1);
    }
    PhoneBook book(file);
    book.SortByNumber();
    std::cout << std::endl;
    book.SortByName();
    book.ChangePhoneNumber(Person{"Petr", "Ilin","Artemovich" }, PhoneNumber{ 16, 465, "9155448", 13 });
    return 0;
}

