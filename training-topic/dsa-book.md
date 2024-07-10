# I. Các kiến thức cơ bản
## 1. Số nguyên tố

### Định lý Fermat

- Phương pháp kiểm tra số nguyên tố theo xác suất sử dụng định lý Fermat như sau:

Nếu $n$ là số nguyên tố thì với mọi số nguyên $a$ thỏa mãn $1 \leq a < n$ ta có:

$$a^{n-1} \equiv 1 \pmod{n}$$

- Định lý Fermat chỉ là một phương pháp kiểm tra số nguyên tố theo xác suất, không phải là phương pháp chắc chắn.

- Áp dụng định lý Fermat để kiểm tra số nguyên tố với a = 2
    - Nếu $2^{n-1} \not\equiv 1 \pmod{n}$ thì n không phải là số nguyên tố.
    - Nếu $2^{n-1} \equiv 1 \pmod{n}$ thì n có thể là số nguyên tố.



###  Sàng nguyên tố

- Sàng nguyên tố là một phương pháp tìm tất cả các số nguyên tố nhỏ hơn một số nguyên dương n cho trước. 
- Có nhiều cách sàng nguyên tố khác nhau, mỗi cách có ưu nhược điểm riêng, sàng Eratosthenes hay sàng Atkin là hai cách sàng nguyên tố phổ biến nhất.

## 2.   Ước số, bội số

### Số các ước số của một số
- Phân tích một số nguyên dương thành tích các thừa số nguyên tố, số ước của một số nguyên dương là tích của các bội số của các ước số nguyên tố đó.

Cụ thể, với một số nguyên dương $n$ phân tích thành dạng:

$$n = p_1^{a_1} \times p_2^{a_2} \times \ldots \times p_k^{a_k}$$

thì số ước của $n$ là:

$$d(n) = (a_1 + 1) \times (a_2 + 1) \times \ldots \times (a_k + 1)$$

### Tổng ước số
Tổng các ước số của một số nguyên dương $n$ có thể được tính bằng công thức:

$$\sigma(n) = \prod_{i=1}^{k} \frac{p_i^{a_i+1} - 1}{p_i - 1}$$



### Ước số chung lớn nhất, bội số chung nhỏ nhất
- Ước số chung lớn nhất (ƯCLN) của hai số nguyên dương $a$ và $b$ là số nguyên dương lớn nhất mà cả $a$ và $b$ đều chia hết cho nó.
- Bội số chung nhỏ nhất (BCNN) của hai số nguyên dương $a$ và $b$ là số nguyên dương nhỏ nhất mà nó chia hết cho cả $a$ và $b$.

Công thức tính ƯCLN và BCNN:

$$\text{BCNN}(a, b) = \frac{a \times b}{\text{ƯCLN}(a, b)}$$

- ƯCLN và BCNN của hai số nguyên dương $a$ và $b$ cũng chính là ƯCLN và BCNN của dãy số $a, b, a \mod b, b \mod (a \mod b), \ldots$.


## 3. Lý thuyết tập hợp
- Các phép toán trên tập hợp
- Các tính chất của phép toán trên tập hợp
- Tích Descartes (Đề-các) của các tập hợp
- Nguyên lí cộng/ nhân/ bù trừ tập hợp
- Chỉnh hợp lặp/ không lặp
    - Chỉnh hợp lặp: $A_n^k = n^k$
    - Chỉnh hợp không lặp: $A_n^k = \frac{n!}{(n-k)!}$
- Hoán vị: $n!$
- Tổ hợp: $C(n, k) = \frac{n!}{k!(n-k)!}$

    - $C(n, k) = C(n, n-k)$
    - $C(n, k) = C(n-1, k) + C(n-1, k-1)$
    - $C(n, 0) = C(n, n) = 1$
    - $C(n, 0) + C(n, 1) + \ldots + C(n, n) = 2^n$

## 4. Số Fibonacci
- Bài toán sinh sản của các cặp thỏ
- Bài toán xếp domino vào bảng $2 \times n$ với các thanh domino $1 \times 2$ và $2 \times 1$

Công thức:
- $F_0 = 0, F_1 = 1$
- $F_n = F_{n-1} + F_{n-2}$ với mọi số nguyên dương $n \geq 2$

Công thức tổng quát:
- $F_n = \frac{\phi^n - \psi^n}{\sqrt{5}}$ với $\phi = \frac{1 + \sqrt{5}}{2}$ và $\psi = \frac{1 - \sqrt{5}}{2}$

## 5. Số Catalan
- Số Catalan là dãy số xuất hiện trong nhiều bài toán liên quan đến cấu trúc dữ liệu và giải thuật như:
    - Số cách đặt n cặp dấu ngoặc đúng
    - Số lượng cây nhị phân có n đỉnh (lá)
    - Số cách chia đa giác lồi n đỉnh thành các tam giác không giao nhau

Công thức:
- $C_0 = 1$

- $C_n = \sum_{i=0}^{n-1} C_i \times C_{n-1-i}$ với mọi số nguyên dương $n \geq 1$


Công thức tổng quát:
- $C_n = \frac{1}{n+1} \times C(2n, n)$ với mọi số nguyên dương $n$

## 6. Xử lý số nguyên lớn
- Số nguyên lớn là số nguyên có giá trị tuyệt đối lớn hơn giới hạn mà kiểu dữ liệu số nguyên thông thường có thể biểu diễn. Trong ngôn ngữ lập trình C++, số nguyên lớn nhất mà kiểu dữ liệu `long long` có thể biểu diễn là $2^{64} - 1$ (tức là $10^{18}$).

