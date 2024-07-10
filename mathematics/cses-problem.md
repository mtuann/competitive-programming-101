
# Mathematics (CSES Problem Set)
## 1. Josephus Queries

Giới hạn thời gian: 1.00 s  
Giới hạn bộ nhớ: 512 MB

Xem xét một trò chơi có $n$ đứa trẻ (được đánh số $1,2,\dots,n$) đứng thành một vòng tròn. Trong suốt trò chơi, cứ đứa trẻ thứ hai sẽ bị loại ra khỏi vòng tròn, cho đến khi không còn đứa trẻ nào nữa.  
Nhiệm vụ của bạn là xử lý $q$ truy vấn dưới dạng: "khi có $n$ đứa trẻ, đứa trẻ thứ $k$ sẽ bị loại là ai?"  

### Đầu vào  
Dòng đầu tiên của đầu vào chứa một số nguyên $q$: số lượng truy vấn.  
Sau đó, có $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai số nguyên $n$ và $k$: số lượng đứa trẻ và vị trí của đứa trẻ.  

### Đầu ra  
In ra $q$ số nguyên: câu trả lời cho mỗi truy vấn.

### Ràng buộc

$1 \le q \le 10^5$  
$1 \le k \le n \le 10^9$

### Ví dụ  
Đầu vào:
```
4
7 1
7 3
2 2
1337 1313
```

Đầu ra:
```
2
6
1
1107
```
Giải thích: Với $n = 7, k = 3$ thì thứ tự các đứa trẻ bị loại lần lượt là $2, 4, 6, 1, 5, 3$.

---

## 2. Exponentiation

Giới hạn thời gian: 1.00 s  
Giới hạn bộ nhớ: 512 MB

Nhiệm vụ của bạn là tính hiệu quả giá trị $a^b$ modulo $10^9+7$.  
Lưu ý rằng trong nhiệm vụ này, ta giả định $0^0=1$.

### Đầu vào  
Dòng đầu tiên của đầu vào chứa một số nguyên $n$: số lượng phép tính.  
Sau đó, có $n$ dòng, mỗi dòng chứa hai số nguyên $a$ và $b$.

### Đầu ra  
In ra mỗi giá trị $a^b$ modulo $10^9+7$.

### Ràng buộc

$1 \le n \le 2 \cdot 10^5$  
$0 \le a,b \le 10^9$

### Ví dụ  
Đầu vào:
```
3
3 4
2 8
123 123
```

Đầu ra:
```
81
256
921450052
```

---
## 3. Exponentiation II

Nhiệm vụ của bạn là tính hiệu quả giá trị $a^{b^c}$ modulo $10^9+7$.  
Lưu ý rằng trong nhiệm vụ này, ta giả định $0^0=1$.

### Đầu vào  
Dòng đầu tiên của đầu vào chứa một số nguyên $n$: số lượng phép tính.  
Sau đó, có $n$ dòng, mỗi dòng chứa ba số nguyên $a$, $b$ và $c$.

### Đầu ra  
In ra mỗi giá trị $a^{b^c}$ modulo $10^9+7$.

### Ràng buộc

$1 \le n \le 10^5$  
$0 \le a,b,c \le 10^9$

### Ví dụ  
Đầu vào:
```
3
3 7 1
15 2 2
3 4 5
```

Đầu ra:
```
2187
50625
763327764
```




## 4. Counting Divisors

Giới hạn thời gian: 1.00 s  
Giới hạn bộ nhớ: 512 MB

Cho $n$ số nguyên, nhiệm vụ của bạn là báo cáo số lượng ước của mỗi số nguyên.
Ví dụ, nếu $x=18$, câu trả lời đúng là 6 vì các ước của nó là 1, 2, 3, 6, 9, 18.

### Đầu vào  
Dòng đầu tiên của đầu vào có một số nguyên $n$: số lượng các số nguyên.  
Sau đó, có $n$ dòng, mỗi dòng chứa một số nguyên $x$.

### Đầu ra  
Với mỗi số nguyên, in ra số lượng ước của nó.

### Ràng buộc

$1 \le n \le 10^5$  
$1 \le x \le 10^6$

### Ví dụ  
Đầu vào:
```
3
16
17
18
```

Đầu ra:
```
5
2
6
```

---

## 5. Common Divisors

Giới hạn thời gian: 1.00 s  
Giới hạn bộ nhớ: 512 MB

