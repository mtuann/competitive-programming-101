## I. Giải thích bài toán 

Cho 4 số nguyên $a$, $b$, $c$ và $m$. Bạn hãy tính $a^{b^c} \mod m$.

Tính $b^c \mod (m-1)$ vì theo Định Lý Euler, $a^{b^c} \mod m = a^{(b^c \mod (m-1))} \mod m$

Đây là một phần quan trọng trong việc tối ưu hóa phép toán với số mũ lớn trong bài toán.

### **1. Định Lý Euler**

Định lý Euler là một công cụ mạnh mẽ trong lý thuyết số học, đặc biệt là khi làm việc với phép toán modulo. Định lý Euler phát biểu rằng:

$$a^{\phi(m)} \equiv 1 \ (\text{mod} \ m)$$

Khi $a$ và $m$ là hai số nguyên tố cùng nhau (tức là $\text{gcd}(a, m) = 1 $), với $\phi(m)$ là hàm Euler phi, được định nghĩa là số lượng số nguyên nhỏ hơn hoặc bằng $m$ mà nguyên tố với $m$.

### **2. Định Lý Euler Trong Bài Toán**

Trong bài toán, chúng ta cần tính giá trị của $ a^{b^c} \mod m $. Tuy nhiên, khi số mũ $ b^c $ rất lớn, tính toán trực tiếp $ a^{b^c} $ là không thực tế. Đây là lúc định lý Euler phát huy tác dụng.

Theo định lý Euler, chúng ta có:

$$ a^{\phi(m)} \equiv 1 \ (\text{mod} \ m) $$

Khi đó, nếu $ k \geq \phi(m) $, thì:

$$ a^k \mod m = a^{k \mod \phi(m)} \mod m $$

### **3. Áp Dụng Định Lý Euler Để Tính $ a^{b^c} \mod m $**

Vì $ b^c $ có thể rất lớn, chúng ta không thể tính toán trực tiếp $ a^{b^c} \mod m $. Thay vào đó, chúng ta sẽ tính toán theo một bước trung gian như sau:

1. **Tính $ b^c \mod (\phi(m)) $**:

   Theo định lý Euler, chúng ta chỉ cần tính $ b^c \mod (\phi(m)) $ thay vì tính trực tiếp $ b^c $, bởi vì:

   $
   a^{b^c} \mod m = a^{(b^c \mod \phi(m))} \mod m
   $

   Để tính $ b^c \mod (\phi(m)) $, chúng ta sử dụng phương pháp **Exponentiation by Squaring**.

2. **Tính $ a^{(b^c \mod (\phi(m)))} \mod m $**:

   Sau khi có giá trị $ (b^c \mod (\phi(m))) $, chúng ta tính $a$ nâng lên lũy thừa của giá trị đó rồi tính modulo $m$.

### **4. Ví Dụ Minh Họa**

**Giả sử** $ a = 3 $, $ b = 2 $, $ c = 4 $, và $ m = 10^9 + 7 $.

- **Bước 1**: Tính $\phi(m)$:

  Với $ m = 10^9 + 7 $, một số nguyên tố, $\phi(m) = m - 1$, tức là $\phi(10^9 + 7) = 10^9 + 6$.

- **Bước 2**: Tính $ b^c \mod (\phi(m)) $:

  $
  b^c = 2^4 = 16
  $

  $
  16 \mod (10^9 + 6) = 16
  $

- **Bước 3**: Tính $ a^{(b^c \mod (\phi(m)))} \mod m $:

  $
  a^{b^c} \mod m = 3^{16} \mod (10^9 + 7)
  $

  Tính $ 3^{16} \mod (10^9 + 7) $:

  $
  3^{16} = 43046721
  $

  $
  3^{16} \mod (10^9 + 7) = 43046721
  $

### **5. Mã C++ Để Thực Hiện Các Phép Toán**

```cpp
#include <iostream>

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
```