- Sử dụng string để biểu diễn số nguyên lớn, và cài đặt các phép toán so sánh, cộng, trừ, nhân, chia, mod trên số nguyên lớn. Với các phép tính nhân và mod trên số nguyên lớn, ta cần cài đặt thuật toán nhân và chia với một số nhỏ hơn.


# II. Sắp xếp và tìm kiếm
- Bubble sort
- Quick sort
- Counting sort
- Other sorts
    - Selection sort
    - Insertion sort
    - Merge sort
    - Heap sort
    - Radix sort

# III. Thiết kế giải thuật
## 1. Quay lui (Backtracking)
- Bài toán xếp hậu
- In ra chỉnh hợp lặp/ không lặp, tổ hợp chập k của n phần tử
- Dùng nhánh và cận để giảm thời gian chạy của thuật toán quay lui (ví dụ bài toán TSP - Travelling Salesman Problem)

## 2. Tham lam (Greedy)
- Lập lịch giảm thiểu thời gian chờ đợi. Cho $N$ công việc, mỗi công việc $i$ có thời gian thực hiện $t_i$ và thời gian deadline $d_i$. Mục tiêu là sắp xếp các công việc sao cho tổng thời gian chờ đợi nhỏ nhất.

Nhận xét:
- Nếu sắp xếp các công việc theo thứ tự tăng dần thời gian thực hiện $t_i$ thì tổng thời gian chờ đợi sẽ nhỏ nhất.
- Độ phức tạp: $O(N \log N)$

## 3. Chia để trị (Divide and Conquer)
- Bài toán tính $a^n$ với $n$ là số nguyên dương
- Bài toán Diff, trả về max(a[i] - a[j]) với mọi cặp $1 \leq i, j \leq n$ ($i \neq j$).
- Bài toán lát nền, kích thước $n \times n$ với $n = 2^k$ ($ 1 \leq k \leq 10$) bị khuyết một phần tư tại góc trên phải (khuyết phần 2) bằng những viên gạch hình thước tạo bởi 3 ô vuông đơn vị.
    - Lời giải: Đệ quy $cover(x, y, s, t)$ để lát nền có kích thước $s$, bị khuyết phần tư tại góc $t$ ($t = 1, 2, 3, 4$), có tọa độ trên cùng bên trái là $(x, y)$.
- Bài toán tháp Hà Nội
    - Lời giải: Đệ quy chuyển n-1 đĩa từ cột A sang cột B, chuyển đĩa thứ n từ cột A sang cột C, chuyển n-1 đĩa từ cột B sang cột C.
- Merge sort
    - Lời giải: Đệ quy sắp xếp nửa đầu mảng, sắp xếp nửa sau mảng, sau đó trộn hai mảng đã sắp xếp.

## 4. Quy hoạch động (Dynamic Programming)
- Số Fibonacci: Sử dụng mảng lưu trữ các số Fibonacci đã tính, $F_i = F_{i-1} + F_{i-2}$ với $i \geq 2$, $F_0 = 0, F_1 = 1$.
- Dãy con đơn điệu tăng dài nhất: Sử dụng mảng $dp[i]$ lưu độ dài dãy con đơn điệu tăng dài nhất kết thúc tại phần tử thứ $i$.
    - Với mỗi $j < i$, nếu $a[j] < a[i]$ thì $dp[i] = \max(dp[i], dp[j] + 1)$.
    - Đáp án của bài toán là $\max(dp[i])$ với $0 \leq i < n$. Bạn đọc có thể chèn phần tử - infinify và infinify đầu và cuối mảng ban đầu để đảm bảo dãy con tăng dài nhất gồm cả 2 phần tử này.
    - Có thể cải tiến thuật toán bằng cách sử dụng binary search để tìm vị trí chèn phần tử $a[i]$ vào mảng $dp$. Ở cách này ta sẽ duy trì một mảng $dp$ tăng dần, mỗi lần cập nhật $dp[i]$ ta sẽ tìm vị trí chèn phần tử $a[i]$ vào mảng $dp$ bằng binary search.

        <details>
        <summary>LIS - CPP-Code</summary>

        ```cpp
        #include <iostream>
        #include <vector>
        #include <algorithm>

        // Function to calculate the length of the longest increasing subsequence
        int longestIncreasingSubsequence(std::vector<int>& nums) {
            if (nums.empty()) return 0;

            std::vector<int> lis; // This will store the smallest tail for all increasing subsequences of different lengths

            for (int num : nums) {
                auto it = std::lower_bound(lis.begin(), lis.end(), num); // Find the position of the smallest number >= num
                if (it == lis.end()) {
                    lis.push_back(num); // If num is greater than all elements in lis, append it
                } else {
                    *it = num; // Otherwise, replace the first element >= num with num
                }
            }

            return lis.size(); // The size of lis is the length of the longest increasing subsequence
        }

        int main() {
            std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
            std::cout << "Length of Longest Increasing Subsequence: " << longestIncreasingSubsequence(nums) << std::endl;
            return 0;
        }
        ```
        </details>

- Bài toán cái túi. Cho $N$ loại vật phẩm, mỗi loại có khối lượng $w_i$ và giá trị $v_i$, và một cái túi có khả năng chứa tối đa $W$ khối lượng. Mục tiêu là chọn một số vật phẩm sao cho tổng giá trị của chúng là lớn nhất mà tổng khối lượng không vượt quá $W$.
    - Sử dụng mảng $dp[i][j]$ lưu giá trị lớn nhất có thể đạt được với $i$ vật phẩm đầu tiên và khối lượng tối đa là $j$.
    - Công thức cập nhật: $dp[i][j] = \max(dp[i-1][j], dp[i-1][j-w_i] + v_i)$.
    - Đáp án của bài toán là $\max(dp[N][j])$ với $0 \leq j \leq W$.
    - Độ phức tạp: $O(NW)$.

