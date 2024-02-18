#include "iostream"
#include <vector>

// 1...n 全排列, 从小到大, 第 k 个
/*
 1, 2, 3, 4

 1, 2, 4, 3
 4! 3! 2! 1!
      k - 2!
 3! < k < 2!
 1, 3/4, ? ?
    2 + (k - 2!) / (2!)

6 2 1

1 2 3 - 1
1 3 2 - 2
2 1 3 - 3,
2 3 1
3 1 2
3 2 1
 * */

void display(const std::vector<int> &result) {
    for (auto &i: result) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void solve(std::vector<int> &result, int n, int k) {
    // [1, 2, 3]
    result.resize(n+1);
    // [6, 2, 1]
    std::vector<int> m(n+1, 0);
    m[n] = 1;
    result[n] = n;
    for (int j = n - 1; j >= 0;j--) {
        m[j] = (n-j+1) * m[j+1];
        result[j] = j;
    }

//    display(m);
//    display(result);

    for (int i = 1; i < n; ++i) {
        if (k >= m[i+1]) {
            /*
             * 1, 2, 3
             * 6, 2, 1
             * 3
             * 2 1 3, 1
             *
             *
             * 1, 2, 3
             *
             * 5, 5 / 2 = 2
             * 3, 1, 2
             *
             * 5
             * 3 1 2
             * k=1, m[i+1]=1
             * 1/1 = 1
             * 3, 2, 1
             * k=0, i=n
             * */
            int p = (k - 1) / m[i+1]; // 和后面的第 p 个交换
//            std::cout << "K " << k << " - " <<  m[i+1] << " - " << p << " - " << i << std::endl;
            std::swap(result[i], result[i+p]);
            // 对后面的进行排序
            std::sort(result.begin() + i + 1, result.end());
            k %= m[i+1];
        }
    }
    result = std::vector<int>(result.begin() + 1, result.end());
}



int main() {
    std::vector<int> result;
    solve(result, 3, 2);
    display(result);
    return 0;
}