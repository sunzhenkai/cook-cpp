#include "seastar/core/metrics.hh"
#include "iostream"
#include "unordered_map"

struct estimated_histogram {
    using clock = std::chrono::steady_clock;
    using duration = clock::duration;
    // buckets is one element longer than bucketOffsets -- the last element is values greater than the last offset
    std::vector<int64_t> buckets;
    std::vector<int64_t> bucket_offsets;
    int64_t _count = 0;
    int64_t _sample_sum = 0;

    estimated_histogram(int bucket_count = 200) {
        new_offsets(bucket_count); //bounder
        buckets.resize(bucket_offsets.size() + 1, 0); //buckets is bucket's counting
    }

    seastar::metrics::histogram get_histogram(size_t lower_bucket = 1, size_t max_buckets = 16) const {
        seastar::metrics::histogram res;
        res.buckets.resize(max_buckets); // set histogram's buckets sum
        int64_t last_bound = lower_bucket;
        uint64_t cummulative_count = 0;
        size_t pos = 0;
        res.sample_count = _count;
        res.sample_sum = _sample_sum;
        for (size_t i = 0; i < res.buckets.size(); i++) {
            auto &v = res.buckets[i];
            v.upper_bound = last_bound;

            while (bucket_offsets[pos] <= last_bound) {
                cummulative_count += buckets[pos];
                pos++;
            }
            v.count = cummulative_count;
            std::cout << i << "," << v.upper_bound << "," << cummulative_count << std::endl;
            int64_t val = round(last_bound * 1.2);
            if (val == last_bound) val++;
            last_bound = val;
        }
        return res;
    }

    seastar::metrics::histogram get_histogram(duration minmal_latency, size_t max_buckets = 16) const {
        return get_histogram(std::chrono::duration_cast<std::chrono::microseconds>(minmal_latency).count(),
                             max_buckets);
    }

private:
    void new_offsets(int size) {
        bucket_offsets.resize(size);
        if (size == 0) {
            return;
        }
        int64_t last = 1;
        bucket_offsets[0] = last;
        for (int i = 1; i < size; i++) {
            int64_t next = round(last * 1.11);
            if (next == last) {
                next++;
            }
            //int64_t next = last + 1;
            bucket_offsets[i] = next;
            last = next;
        }
    }
};

int main() {
    std::unordered_map<size_t, estimated_histogram> mm;
    estimated_histogram m;
    mm[0].get_histogram(100, 35);
    mm[1].get_histogram(2, 35);
    return 0;
}