# IV. Các thuật toán trên đồ thị
## 1. Các khái niệm cơ bản
Đồ thị là một cấu trúc dữ liệu biểu diễn mối quan hệ giữa các đối tượng. Đồ thị gồm các đỉnh (vertex) và các cạnh (edge) nối các đỉnh với nhau.

Kí hiệu: $G = (V, E)$ với $V$ là tập hợp các đỉnh và $E$ là tập hợp các cạnh.

Phân loại đồ thị theo $E$:
- Đồ thị vô hướng (undirected graph): Các cạnh không có hướng.
- Đồ thị có hướng (directed graph): Các cạnh có hướng.
- Đơn đồ thị (simple graph): Không có nhiều hơn một cạnh nối cùng một cặp đỉnh $(u, v)$.
- Đa đồ thị (multigraph): Có thể có nhiều cạnh nối cùng một cặp đỉnh $(u, v)$.

Phân loại đồ thị theo $V$:
- Đồ thị đầy đủ (complete graph): Mọi cặp đỉnh $(u, v)$ đều được nối với nhau.
- Đồ thị rỗng (null graph): Không có cạnh nào.
- Đồ thị con (subgraph): Đồ thị $G' = (V', E')$ với $V' \subseteq V$ và $E' \subseteq E$.
- Đồ thị con liên thông (connected graph): Mọi cặp đỉnh $(u, v)$ đều có đường đi giữa chúng.
- Cây (tree): Đồ thị vô hướng liên thông không chứa chu trình.
- Cây khung (spanning tree): Cây con của đồ thị liên thông chứa tất cả các đỉnh của đồ thị.
- Đồ thị phẳng (planar graph): Có thể vẽ trên mặt phẳng mà không có cạnh nào giao nhau. Một đồ thị là đồ thị phẳng nếu nó không chứa đồ thị con đẳng cấu/ đồng dạng (isomorphic graph) $K(3, 3)$ hoặc $K_5$.

- Đồ thị hai phía (bipartite graph): Có thể chia tập đỉnh thành hai tập con $V = V_1 \cup V_2$ sao cho mọi cạnh nối hai đỉnh cùng tập đều nối giữa hai tập khác nhau.
- Đồ thị Euler: Có một chu trình Euler, tức là chu trình đi qua mỗi cạnh đúng một lần.
- Đồ thị Hamilton: Có một chu trình Hamilton, tức là chu trình đi qua mỗi đỉnh đúng một lần.
- Đồ thị đồng dạng (isomorphic graph): Hai đồ thị có cùng cấu trúc, tức là có thể biến đổi một đồ thị thành đồ thị kia bằng cách đổi tên các đỉnh.

Các khái niệm khác:
- Bậc của một đỉnh (degree of a vertex): Số cạnh nối với đỉnh đó.
- Bậc vào và bậc ra của một đỉnh trong đồ thị có hướng.
- Đường đi (path): Dãy các đỉnh mà mỗi cặp đỉnh liên tiếp đều được nối với nhau.
- Chu trình (cycle): Đường đi mà đỉnh đầu tiên và cuối cùng trùng nhau.
- Đường đi Euler: Đường đi đi qua mỗi cạnh đúng một lần.
- Chu trình Euler: Chu trình đi qua mỗi cạnh đúng một lần.
- Đường đi Hamilton: Đường đi đi qua mỗi đỉnh đúng một lần.
- Chu trình Hamilton: Chu trình đi qua mỗi đỉnh đúng một lần.
- Đồ thị liên thông mạnh (strongly connected graph): Đồ thị có hướng mà mọi cặp đỉnh $(u, v)$ đều có đường đi từ $u$ đến $v$ và từ $v$ đến $u$.
- Đồ thị liên thông yếu (weakly connected graph): Đồ thị có hướng mà nếu bỏ hướng của các cạnh thì đồ thị trở thành đồ thị liên thông.
- Đồ thị có trọng số (weighted graph): Mỗi cạnh được gán một trọng số.
- Đồ thị có hướng có trọng số (directed weighted graph): Đồ thị có hướng với mỗi cạnh được gán một trọng số.
- Đồ thị đường: chuyển đổi cạnh của đồ thị gốc thành đỉnh trong đồ thị mới. Cạnh $(x, y)$ trên đồ thị mới nếu tồn tại đỉnh $z$ sao cho $(x, z)$ và $(z, y)$ là cạnh trên đồ thị gốc.

## 2. Biểu diễn đồ thị
- Ma trận kề (adjacency matrix): Ma trận $A$ với $A_{ij} = 1$ nếu có cạnh nối giữa đỉnh $i$ và đỉnh $j$, ngược lại $A_{ij} = 0$.
- Danh sách cạnh (edge list): Sử dụng một mảng gồm $M$ cặp $(u, v)$ biểu diễn cạnh nối giữa đỉnh $u$ và đỉnh $v$.
- Danh sách kề (adjacency list): Sử dụng một mảng gồm $N$ danh sách liên kết, mỗi danh sách liên kết chứa các đỉnh kề với một đỉnh.
- Danh sách liên thuộc (incidence lists): Sử dụng $head[u]$ để lưu con trỏ đầu tiên của danh sách liên thuộc của đỉnh $u$, $link[i]$ là chỉ số cung kế tiếp cung $e[i]$ trong danh sách liên thuộc của đỉnh $u$, trong đó $e[i]$ là cung thứ $i$ của đồ thị. Trong trường hợp $e[i]$ là cung cuối cùng của đỉnh $u$, ta có $link[i] = -1$.