Bạn được cho một mảng gồm $n$ số nguyên dương. Nhiệm vụ của bạn là tìm hai số sao cho ước chung lớn nhất của chúng là lớn nhất có thể.
### Đầu vào  
Dòng đầu tiên của đầu vào có một số nguyên $n$: kích thước của mảng.  
Dòng thứ hai có $n$ số nguyên $x_1, x_2, \ldots, x_n$: các phần tử của mảng.

### Đầu ra  
In ra ước chung lớn nhất lớn nhất.

### Ràng buộc

$2 \le n \le 2 \cdot 10^5$  
$1 \le x_i \le 10^6$

### Ví dụ  
Đầu vào:
```
5
3 14 15 7 9
```

Đầu ra:
```
7
```
---

## 6. Sum of Divisors
Giới hạn thời gian: 1.00 s  
Giới hạn bộ nhớ: 512 MB

Hãy để $\sigma(n)$ là tổng các ước của một số nguyên $n$. Ví dụ, $\sigma(12) = 1 + 2 + 3 + 4 + 6 + 12 = 28$. Nhiệm vụ của bạn là tính tổng $\sum_{i=1}^n \sigma(i)$ modulo $10^9+7$.
### Đầu vào
Dòng đầu tiên và duy nhất của đầu vào có một số nguyên $n$.

### Đầu ra
In ra giá trị của $\sum_{i=1}^n \sigma(i)$ modulo $10^9+7$.

### Ràng buộc

$1 \le n \le 10^{12}$

### Ví dụ  
Đầu vào:
```
5
```

Đầu ra:
```
21
```
---

## 7. Divisor Analysis

Giới hạn thời gian: 1.00 s  
Giới hạn bộ nhớ: 512 MB

Cho một số nguyên, nhiệm vụ của bạn là tìm số lượng, tổng và tích của các ước của nó. Ví dụ, hãy xem xét số 12:

- số lượng ước là 6 (là các số 1, 2, 3, 4, 6, 12)
- tổng các ước là $1 + 2 + 3 + 4 + 6 + 12 = 28$
- tích các ước là $1 \cdot 2 \cdot 3 \cdot 4 \cdot 6 \cdot 12 = 1728$

Vì số đầu vào có thể lớn, nó được đưa ra dưới dạng phân tích thừa số nguyên tố.

### Đầu vào
Dòng đầu tiên có một số nguyên $n$: số phần trong phân tích thừa số nguyên tố.
Sau đó, có $n$ dòng mô tả phân tích thừa số. Mỗi dòng có hai số $x$ và $k$ trong đó $x$ là một số nguyên tố và $k$ là số mũ của nó.

### Đầu ra
In ra ba số nguyên modulo $10^9+7$: số lượng, tổng và tích của các ước.

### Ràng buộc

$1 \le n \le 10^5$  
$2 \le x \le 10^6$  
mỗi $x$ là một số nguyên tố khác nhau  
$1 \le k \le 10^9$

### Ví dụ  
Đầu vào:
```
2
2 2
3 1
```

Đầu ra:
```
6 28 1728
```

---

## 8. Prime Multiples


Giới hạn thời gian: 1.00 s  
Giới hạn bộ nhớ: 512 MB

Bạn được cho $k$ số nguyên tố phân biệt $a_1,a_2,\ldots,a_k$ và một số nguyên $n$.
Nhiệm vụ của bạn là tính xem có bao nhiêu số nguyên dương đầu tiên trong khoảng từ 1 đến $n$ chia hết cho ít nhất một trong những số nguyên tố đã cho.

### Đầu vào
Dòng đầu tiên có hai số nguyên $n$ và $k$.
Dòng thứ hai có $k$ số nguyên tố $a_1,a_2,\ldots,a_k$.

### Đầu ra
In ra một số nguyên: số lượng các số trong khoảng từ $1,2,\ldots,n$ chia hết cho ít nhất một trong các số nguyên tố.

### Ràng buộc

$1 \le n \le 10^{18}$  
$1 \le k \le 20$  
$2 \le a_i \le n$

### Ví dụ
Đầu vào:
```
20 2
2 5
```

Đầu ra:
```
12
```

Giải thích: 12 số là 2, 4, 5, 6, 8, 10, 12, 14, 15, 16, 18, 20.

---

## 9. Counting Coprime Pairs

Giới hạn thời gian: 1.00 s  
Giới hạn bộ nhớ: 512 MB

Cho một danh sách gồm $n$ số nguyên dương, nhiệm vụ của bạn là đếm số cặp số nguyên trong danh sách có ước số chung lớn nhất là 1 (nghĩa là chúng là các số nguyên tố cùng nhau).
### Đầu vào
Dòng đầu tiên chứa một số nguyên $n$: số lượng phần tử.
Dòng tiếp theo chứa $n$ số nguyên $x_1,x_2,\dots,x_n$: nội dung của danh sách.

