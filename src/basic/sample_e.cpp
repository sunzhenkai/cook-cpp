#include "iostream"
#include <fstream>
#include "thread"
#include "chrono"
#include "thread"
#include "chrono"
#include "unordered_set"
#include "unordered_map"
#include "vector"
#include "utils/utils.h"
#include "memory"
#include "shared_mutex"
#include "mutex"
#include "functional"
#include "unordered_set"
#include "queue"

template<typename T>
void Unique(std::vector<T> &data) {
    std::unordered_set<T> store;
    for (auto &item: data) {
        store.emplace(std::forward<T>(item));
    }

    size_t idx = 0ul;
    for (auto it = store.begin(); it != store.end(); ++it) {
        data[idx++] = std::forward<T>(std::remove_const_t<T>(*it));
    }
    data.resize(idx);
}

template<typename T, typename V>
void ZipUnique(std::vector<T> &data, std::vector<V> &value) {
    if (data.size() <= 1) return;
    std::unordered_map<T, V> store;
    for (size_t i = 0ul; i < data.size(); ++i) {
        store[data[i]] = std::forward<V>(value[i]);
    }

    size_t idx = 0ul;
    for (auto it = store.begin(); it != store.end(); ++it, ++idx) {
        data[idx] = it->first;
        value[idx] = std::forward<V>(it->second);
    }
    data.resize(idx);
    value.resize(idx);
}

template<typename K, typename V>
class SimpleSafeMap {
private:
    std::unordered_map<K, V> m;
    std::shared_mutex mtx;

public:
    void Insert(const K &key, const V &value) {
        std::unique_lock lock(mtx);
        //        m[key] = value;
        m.insert({key, value});
    }

    void Insert(const K &key, const std::function<V(const K &key)> &generator) {
        std::unique_lock lock(mtx);
        m[key] = generator(key);
        //            m.insert({key, generator(key)});
    }

    typename std::unordered_map<K, V>::iterator Find(const K &key) {
        std::shared_lock lock(mtx);
        return m.find(key);
    }

    void Erase(const K &key) {
        std::unique_lock lock(mtx);
        m.erase(key);
    }

    typename std::unordered_map<K, V>::iterator End() {
        return m.end();
    }

    typename std::unordered_map<K, V>::iterator Begin() {
        return m.begin();
    }

    typename std::unordered_map<K, V>::const_iterator CEnd() const {
        return m.end();
    }

    typename std::unordered_map<K, V>::const_iterator CBegin() const {
        return m.begin();
    }

    size_t Size() const {
        return m.size();
    }

    template<typename F>
    void SafetyRun(F &func, bool unique = false) {
        if (unique) {
            std::unique_lock lock(mtx);
            func(this);
        } else {
            std::shared_lock lock(mtx);
            func(this);
        }
    }
};

struct TestA {
    int i = 0;
};

/*
 * 1. 读一个文本文件
 * 2. 逐行
 *
 * 功能: 把一个文件数据发送到远端
 * */

//class RpcClient {
//public:
//    // 创建一个链接到 remote_ip RPC client
//    explicit RpcClient(const std::string &remote_ip);
//    // 发送多行文本到远端
//    void Send(const std::vector<std::string> &datas);
//};
//

/*
 *
 *
 * 1. 多线程，定义 size
 * 2. 创建一个读文件的句柄，临界资源需要考虑线程安全问题, 或者一个线程读
 *         2.1 一个线程读更优, 考虑内存大小的问题
 *         2.2 无锁队列
 * 3. 支持设置 batch_size
 * */