## 3. Các thuật toán tìm kiếm trên đồ thị
### 3.1. Duyệt theo chiều sâu (DFS - Depth First Search)
- Duyệt theo chiều sâu từ một đỉnh $u$:
    - Đánh dấu đỉnh $u$ đã được duyệt.
    - Duyệt qua tất cả các đỉnh kề $v$ chưa được duyệt, đánh dấu chúng và gọi đệ quy DFS($v$).

- Độ phức tạp: $O(N + M)$ với $N$ là số đỉnh và $M$ là số cạnh của đồ thị.
- Ứng dụng: Tìm đường đi trên đồ thị, kiểm tra chu trình trên đồ thị, kiểm tra tính liên thông của đồ thị.

- Một vài tính chất của DFS
    - Cây DFS
    - Thứ tự duyệt các đỉnh trong DFS (duyệt đến và duyệt xong)

### 3.2. Duyệt theo chiều rộng (BFS - Breadth First Search)
- Duyệt theo chiều rộng từ một đỉnh $u$:
    - Khởi tạo hàng đợi $Q$ rỗng, đánh dấu đỉnh $u$ đã được duyệt.
    - Thêm $u$ vào $Q$.
    - Lặp cho đến khi $Q$ rỗng:
        - Lấy đỉnh $v$ đầu tiên ra khỏi $Q$.
        - Duyệt qua tất cả các đỉnh kề $v$ chưa được duyệt, đánh dấu chúng và thêm vào $Q$.

- Độ phức tạp: $O(N + M)$ với $N$ là số đỉnh và $M$ là số cạnh của đồ thị.
- Ứng dụng: Tìm đường đi ngắn nhất trên đồ thị không có trọng số, kiểm tra tính liên thông của đồ thị, kiểm tra chu trình trên đồ thị.
- Một vài tính chất của BFS
    - Cây BFS
    - Thứ tự duyệt các đỉnh trong BFS (duyệt đến và duyệt xong)

## 4. Tính liên thông của đồ thị
- Đồ thị vô hướng $G = (V, E)$ được gọi là liên thông nếu có đường đi giữa mọi cặp đỉnh $(u, v) \in V$ (connected graph).
- Đồ thị vô hướng $G = (V, E)$, $U \subseteq V$ được gọi là một thành phần liên thông (connected component) nếu có đường đi từ mọi đỉnh $u \in U$ đến mọi đỉnh $v \in U$.
    - Bài toán tìm khớp nối (articulation points) và cầu (bridges) trên đồ thị vô hướng.
- Đồ thị có hướng $G = (V, E)$ được gọi là liên thông mạnh (strongly connected) nếu có đường đi từ mọi đỉnh $u$ đến mọi đỉnh $v$ và từ mọi đỉnh $v$ đến mọi đỉnh $u$. Đồ thị có hướng $G$ được gọi là liên thông yếu (weakly connected) nếu bỏ hướng của các cạnh thì đồ thị trở thành đồ thị liên thông.
    - Bài toán tìm thành phần liên thông mạnh (strongly connected components) trên đồ thị có hướng sử dụng thuật toán Kosaraju và Tarjan (các tập con của đồ thị mà mỗi cặp đỉnh trong tập con đều có đường đi giữa chúng).
### 4.1. Bao đóng của đồ thị vô hướng
- Đồ thị đầy đủ $K_N$ là đồ thị vô hướng có $N$ đỉnh và mọi cặp đỉnh đều được nối với nhau.
- Bao đóng của một đồ thị vô hướng $G = (V, E)$ là đồ thị vô hướng $G' = (V, E')$ trong đó cạnh $(u, v)$ thuộc $E'$ nếu có đường đi giữa $u$ và $v$ trên $G$.
    - Sử dụng thuật toán Warshall để tìm bao đóng của đồ thị vô hướng. Độ phức tạp: $O(N^3)$.

### 4.2. Bài toán xác định các thành phần liên thông mạnh
- Sử dụng DFS để duyệt đồ thị theo chiều sâu, ngoài những cung nằm trên cây DFS, những cung còn lại chia làm 3 loại: cung ngược, cung xuôi và cung chéo (quay lui).
- Thuật toán Tarjan: Sử dụng DFS để duyệt đồ thị, duyệt qua tất cả các đỉnh và cung, gán thời gian thăm và thời gian hoàn thành cho mỗi đỉnh, sử dụng stack để lưu trữ các đỉnh đã duyệt, xác định thành phần liên thông mạnh của đồ thị.
    - Độ phức tạp: $O(N + M)$ với $N$ là số đỉnh và $M$ là số cạnh của đồ thị.'
- Thuật toán Kosaraju-Sharir: Sử dụng DFS để duyệt đồ thị và đồ thị đảo, xác định thành phần liên thông mạnh của đồ thị.
    - Độ phức tạp: $O(N + M)$ với $N$ là số đỉnh và $M$ là số cạnh của đồ thị.

## 5. Sắp xếp topological
- Đồ thị có hướng $G = (V, E)$ được gọi là đồ thị acyclic nếu không chứa chu trình.'
- Sắp xếp topological của một đồ thị acyclic là một cách sắp xếp các đỉnh sao cho mọi cạnh nối từ đỉnh $u$ đến đỉnh $v$ thì $u$ đứng trước $v$.
- Sắp xếp topological của một đồ thị acyclic có thể được tìm bằng cách sử dụng thuật toán DFS hoặc thuật toán Kahn.
    - Thuật toán DFS: Duyệt đồ thị theo chiều sâu, sau khi duyệt xong một đỉnh thì thêm đỉnh đó vào đầu danh sách kết quả.
    - Thuật toán Kahn: Tìm tất cả các đỉnh không có cạnh vào, sau đó xóa đỉnh đó khỏi đồ thị và lặp lại quá trình cho đến khi không còn đỉnh nào.
    - Độ phức tạp: $O(N + M)$ với $N$ là số đỉnh và $M$ là số cạnh của đồ thị.
