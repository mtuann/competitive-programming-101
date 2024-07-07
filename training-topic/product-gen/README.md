In this tutorial, we will learn how to generate test cases and check the output of the product problem: Given two integers `a` and `b`, you need to calculate the product of `a` and `b` ($1 \leq a, b \leq 10^9$.)


### Step 01: Write `product_gen.cpp`
```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random number in a given range [min, max]
long long randomNumber(long long min, long long max) {
    long long res = 0;
    for (int i = 0; i < 4; ++i)
        res = (res << 15) + (rand() & 0x7FFF);
    return min + res % (max - min + 1);
}

int main() {
    freopen("product.inp", "w", stdout);
    srand(time(nullptr)); // Seed for random number generation

    // random a, b in range [1, 10^9] with 4 subtask [1, 10], [1, 1e3], [1, 1e6], [1, 1e9]
    long long type = randomNumber(1, 4);
    long long a, b;
    if (type == 1) {
        a = randomNumber(1, 10);
        b = randomNumber(1, 10);
    } else if (type == 2) {
        a = randomNumber(1, 1000);
        b = randomNumber(1, 1000);
    } else if (type == 3) {
        a = randomNumber(1, 1000000);
        b = randomNumber(1, 1000000);
    } else {
        a = randomNumber(1, 1000000000);
        b = randomNumber(1, 1000000000);
    }
    cout << a << " " << b << endl;
    cerr << a << " " << b << endl;
    return 0;
}
```

### Step 02: Write `product_slow.cpp`
```cpp
#include <iostream>

using namespace std;

int main() {
    freopen("product.inp", "r", stdin);
    freopen("product.ans", "w", stdout);

    long long a, b;
    cin >> a >> b;
    long long sum = 0;
    for (int i = 0; i < a; ++i) {
        sum += b;
    }
    cout << sum << endl;
    return 0;
}
```

### Step 03: Write `problem_solution.cpp`
```cpp
#include <iostream>

using namespace std;

int main() {
    freopen("product.inp", "r", stdin);
    freopen("product.out", "w", stdout);

    long long a, b;
    cin >> a >> b;
    cout << a * b << endl;
    return 0;
}
```

### Step 04: Running bash script in Window, `product_check.sh`
- For Window, please make sure the `.exe` file is generated after compiling the source code.
After that, you can use `fc` command to compare two files.

- For Linux, you can use `diff` command. Before running the bash script, please make sure the file has the execute permission and the output file is generated.

```bash
# List of commands to run in Linux/ MacOS
# adding -O2, -Wall, -Wextra and compile with c++14 standard

g++ -O2 -Wall -Wextra -std=c++14 -o product_gen.exe product_gen.cpp

g++ -O2 -Wall -Wextra -std=c++14 -o product_slow.exe product_slow.cpp

g++ -O2 -Wall -Wextra -std=c++14 -o problem_solution.exe problem_solution.cpp

chmod +x product_check.sh

./product_check.sh
```

```bash
# List of commands to run in Window
product_gen.exe
product_slow.exe
problem_solution.exe
fc /w product.ans product.out # Window

# List of commands to run in Unix/ MacOS
./product_gen.exe
./product_slow.exe
./problem_solution.exe
diff product.ans product.out
```





