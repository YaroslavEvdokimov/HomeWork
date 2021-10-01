#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm> 
#include <fstream>
#include <string>
#include <chrono>

class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::string m_name;
    std::chrono::time_point<clock_t> m_beg;
    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }

public:
    Timer() : m_beg(clock_t::now()) { }
    Timer(std::string name) : m_name(name), m_beg(clock_t::now()) { }

    void start(std::string name) {
        m_name = name;
        m_beg = clock_t::now();
    }
    void print() const {
        std::cout << m_name << ":\t" << elapsed() * 1000 << " ms" << '\n';
    }
};

void Swap(int* ptr_a, int* ptr_b) {
    int tmp = *ptr_a;
    *ptr_a = *ptr_b;
    *ptr_b = tmp;
}

void SortPointer(std::vector<int*>& point) {
    for (int i = 0; i < point.size(); ++i) {

        for (int j = i + 1; j < point.size(); ++j) {
            if (*point[i] > *point[j]) {
                Swap(point[i], point[j]);
            }
        }
    }
}


bool Find(std::string str) {

    char vow[] = "AEIOUYaeiouy";
    int i = 0;
    return (str.find(vow[++i]) != std::string::npos);
}

int main() {
    //Task 1
    int a = 4;
    int b = 5;
    int* ptr_a = &a;
    int* ptr_b = &b;
    std::cout << *ptr_a << " " << *ptr_b << std::endl;
    Swap(ptr_a, ptr_b);
    std::cout << *ptr_a << " " << *ptr_b << std::endl;
    //Task 2
    std::vector<int*> point;
    int tmp[] = { 1,2,4,3,5,6,1,45,6,1 };
    for (int i = 0; i < 10; ++i) {
        point.push_back(tmp + i);
    }
    SortPointer(point);
    for (int i = 0; i < point.size(); ++i)
        std::cout << *point[i] << " ";
    //Task 3
    
    std::vector<std::string> str;
    std::string tmp_str;
    std::ifstream file_o("1.txt");
    if (file_o.is_open()){
    while (getline(file_o, tmp_str)) {
        str.push_back(tmp_str);
    } 
    auto n = std::count_if(str.begin(), str.end(), Find);
    std::cout << n;
    }
    return 0;
}