## 6. Ứng dụng của BFS và DFS

### 6.1. Xây dựng cây khung của đồ thị
- Cây khung của đồ thị $G = (V, E)$ là một đồ thị con của $G$ chứa tất cả các đỉnh của $G$ và là một cây.

- Cây khung nhỏ nhất (minimum spanning tree - MST) của đồ thị vô hướng có trọng số là cây khung có tổng trọng số nhỏ nhất.
    - Sử dụng thuật toán Prim hoặc thuật toán Kruskal để tìm cây khung nhỏ nhất.
    - Độ phức tạp: $O(M \log N)$ với $N$ là số đỉnh và $M$ là số cạnh của đồ thị.

### 6.2. Tập các chu trình cơ sở của đồ thị
- Xét đồ thị vô hướng liên thông $G = (V, E)$, gọi $T = (V, E_T)$ là một cây khung của $G$. Nếu thêm một cạnh $(u, v)$ vào $T$ thì sẽ tạo thành một chu trình. Các chu trình này được gọi là chu trình cơ sở (fundamental cycle) của cạnh $(u, v)$.

### 6.3. Bài toán định chiều đồ thị
- Đồ thị vô hướng $G = (V, E)$ có thể được định chiều bằng cách thêm hướng cho mỗi cạnh của đồ thị để được một đồ thị có hướng liên thông mạnh.

### 6.4. Liệt kê khớp và cầu của đồ thị
- Khớp (articulation points) là đỉnh mà nếu xóa nó ra khỏi đồ thị thì số thành phần liên thông của đồ thị tăng lên.
- Cầu (bridges) là cạnh mà nếu xóa nó ra khỏi đồ thị thì số thành phần liên thông của đồ thị tăng lên.

- Sử dụng thuật toán Tarjan để liệt kê khớp và cầu của đồ thị vô hướng.
    - Độ phức tạp: $O(N + M)$ với $N$ là số đỉnh và $M$ là số cạnh của đồ thị.
    - Chi tiết: Duyệt đồ thị bằng DFS, gán thời gian thăm và thời gian hoàn thành cho mỗi đỉnh, xác định thời gian thăm sớm nhất của mỗi đỉnh có thể đến được, xác định thời gian thăm sớm nhất của mỗi đỉnh có thể đến được qua một cạnh ngược, xác định khớp và cầu của đồ thị.

### 6.5. Các thành phần song liên thông
- Đồ thị vô hướng $G = (V, E)$ được gọi là đồ thị song liên thông (biconnected graph) nếu không chứa khớp và mọi cặp đỉnh đều có ít nhất hai đường đi đến nhau.

## 7. Đồ thị Euler và Hamilton
### 7.1. Đồ thị Euler
- Tìm chu trình Euler trên đồ thị vô hướng $G = (V, E)$ là tìm một chu trình đi qua mỗi cạnh đúng một lần.

- Đồ thị Euler tồn tại nếu và chỉ nếu đồ thị liên thông và mọi đỉnh của đồ thị có bậc chẵn.

- Sử dụng thuật toán Fleury để tìm chu trình Euler trên đồ thị vô hướng.
    - Độ phức tạp: $O(M)$ với $M$ là số cạnh của đồ thị.
    - Chi tiết: Chọn một đỉnh bất kỳ làm đỉnh xuất phát, duyệt qua tất cả các cạnh của đồ thị, chọn cạnh không phải cầu nếu có, nếu không chọn cầu.
    - Lưu ý: Đồ thị có thể chứa nhiều chu trình Euler.

### 7.2. Đồ thị Hamilton
- Tìm chu trình Hamilton trên đồ thị $G = (V, E)$ là tìm một chu trình đi qua mỗi đỉnh đúng một lần.

- Đồ thị Hamilton tồn tại nếu và chỉ nếu đồ thị liên thông và bậc của mọi đỉnh lớn hơn hoặc bằng $N/2$.

- Sử dụng thuật toán Held-Karp để tìm chu trình Hamilton trên đồ thị đầy đủ có trọng số.
    - Độ phức tạp: $O(2^N \times N^2)$ với $N$ là số đỉnh của đồ thị.

Hai bài toán nổi tiếng liên quan:
- Bài toán người du lịch (Travelling Salesman Problem - TSP): Tìm chu trình Hamilton ngắn nhất trên đồ thị đầy đủ có trọng số.
- Bài toán người đưa thư (Chinese Postman Problem): Tìm chu trình Euler ngắn nhất trên đồ thị có hướng.

## 8. Các thuật toán tìm đường đi ngắn nhất
### 8.1. Đường đi ngắn nhất xuất phát từ một đỉnh
- Thuật toán Dijkstra
- Thuật toán Bellman-Ford

### 8.2. Đường đi ngắn nhất giữa mọi cặp đỉnh
- Thuật toán Floyd-Warshall
- Thuật toán Johnson

## 8.3. Cây khung nhỏ nhất
- Thuật toán Prim
- Thuật toán Kruskal

## 9. Luồng cực đại trên mạng
- Thuật toán Ford-Fulkerson
- Thuật toán Edmonds-Karp
- Thuật toán Dinic
- Thuật toán Push-Relabel (FIFO Preflow-Push)