### **6. Tổng Kết**

Khi bạn cần tính $ a^{b^c} \mod m $, việc tính toán theo định lý Euler giúp bạn giảm độ phức tạp của số mũ cực lớn xuống thành phép toán modulo đơn giản hơn, giúp tiết kiệm thời gian và tài nguyên tính toán.

- **Định lý Euler** giúp giảm số mũ trong các phép toán modulo.
- **Phương pháp Exponentiation by Squaring** giúp tính toán hiệu quả các lũy thừa modulo.

Để tính hàm Euler phi $\phi(n)$ của một số nguyên $n$, bạn có thể sử dụng các công thức và thuật toán sau. Trong trường hợp này, chúng ta sẽ tính $\phi(10)$.

## II. Cách tính hàm Euler phi $\phi(n)$
### 1. **Định Nghĩa Hàm Euler Phi**

Hàm Euler phi của một số nguyên $n$, ký hiệu là $\phi(n)$, là số lượng số nguyên nhỏ hơn hoặc bằng $n$ mà nguyên tố với $n$. 

### 2. **Công Thức Tính $\phi(n)$**

Nếu $n$ có phân tích thừa số nguyên tố:

$n = p_1^{e_1} \cdot p_2^{e_2} \cdots p_k^{e_k}$

Trong đó $p_1, p_2, \ldots, p_k$ là các số nguyên tố khác nhau, thì hàm Euler phi được tính bằng công thức:

$ \phi(n) = n \left(1 - \frac{1}{p_1}\right) \left(1 - \frac{1}{p_2}\right) \cdots \left(1 - \frac{1}{p_k}\right) $

### 3. **Tính $\phi(10)$**

Số $10$ có phân tích thừa số nguyên tố là:

$ 10 = 2 \times 5 $

Dựa vào công thức hàm Euler phi, ta có:

$
\phi(10) = 10 \left(1 - \frac{1}{2}\right) \left(1 - \frac{1}{5}\right)
$

Tính từng bước như sau:

$
\phi(10) = 10 \times \left(1 - \frac{1}{2}\right) \times \left(1 - \frac{1}{5}\right)
$

$
\phi(10) = 10 \times \frac{1}{2} \times \frac{4}{5}
$

$
\phi(10) = 10 \times \frac{4}{10}
$

$
\phi(10) = 4
$

### **Tổng Kết**

- **$\phi(n)$** là số lượng số nguyên nhỏ hơn hoặc bằng $n$ và nguyên tố với $n$.
- Để tính $\phi(n)$, bạn có thể sử dụng công thức $\phi(n) = n \prod_{p|n} (1 - \frac{1}{p})$.
- Trong trường hợp $n = 10$, $\phi(10) = 4$.

## III. Giải Thích Cách Tính Exponentiation by Squaring

**Exponentiation by Squaring** (Tính Lũy Thừa Bằng Phép Bình Phương) là một phương pháp hiệu quả để tính lũy thừa của một số. Phương pháp này giúp tính toán $a^b$ một cách nhanh chóng với thời gian tính toán là $O(\log b)$ so với phương pháp trực tiếp có độ phức tạp $O(b)$.

### **1. Mục Tiêu Của Phương Pháp**

Phương pháp **Exponentiation by Squaring** được sử dụng để tính toán giá trị của $a^b$ (a lũy thừa b) với độ phức tạp thấp hơn nhiều so với phương pháp trực tiếp. Phương pháp này rất hữu ích trong các bài toán liên quan đến lũy thừa và số học modulo.

### **2. Các Tính Chất Cơ Bản**

- **Lũy thừa chẵn**: Khi $b$ là số chẵn, $a^b = (a^2)^{b/2}$.
- **Lũy thừa lẻ**: Khi $b$ là số lẻ, $a^b = a \cdot a^{b-1}$.

### **3. Phương Pháp Exponentiation by Squaring**

Để tính $a^b$, phương pháp Exponentiation by Squaring sẽ áp dụng các bước sau:

- **Nếu $b$ bằng 0**: $a^0 = 1$ (theo định lý số học).
- **Nếu $b$ là số chẵn**: $a^b = (a^2)^{b/2}$.
- **Nếu $b$ là số lẻ**: $a^b = a \cdot a^{b-1}$.

### **4. Thuật Toán**

Dưới đây là thuật toán chi tiết cho phương pháp Exponentiation by Squaring:

1. **Khởi tạo**: $result = 1$, $base = a$.
2. **Lặp qua từng bit của $b$**:
   - **Nếu $b$ lẻ**: $result = (result \cdot base) \% MOD$.
   - **Cập nhật**: $base = (base \cdot base) \% MOD$.
   - **Chia đôi**: $b = b / 2$ (làm tròn xuống).
3. **Kết quả**: Sau khi vòng lặp kết thúc, $result$ chứa giá trị của $a^b \% MOD$.

### **5. Mã Python Của Phương Pháp**

```python
def exponentiation_by_squaring(a, b, MOD):
    result = 1
    base = a % MOD
    while b > 0:
        if b % 2 == 1:  # Nếu b là lẻ
            result = (result * base) % MOD
        base = (base * base) % MOD  # Bình phương base
        b //= 2  # Chia đôi b
    return result
```

### **6. Ví Dụ Cụ Thể**

Tính $3^13 \mod 1000000007$.

- **Khởi tạo**: $result = 1$, $base = 3$.
- **Đầu tiên**: $b = 13$ (lẻ), nên $result = (result \cdot base) \mod 1000000007$.

  ```
  result = (1 \cdot 3) % 1000000007 = 3
  ```

- **Cập nhật**: $base = (3 \cdot 3) \mod 1000000007 = 9$.

- **Chia đôi**: $b = 6$.

- **Lặp**:

  - $b = 6$ (chẵn), nên $result = 3$.
  - $base = (9 \cdot 9) \mod 1000000007 = 81$.
  - $b = 3$.

  - $b = 3$ (lẻ), nên $result = (3 \cdot 81) \mod 1000000007 = 243$.
  - $base = (81 \cdot 81) \mod 1000000007 = 6561$.
  - $b = 1$.

  - $b = 1$ (lẻ), nên $result = (243 \cdot 6561) \mod 1000000007 = 1594323$.
  - $base = (6561 \cdot 6561) \mod 1000000007 = 43046721$.
  - $b = 0$.

  - **Kết quả**: $result = 1594323$.

### **7. Mã C++ Của Phương Pháp**

Dưới đây là mã C++ cho thuật toán Exponentiation by Squaring:

```cpp
#include <iostream>

const int MOD = 1000000007;

long long exponentiation_by_squaring(long long a, long long b, int mod) {
    long long result = 1;
    long long base = a % mod;
    while (b > 0) {
        if (b % 2 == 1) {  // Nếu b là lẻ
            result = (result * base) % mod;
        }
        base = (base * base) % mod;  // Bình phương base
        b /= 2;  // Chia đôi b
    }
    return result;
}

int main() {
    long long a = 3, b = 13;
    std::cout << "3^13 % 1000000007 = " << exponentiation_by_squaring(a, b, MOD) << std::endl;
    return 0;
}
```

### **8. Kết Luận**

Phương pháp Exponentiation by Squaring giúp tính toán lũy thừa hiệu quả hơn nhiều so với phương pháp trực tiếp. Đây là một kỹ thuật quan trọng trong nhiều bài toán số học và thuật toán cần xử lý các phép toán lớn.

### **Tài Liệu Tham Khảo**

- [Exponentiation by Squaring - Wikipedia](https://en.wikipedia.org/wiki/Exponentiation_by_squaring)
- [Exponentiation by Squaring - GeeksforGeeks](https://www.geeksforgeeks.org/exponential-squaring-fast-modulo-multiplication/)

