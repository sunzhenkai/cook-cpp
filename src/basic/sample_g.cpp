#include "iostream"
#include <vector>
#include "unordered_map"

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

template<typename T>
void display(const std::vector<T> &result) {
    for (auto &i: result) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void display_ln(const std::vector<T> &result) {
    for (auto &i: result) {
        std::cout << i << std::endl;
    }
    //    std::cout << std::endl;
}

void solve(std::vector<int> &result, int n, int k) {
    // [1, 2, 3]
    result.resize(n + 1);
    // [6, 2, 1]
    std::vector<int> m(n + 1, 0);
    m[n] = 1;
    result[n] = n;
    for (int j = n - 1; j >= 0; j--) {
        m[j] = (n - j + 1) * m[j + 1];
        result[j] = j;
    }

    //    display(m);
    //    display(result);

    for (int i = 1; i < n; ++i) {
        if (k >= m[i + 1]) {
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
            int p = (k - 1) / m[i + 1]; // 和后面的第 p 个交换
            //            std::cout << "K " << k << " - " <<  m[i+1] << " - " << p << " - " << i << std::endl;
            std::swap(result[i], result[i + p]);
            // 对后面的进行排序
            std::sort(result.begin() + i + 1, result.end());
            k %= m[i + 1];
        }
    }
    result = std::vector<int>(result.begin() + 1, result.end());
}


void StringSplit(const std::string &in, const char &c, std::vector<std::string_view> &ret) {
    ret.clear();
    for (size_t i = 0, j = 0; j <= in.size(); i = ++j) {
        while (j < in.size() && in[j] != c)
            ++j;
        ret.emplace_back(std::string_view(in.data() + i, j - i));
    }
}

void fb(std::string s) {
    std::vector<std::string_view> svs;
    StringSplit(s, '#', svs);
    display(svs);
    std::cout << "----" << std::endl;
}

void st() {
    std::vector<int> v1;
    v1 = {1, 3, 2, 4, 6, 5};
    std::sort(v1.begin(), v1.end());
    display(v1);

    v1 = {1, 3, 2, 4, 6, 5};
    std::sort(v1.begin(), v1.end(), std::greater<>());
    display(v1);

    v1 = {1, 3, 2, 4, 6, 5};
    std::sort(v1.begin(), v1.end(), [](int &a, int &b) { return a > b; });
    display(v1);
}

void fc() {
    std::string s = "你好Hi";
    std::string ni = "你";
    std::cout << ni.size() << " - " << s.size() << std::endl; // 8

    std::wstring ws = L"你好Hi";
    std::wstring wni = L"你";
    std::cout << wni.size() << " - " << ws.size() << std::endl; // 8
}

void fd() {
    std::vector<std::string> vs{"1", "2", "3"};
    std::unordered_map<std::string, std::string> m;
    for (auto &v: vs) {
        m.emplace(v, v);
    }

    for (auto &[k, v]: m) {
        std::cout << k << " - " << v << std::endl;
    }
}

void fe() {
    std::vector<std::string> vecs{"A", "", "B", "", "C", "D"};
    // vecs.erase(std::remove(vecs.begin(), vecs.end(), ""), vecs.end());

    auto it = std::remove(vecs.begin(), vecs.end(), "");
    for (; it != vecs.end(); ++it) {
        std::cout << "> " << *it << std::endl;
    }
}

int main() {
    fe();

    //    fc();
    //    fb("1#1.1#2.1");
    //    fb("");
    //    fb("1");
    //    fb("1#");
    //    std::vector<int> result;
    //    solve(result, 3, 2);
    //    display(result);
    return 0;
}