### Đầu ra
In ra một số nguyên: đáp án của bài toán.

### Ràng buộc
$1 \le n \le 10^5$  
$1 \le x_i \le 10^6$

### Ví dụ
Đầu vào:
```
8
5 4 20 1 16 17 5 15
```

Đầu ra:
```
19
```

---

## 10. Binomial Coefficients

Giới hạn thời gian: 1.00 s  
Giới hạn bộ nhớ: 512 MB

Nhiệm vụ của bạn là tính toán các hệ số nhị phân $n$ theo modulo $10^9+7$.
Hệ số nhị phân $\binom{a}{b}$ có thể được tính bằng công thức $\frac{a!}{b!(a-b)!}$. Chúng ta giả sử rằng $a$ và $b$ là các số nguyên và $0 \le b \le a$.

### Đầu vào
Dòng đầu tiên chứa một số nguyên $n$: số lượng phép tính.
Sau đó, có $n$ dòng, mỗi dòng chứa hai số nguyên $a$ và $b$: số lượng và chỉ số của hệ số nhị phân cần tính.

### Đầu ra
In ra mỗi hệ số nhị phân theo modulo $10^9+7$.

### Ràng buộc
$1 \le n \le 10^5$  
$0 \le b \le a \le 10^6$

### Ví dụ
Đầu vào:
```
3
5 3
8 1
9 5
```

Đầu ra:
```
10
8
126
```

### Hướng dẫn tính toán

Để tính toán các hệ số nhị phân modulo $10^9+7$, bạn có thể sử dụng các phương pháp tối ưu như:

1. **Tính giai thừa** và **Tính nghịch đảo của giai thừa** modulo $10^9+7$.
2. **Dùng định lý Fermat** để tính nghịch đảo: $\text{inv}(x) \equiv x^{MOD-2} \mod MOD$ khi $MOD$ là số nguyên tố.

### Mã code CPP
```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

// Hàm tính hệ số nhị phân
long long binomial_coefficient(int a, int b, const vector<long long>& fact, const vector<long long>& inv_fact) {
    return fact[a] * inv_fact[b] % MOD * inv_fact[a - b] % MOD;
}

// Hàm tiền xử lý giai thừa và nghịch đảo giai thừa
void precompute_factorials(int max_n, vector<long long>& fact, vector<long long>& inv_fact) {
    fact[0] = 1;
    for (int i = 1; i <= max_n; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv_fact[max_n] = 1;
    // Tính nghịch đảo của giai thừa[max_n] bằng cách sử dụng định lý Fermat
    for (int i = max_n; i > 0; --i) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
    inv_fact[0] = 1;  // inv_fact[0] mặc định là 1
}

int main() {
    int max_a = 1e6;
    
    // Khởi tạo các vector để lưu trữ giai thừa và nghịch đảo giai thừa
    vector<long long> fact(max_a + 1), inv_fact(max_a + 1);
    
    // Tiền xử lý giai thừa và nghịch đảo giai thừa
    precompute_factorials(max_a, fact, inv_fact);

    // Ví dụ sử dụng hàm binomial_coefficient
    int a = 5, b = 3;
    cout << "C(" << a << ", " << b << ") = " << binomial_coefficient(a, b, fact, inv_fact) << endl;
    
    return 0;
}

```

---

## 11. Creating Strings II

Giới hạn thời gian: 1.00 s  
Giới hạn bộ nhớ: 512 MB

Cho một chuỗi, nhiệm vụ của bạn là tính số lượng các chuỗi khác nhau có thể được tạo ra bằng cách sử dụng các ký tự của chuỗi đó.

### Đầu vào
Dòng duy nhất chứa một chuỗi có độ dài $n$. Mỗi ký tự nằm trong khoảng từ a đến z.

### Đầu ra
In ra số lượng các chuỗi khác nhau theo modulo $10^9+7$.

### Ràng buộc
$1 \le n \le 10^6$

### Ví dụ
Đầu vào:
```
aabac
```

Đầu ra:
```
20
```

### Hướng dẫn tính toán

Để tính số lượng các chuỗi khác nhau có thể được tạo ra, bạn có thể sử dụng công thức tính số tổ hợp của các ký tự, điều này liên quan đến giai thừa và phân phối các ký tự.

Công thức để tính số lượng chuỗi khác nhau là:

$$
\text{Số lượng chuỗi} = \frac{n!}{f_1! \times f_2! \times \cdots \times f_k!}
$$