### 9.1. Mạng với nhiều nguồn và nhiều đích
- Sử dụng phương pháp chuyển đổi mạng nhiều nguồn và nhiều đích thành mạng một nguồn và một đích.

### 9.2. Mạng với sức chứa trên cả các đỉnh và các cung
- Sử dụng phương pháp chuyển đổi mạng với sức chứa trên cả các đỉnh và các cung thành mạng với sức chứa chỉ trên các cung.

### 9.3. Mạng với ràng buộc luồng dương bị chặn 2 phía
- Luồng dương trên mỗi cung $e$ không vượt quá $c_e$ và không nhỏ hơn $l_e$.

### 9.4. Mạng với sức chứa âm


### 9.5. Lát cắt cực tiểu
Loại bỏ một số cạnh để đồ thị mất tính liên thông, cần tìm phương án sao cho tổng trọng số của các cạnh bị loại bỏ là nhỏ nhất.

- Thuật toán Min-Cost Max-Flow

## 10. Bộ ghép cực đại trên đồ thị hai phía
- Thuật toán Hopcroft-Karp
- Thuật toán Hungarian
- Thuật toán Blossom


# V. Các kiểu dữu liệu trừu tượng và cấu trúc dữ liệu
## 1. List
- Danh sách liên kết đơn
- Danh sách liên kết kép
- Danh sách liên kết vòng
- Danh sách liên kết vòng kép

## 2. Stack

Ngăn xếp (stack) là một cấu trúc dữ liệu dạng LIFO (Last In First Out), tức là phần tử cuối cùng được thêm vào ngăn xếp sẽ là phần tử đầu tiên được lấy ra khỏi ngăn xếp.


## 3. Queue

Hàng đợi (queue) là một cấu trúc dữ liệu dạng FIFO (First In First Out), tức là phần tử đầu tiên được thêm vào hàng đợi sẽ là phần tử đầu tiên được lấy ra khỏi hàng đợi.

## 4. Tree
### 4.1. Các khoái niệm cơ bản
- Cây là một cấu trúc dữ liệu phân cấp, bao gồm một nút gốc và các nút con của nó.
- Một nút có thể có nhiều nút con, được gọi là nút cha của các nút con đó.
- Một nút không có nút con được gọi là nút lá.
- Ancestor và descendant: Nút $u$ là tổ tiên của nút $v$ nếu có đường đi từ $u$ đến $v$.
- Height của một nút là độ sâu của nút đó trong cây.
- Height của cây là chiều cao của nút gốc.
- Forest là một tập hợp các cây.
- Siblings: Hai nút cùng một nút cha.

### 4.2. Các loại cây
- Cây nhị phân: Mỗi nút có tối đa hai nút con.
- Cây nhị phân đầy đủ: Mỗi nút có đúng hai nút con hoặc không có nút con nào.
- Cây $k$-ary: Mỗi nút có tối đa $k$ nút con (cây k phân).

### 4.3. Phép duyệt cây
- Duyệt theo thứ tự trước (pre-order traversal): Duyệt nút gốc trước, sau đó duyệt nút con trái và nút con phải.
- Duyệt theo thứ tự giữa (in-order traversal): Duyệt nút con trái trước, sau đó duyệt nút gốc và cuối cùng là duyệt nút con phải.
- Duyệt theo thứ tự sau (post-order traversal): Duyệt nút con trái trước, sau đó duyệt nút con phải và cuối cùng là duyệt nút gốc.

## 5. Ký pháp tiền tố, trung tố và hậu tố
- Công thức tiền tố: Toán tử đứng trước hai toán hạng.
- Công thức trung tố: Toán tử đứng giữa hai toán hạng.
- Công thức hậu tố: Toán tử đứng sau hai toán hạng.

### 5.1. Chuyển đổi giữa các ký pháp
- Chuyển đổi từ trung tố sang hậu tố: Sử dụng stack để lưu trữ toán tử, duyệt qua từng phần tử trong biểu thức trung tố, nếu gặp toán hạng thì thêm vào biểu thức hậu tố, nếu gặp toán tử thì thêm vào stack, nếu gặp dấu ngoặc mở thì thêm vào stack, nếu gặp dấu ngoặc đóng thì lấy toán tử từ stack cho đến khi gặp dấu ngoặc mở.
- Xây dựng cây nhị phân từ biểu thức hậu tố: Sử dụng stack để lưu trữ cây nhị phân, duyệt qua từng phần tử trong biểu thức hậu tố, nếu gặp toán hạng thì thêm vào stack, nếu gặp toán tử thì tạo một cây nhị phân với toán tử là nút gốc, lấy hai nút con từ stack và thêm vào cây nhị phân.

## 6. Cây nhị phân tìm kiếm
### 6.1. Các thao tác cơ bản
- Tìm kiếm: Tìm kiếm một phần tử trong cây nhị phân tìm kiếm.
- Thêm: Thêm một phần tử vào cây nhị phân tìm kiếm.
- Xóa: Xóa một phần tử khỏi cây nhị phân tìm kiếm.
- Duyệt: Duyệt cây nhị phân tìm kiếm theo thứ tự trước, giữa và sau.
- Tìm phần tử lớn nhất và nhỏ nhất trong cây nhị phân tìm kiếm.
### 6.2. Cây nhị phân tìm kiếm tự cân bằng
- Cây AVL
- Cây đỏ đen
- Cây Splay

## 7. Cây nhị phân tìm kiếm ngẫu nhiên
- Cây Treap