//class FileSender {
//public:
//    FileSender(const std::string &file_name,
//               const std::string &remote_addr,
//               int batch_size,
//               int thread_num) :
//               batch_size(batch_size),
//               file_name(file_name),
//               remote_addr(remote_addr),
//               infile(file_name),
//               client(remote_addr){
//        read_thread = std::thread(&FileSender::ReadFile, this);
//        for (int i = 0; i < thread_num; ++i) {
//            sender_threads.emplace_back(&FileSender::SendData, this);
//        }
//    }
//
//    static void ReadFile(void *arg) {
//        auto that = (FileSender*)arg;
//        std::vector<std::string> data;
//        data.reserve(that->batch_size);
//
//        // block (固定的 size)
//
//        while (!that->is_done) {
//            for (int i = 0; i < that->batch_size; ++i) {
//                std::string line;
//                auto result = that->infile.read_line(line);
//                if (!result) {
//                    that->is_done = true;
//                    break;
//                }
//                data.emplace_back(std::move(line));
//            }
//            {
//                std::unique_lock lock(that->data_queue_mtx);
//                that->data_queue.push(std::move(data));
//            }
//            that->cond.notify_one();
//        }
//    }
//
//    static void SendData(void *arg) {
//        auto that = (FileSender*)arg;
//        while (!that->is_done) {
//            cond.wait();
//            std::vector<std::string> data;
//            {
//                std::unique_lock lock(that->data_queue_mtx);
//                data = std::move(that->data_queue.front());
//                that->data_queue.pop();
//            }
//            that->client.Send(data);
//        }
//    }
//
//private:
//    std::string file_name;
//    std::string remote_ip;
//    int batch_size;
//    bool is_done;
//    RpcClient client;
//
//    std::thread read_thread;
//    std::vector<std::thread> sender_threads;
//    std::ifstream infile;
//    std::queue<std::vector<std::string>> data_queue;
//    std::condition_variable cond;
//    std::shared_mutex data_queue_mtx;
//};
//
//void Solve(const std::string &file_name, const std::string &remote_ip) {
//    RpcClient client(remote_ip);
//
//    // 设置线程数量
//    size_t thread_size = 5;
//
//    // 读取文件长度
//    std::ifstream infile(file_name);
//    infile.seekg(0, std::ios::end);
//    size_t length = infile.tellg();
//    //    for (size_t position = 0, i = 0; i < thread_size; ++i) {
//    //        auto predict_next_pos = position + length / thread_size;
//    //        // 查找下一个换行符位置
//    //        auto next_line_position = infile.seekg(position, '\n') + 1;
//    //    }
//
//
//    auto read_file = [&] {
//        std::string result;
//        std::ifstream infile(file_name);
//        infile.seekg(0, std::ios::end);
//        size_t length = infile.tellg();
//        infile.seekg(0, std::ios::beg);
//        result.resize(length);
//        infile.read(result.data(), length + 1);
//    };
//
//
//}
//
int main() {
    //    std::unordered_set<std::string_view> ss;
    //    std::vector<std::string> s = {"a", "b", "a", "c", "d", "v", "b", "c"};
    //    for (auto &i: s) {
    //        std::cout << "- " << (ss.find(i) == ss.end()) << std::endl;
    //        ss.insert(i);
    //    }
    //
    //    SimpleSafeMap<std::string, std::shared_ptr<TestA>> m;
    //    m.Insert("a", std::make_shared<TestA>(1));
    //    m.Insert("a", std::make_shared<TestA>(2));
    //    std::cout << m.Find("a")->second->i << std::endl;
    //    std::cout << (m.Find("a") == m.End()) << std::endl;

    //    std::ofstream f;
    //    f.open("test.log");
    //    for (int i = 0; true; ++i) {
    //        f << i << "\u0004\u0004\u0004\u0005\u0005\u0005\n";
    //        std::this_thread::sleep_for(std::chrono::microseconds(100));
    //    }
    //    while (true) {
    //        auto result = std::getenv("NPS_BATCH_SIZE");
    //        std::cout << result << std::endl;
    //        std::cout << (result ? "yes" : "no") << std::endl;
    //        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //    }

    //    std::vector<uint64_t> ids{1, 3, 1, 2, 2, 3, 4, 2, 5};
    //    std::vector<float> values{1.1, 3.3, 1.1, 2.2, 2.2, 3.3, 4.4, 2.2, 5.5};
    //    ZipUnique(ids, values);
    //    utils::display(ids);
    //    utils::display(values);
    return 0;
}