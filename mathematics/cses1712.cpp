#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;

// Hàm tính a^b mod m bằng phương pháp Exponentiation by Squaring
long long mod_exp(long long a, long long b, long long m) {
    long long result = 1;
    a %= m;  // Tinh a mod m trước để tránh số quá lớn
    while (b > 0) {
        if (b % 2 == 1) {  // Nếu b lẻ, nhân kết quả với a
            result = (result * a) % m;
        }
        a = (a * a) % m;  // Cập nhật a = a^2
        b /= 2;  // Chia b cho 2
    }
    return result;
}

// Hàm tính a^(b^c) mod m
long long calculate(long long a, long long b, long long c, long long m) {
    if (b == 0) return 1;  // Nếu b = 0, bất kỳ số mũ nào đều là 1
    // Tính b^c mod (m-1) vì theo định lý Euler, a^(b^c) % m = a^(b^c mod (m-1)) % m
    long long exp = mod_exp(b, c, m - 1);  // b^c % (m-1)
    return mod_exp(a, exp, m);  // a^exp % m
}

int main() {
    long long a, b, c;
    std::cin >> a >> b >> c;
    std::cout << calculate(a, b, c, MOD) << std::endl;
    return 0;
}