## 8. Một số ứng dụng của cây nhị phân tìm kiếm
- Cho một danh sách $L$ để chứa các số nguyên với một trong 2 loại thao tác. Nhiệm vụ của bạn là in ra danh sách $L$ sau $Q$ thao tác.
    - Thêm một số nguyên $x$ vào danh sách $L$ tại vị trí $k$.
    - Xóa số nguyên tại vị trí $k$ khỏi danh sách $L$. 
- Bài toán hoán vị Josephus: Cho $N$ người đánh số từ $1$ đến $N$ đứng thành vòng tròn. Bắt đầu từ người thứ $1$, mỗi người sẽ bị loại khỏi vòng tròn theo chiều kim đồng hồ sau $M$ lượt. Hỏi người cuối cùng còn lại là người thứ mấy?
    - Ví dụ: Với $N = 7$ và $M = 3$, kết quả là $4$, hoán vị Josephus là $3, 6, 2, 7, 5, 1, 4$.
    - Tìm người cuối cùng còn lại trong hoán vị Josephus sử dụng quy hoạch động: $f(N) = (f(N - 1) - 1 + M) \mod N + 1$ với $N > 1$ và $f(1) = 1$.
- Thứ tự thống kê tự động
- Interval Tree
- Điểm giao nhiều nhất

# VI. Hình học tính toán
## 1. Các khái niệm cơ bản
- Hệ tọa độ Descartes: Hệ tọa độ 2D với trục $x$ và trục $y$.
- Tọa độ: Một điểm trong hệ tọa độ Descartes được biểu diễn bởi cặp số thực $(x, y)$.
- Khoảng cách giữa hai điểm: $\sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}$.
- Góc giữa hai điểm: $\arctan\left(\frac{y_2 - y_1}{x_2 - x_1}\right)$.
- Góc giữa hai vector: $\arccos\left(\frac{u \cdot v}{\|u\| \cdot \|v\|}\right)$.

## 2. Các phép biến đổi tọa độ cơ bản
- Phép quay: Quay một điểm $(x, y)$ quanh gốc tọa độ một góc $\theta$ theo chiều kim đồng hồ từ $(x, y)$ sang $(x \cos \theta - y \sin \theta, x \sin \theta + y \cos \theta)$.
- Tịnh tiến: Dịch chuyển một điểm từ $(x, y)$ sang $(x + a, y + b)$.
- Phép quay quanh một điểm: Quay một điểm $(x, y)$ quanh một điểm $(a, b)$ một góc $\theta$ theo chiều kim đồng hồ từ $(x, y)$ sang $(a + (x - a) \cos \theta - (y - b) \sin \theta, b + (x - a) \sin \theta + (y - b) \cos \theta)$.
- Phép vị tự

## 3. Một số khái niệm khác
- Tích chấm (dot product): $u \cdot v = u_x v_x + u_y v_y$.
- Tích vector (cross product): $u \times v = u_x v_y - u_y v_x$.
- Đường thẳng: $Ax + By + C = 0$.
- Đa giác: đường gấp khúc không tự cắt. Diện tích của đa giác: $\frac{1}{2} \sum_{i = 1}^{n} (x_i y_{i + 1} - x_{i + 1} y_i)$.
- Đường tròn: $(x - a)^2 + (y - b)^2 = r^2$.
## 4. Một số bài toán hình học cơ bản
- Biểu diễn tuyến tính cho 3 vector $a, b, c$, tìm 2 số thực $p, q$ sao cho $c = pa + qb$.
- Tìm giao điểm của hai đường thẳng $A_1x + B_1y + C_1 = 0$ và $A_2x + B_2y + C_2 = 0$.
- Tìm giao điểm của 2 đoạn thẳng $AB$ và $CD$, với $A(x_1, y_1)$, $B(x_2, y_2)$, $C(x_3, y_3)$, $D(x_4, y_4)$.
- Tìm giao điểm giữa một đoạn thẳng $AB$ và tia $CD$.
- Góc giữa 2 vector $u$ và $v$, $-pi < \theta \leq \pi$, $\theta = \arccos\left(\frac{u \cdot v}{\|u\| \cdot \|v\|}\right)$.
- Tính diện tích của tam giác $ABC$ với $A(x_1, y_1)$, $B(x_2, y_2)$, $C(x_3, y_3)$; $S = \frac{1}{2} \left|(x_1 - x_3)(y_2 - y_1) - (x_1 - x_2)(y_3 - y_1)\right|$.
- Tính diện tích của đa giác lồi $P$ với $n$ đỉnh $A_1, A_2, \dots, A_n$; $S = \frac{1}{2} \sum_{i = 1}^{n} (x_i y_{i + 1} - x_{i + 1} y_i)$.
- Diện tích đường cong $y = f(x)$ giữa $x = a$ và $x = b$; $S = \int_{a}^{b} f(x) dx$.

## 5. Một số bài toán thông dụng khác
- Tam giác với 3 điểm $A (A.x, A.y)$, $B (B.x, B.y)$, $C (C.x, C.y)$; trong đó $a, b, c$ là độ dài 3 cạnh, $p$ là nửa chu vi, $S$ là diện tích.
    - Đường tròn ngoại tiếp tam giác
    - Đường phân giác
    - Đường tròn nội tiếp tam giác
- Kiểm tra điểm nằm trong đa giác lồi sử dụng thuật toán Ray Casting, Winding Number.
- Tìm 2 điểm gần nhau nhất trong tập hợp các điểm sử dụng thuật toán Closest Pair of Points.