Trong đó, $n$ là độ dài của chuỗi, và $f_i$ là số lần xuất hiện của ký tự thứ $i$.

### Ví dụ tính toán

- Đối với chuỗi "aabac":
  - Số lượng ký tự là $5$.
  - Các ký tự và số lần xuất hiện là:
    - `a`: 3 lần
    - `b`: 1 lần
    - `c`: 1 lần
  - Số lượng các chuỗi khác nhau là:
    $$
    \frac{5!}{3! \times 1! \times 1!} = \frac{120}{6 \times 1 \times 1} = 20
    $$

### Mã code CPP

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

const int MOD = 1e9 + 7;

// Hàm tính giai thừa modulo
long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result = result * i % MOD;
    }
    return result;
}

// Hàm tính nghịch đảo modulo bằng định lý Fermat
long long mod_inverse(long long x, long long mod) {
    long long result = 1;
    long long power = mod - 2;  // Định lý Fermat: a^(p-1) ≡ 1 (mod p) => a^(p-2) ≡ a^(-1) (mod p)
    while (power > 0) {
        if (power % 2 == 1) {
            result = result * x % mod;
        }
        x = x * x % mod;
        power /= 2;
    }
    return result;
}

// Hàm tính số lượng các chuỗi khác nhau có thể tạo ra từ các ký tự của chuỗi đầu vào
long long count_distinct_strings(const string& s) {
    unordered_map<char, int> freq;
    for (char c : s) {
        freq[c]++;
    }
    
    int n = s.length();
    long long result = factorial(n);
    
    for (auto& [ch, count] : freq) {
        result = result * mod_inverse(factorial(count), MOD) % MOD;
    }
    
    return result;
}

int main() {
    // Ví dụ sử dụng
    string s = "aabac";
    cout << count_distinct_strings(s) << endl;  // Output: 20
    
    return 0;
}

```

### Hướng dẫn giải thuật

1. **Đếm số lần xuất hiện của từng ký tự**: Sử dụng `Counter` từ thư viện `collections`.
2. **Tính giai thừa của độ dài chuỗi**: `factorial(n)`.
3. **Tính nghịch đảo của giai thừa cho từng ký tự**: Sử dụng định lý Fermat để tính nghịch đảo modulo.
4. **Tính số chuỗi khác nhau**: Áp dụng công thức và in ra kết quả modulo $10^9+7$.

---

## 12. Distributing Apples


### Time limit: 1.00 s
### Memory limit: 512 MB

Có $n$ trẻ em và $m$ quả táo sẽ được phân phát cho chúng. Nhiệm vụ của bạn là đếm số cách phân phát táo sao cho mỗi trẻ em có thể nhận từ 0 đến $m$ quả táo.

Ví dụ, nếu $n = 3$ và $m = 2$, có 6 cách phân phát: `[0,0,2]`, `[0,1,1]`, `[0,2,0]`, `[1,0,1]`, `[1,1,0]` và `[2,0,0]`.

**Input**  
Dòng đầu tiên chứa hai số nguyên $n$ và $m$.

**Output**  
In ra số cách phân phát theo mô-đun $10^9 + 7$.

**Constraints**

- $1 \leq n, m \leq 10^6$

**Example**

**Input:**

```
3 2
```

**Output:**

```
6
```

---


## 13. Christmas Party

### Time limit: 1.00 s
### Memory limit: 512 MB

Có $n$ trẻ em tại một bữa tiệc Giáng Sinh, và mỗi trẻ em đều mang một món quà. Ý tưởng là mỗi người sẽ nhận được một món quà được mang đến bởi một người khác.

Hãy tính số cách phân phát quà sao cho mỗi người nhận được một món quà từ người khác.

**Input**  
Dòng duy nhất chứa một số nguyên $n$: số lượng trẻ em.

**Output**  
In ra số cách phân phát theo mô-đun $10^9 + 7$.

**Constraints**

- $1 \leq n \leq 10^6$

**Example**

**Input:**

```
4
```

**Output:**

```
9
```

---

## 14. Bracket Sequences I
---

## 15. Bracket Sequences II
---

## 16. Counting Necklaces
---

## 17. Counting Grids
---

## 18. Fibonacci Numbers
---

## 19. Throwing Dice
---

## 20. Graph Paths I
---

## 21. Graph Paths II
---

## 22. Dice Probability
---

## 23. Moving Robots
---

## 24. Candy Lottery
---

## 25. Inversion Probability
---

## 26. Stick Game
---

## 27. Nim Game I
---

## 28. Nim Game II
---

## 29. Stair Game
---

## 30. Grundy's Game
---

## 31. Another Game
---
