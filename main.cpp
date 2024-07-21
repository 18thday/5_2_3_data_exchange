#include <iostream>
#include <mutex>

class Data {
public:
    Data(int x, int y) : x_(x), y_(y) {}
private:
    int x_;
    int y_;
    mutable std::mutex m_;

    friend void swap_lock_quard (Data& lhs, Data& rhs);
    friend void swap_scoped_lock (Data& lhs, Data& rhs);
    friend void swap_unique_lock (Data& lhs, Data& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Data& d);
};

std::ostream& operator<<(std::ostream& os, const Data& d) {
    std::lock_guard<std::mutex> lg(d.m_);
    os << "x = " << d.x_ << ", y = " << d.y_;
    return os;
}

void swap_lock_quard (Data& lhs, Data& rhs) {
    std::lock_guard<std::mutex> lg_lhs(lhs.m_);
    std::lock_guard<std::mutex> lg_rhs(rhs.m_);
    std::swap(lhs.x_, rhs.x_);
    std::swap(lhs.y_, rhs.y_);
}

void swap_scoped_lock (Data& lhs, Data& rhs) {
    std::scoped_lock lg_scoped(lhs.m_, rhs.m_);
    std::swap(lhs.x_, rhs.x_);
    std::swap(lhs.y_, rhs.y_);
}

void swap_unique_lock (Data& lhs, Data& rhs) {
    std::unique_lock<std::mutex> lg_lhs(lhs.m_);
    std::unique_lock<std::mutex> lg_rhs(rhs.m_);
    std::swap(lhs.x_, rhs.x_);
    std::swap(lhs.y_, rhs.y_);
}



int main() {
    Data d1(1, 7);
    Data d2(2, 8);
    std::cout << "d1 : " << d1 << std::endl;
    std::cout << "d2 : " << d2 << std::endl;

    std::cout << "swap_lock_quard :" << std::endl;
    swap_lock_quard(d1, d2);

    std::cout << "d1 : " << d1 << std::endl;
    std::cout << "d2 : " << d2 << std::endl;

    std::cout << "swap_scoped_lock :" << std::endl;
    swap_lock_quard(d1, d2);

    std::cout << "d1 : " << d1 << std::endl;
    std::cout << "d2 : " << d2 << std::endl;

    std::cout << "swap_unique_lock :" << std::endl;
    swap_lock_quard(d1, d2);

    std::cout << "d1 : " << d1 << std::endl;
    std::cout << "d2 : " << d2 << std::endl;
    return 0;
}