## 6. Các hàm cơ bản trong thư viện hình học tính toán
- Hàm kiểm soát sai số `is_equal`, so sánh hai số thực, $abs(a - b) < \epsilon$.
- Hàm kiểm tra 2 điểm trùng nhau $a, b$ `is_same_point`
- Khoảng cách 2 điểm $a, b$ `distance`, $\sqrt{(a.x - b.x)^2 + (a.y - b.y)^2}$.
- Tổng vector $a, b$ `add`, $(a.x + b.x, a.y + b.y)$.
- Tích vô hướng 2 vector $a, b$ `dot`, $a.x \cdot b.x + a.y \cdot b.y$.
- Góc với trục Ox, đo bằng radian, $-\pi < \theta \leq \pi$ `angle`, $\arctan\left(\frac{a.y}{a.x}\right)$.
- Tọa độ Đề-Các sang tọa độ cực `to_polar`, $(\sqrt{a.x^2 + a.y^2}, \arctan\left(\frac{a.y}{a.x}\right))$.
- Tọa độ cực sang tọa độ Đề-Các `to_cartesian`, $(a.x \cdot \cos(a.y), a.x \cdot \sin(a.y))$.
- Phương trình đường thẳng qua 2 điểm $a, b$ `line`, $(a.y - b.y, b.x - a.x, a.x \cdot b.y - a.y \cdot b.x)$.
- Giao điểm 2 đường thẳng `intersection`, $((l1.y \cdot l2.z - l1.z \cdot l2.y) / (l1.x \cdot l2.y - l1.y \cdot l2.x), (l1.z \cdot l2.x - l1.x \cdot l2.z) / (l1.x \cdot l2.y - l1.y \cdot l2.x))$.
- Khoảng cách từ điểm $a$ đến đường thẳng $l$ `distance_point_to_line`, $\frac{|l.x \cdot a.x + l.y \cdot a.y + l.z|}{\sqrt{l.x^2 + l.y^2}}$.
- Kiểm tra đoạn thẳng cắt nhau `is_intersected`
- Đường thẳng vuông góc với đường thẳng `perpendicular_line`, $(l.y, -l.x, l.x \cdot a.y - l.y \cdot a.x)$.
- Bán kinh đường tròn nội tiếp tam giác `in_circle_radius`, $\frac{2 \cdot S}{a + b + c}$.
- Bán kinh đường tròn ngoại tiếp tam giác `circum_circle_radius`, $\frac{a \cdot b \cdot c}{4 \cdot S}$.
- Tâm đường tròn nội tiếp tam giác `in_circle_center`, $(\frac{a \cdot A.x + b \cdot B.x + c \cdot C.x}{a + b + c}, \frac{a \cdot A.y + b \cdot B.y + c \cdot C.y}{a + b + c})$.
- Thư viện `Math` trong C++: `abs`, `sqrt`, `acos`, `atan`, `atan2`, `cos`, `sin`, `tan`, `pow`, `log`, `exp`, `ceil`, `floor`, `round`, `min`, `max`.
- Check `inf` và `nan` trong C++: `isinf`, `isnan`. Check `zero`: `abs(x) < eps`.

# VII. Lý thuyết trò chơi
## 1. Các khái niệm cơ bản
Vị trí: Trạng thái của trò chơi tại một thời điểm nào đó.

Luật chơi: Quy tắc để thực hiện một bước chơi từ một vị trí cho trước.

Trò chơi đối kháng: Trò chơi giữa hai người chơi, mỗi người chơi cố gắng tối ưu hóa lợi ích của mình, chia ra làm 2 loại: trò chơi có thông tin hoàn toàn và trò chơi có thông tin không hoàn toàn.

- Trò chơi Nim: Một trò chơi với $n$ đống sỏi, mỗi lượt mỗi người chơi được phép lấy một số sỏi từ một đống bất kỳ, người chơi cuối cùng lấy sỏi là người thắng cuộc.
- Trò chơi Grundy: Một trò chơi với $n$ trạng thái, mỗi lượt mỗi người chơi được phép chuyển từ trạng thái hiện tại sang một trạng thái khác, người chơi cuối cùng không thể chuyển nữa là người thắng cuộc.
- Trò chơi Wythoff: Một trò chơi với hai đống sỏi, mỗi lượt mỗi người chơi được phép lấy một số sỏi từ một đống bất kỳ hoặc lấy cùng một số sỏi từ hai đống, người chơi cuối cùng lấy sỏi là người thắng cuộc.
- Trò chơi Sprague-Grundy: Một trò chơi với $n$ trạng thái, mỗi lượt mỗi người chơi được phép chuyển từ trạng thái hiện tại sang một trạng thái khác, người chơi cuối cùng không thể chuyển nữa là người thắng cuộc.
- Trò chơi Hackenbush: Một trò chơi với một đồ thị vô hướng, mỗi lượt mỗi người chơi được phép xóa một cạnh, người chơi cuối cùng không thể xóa nữa là người thắng cuộc.
- Trò chơi Chomp: Một trò chơi với một bảng hình chữ nhật, mỗi lượt mỗi người chơi được phép ăn một phần hình chữ nhật, người chơi cuối cùng ăn phần hình chữ nhật ở góc trên cùng bên trái là người thắng cuộc.
- Trò chơi Kayles: Một trò chơi với một dãy sỏi, mỗi lượt mỗi người chơi được phép xóa một số sỏi liên tiếp, người chơi cuối cùng không thể xóa nữa là người thắng cuộc.

## 2. Trò tổ hợp cân bằng
- Trò chơi làm rỗng và phân chia
- Trò chơi lấy bớt quân cờ
- Trò chơi trừ dần
- Tổng Nim và trò chơi Nim
- Trò chơi trên đồ thị
- Các trò chơi lật xu

## 3. Trò chơi hai người có tổng điểm bằng 0


