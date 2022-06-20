#include "iostream"
#include "vector"
#include "hello.pb.h"
#include "mv.pb.h"
#include "google/protobuf/reflection.h"
#include "atomic"
#include "google/protobuf/text_format.h"
#include "sstream"

class SimpleRateLimit {
    int64_t microseconds_per_second = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::seconds(1)).count();
    int64_t permits_per_seconds_;
    std::atomic<uint64_t> next_permit_ts_{0};
    std::atomic<int64_t> remain_permits_{};
public:
    explicit SimpleRateLimit(int64_t permits_per_seconds) : permits_per_seconds_(permits_per_seconds) {
        assert(permits_per_seconds_ > 0);
        CalculatePermits();
    }

    bool CalculatePermits() {
        auto now = std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
        if (now > next_permit_ts_) {
            if (now > next_permit_ts_.exchange(now + microseconds_per_second)) {
                remain_permits_.exchange(permits_per_seconds_);
            }
            return true;
        }
        return false;
    }

    bool TryAcquire() {
        if (remain_permits_-- <= 0) {
            return CalculatePermits() && remain_permits_-- > 0;
        } else {
            return true;
        }
    }
};


int main() {
    RsRequest req;
    if (req.has_abkeys() && !req.abkeys().used_ab_keys().empty()) {
        for (auto &ele: req.abkeys().used_ab_keys()) {
            std::cout << "user_ab_keys:" << ele.key() << "\t" << ele.value();
        }
    }

//    std::atomic<int> ai{4};
//    std::cout << ai-- << std::endl;
//    ai++;
//    std::cout << --ai << std::endl;

    World wd{};
    std::cout << wd.age() << std::endl;
    auto age = World::GetDescriptor()->FindFieldByName("age");
    World::GetReflection()->SetInt64(&wd, age, 100);
    std::cout << wd.age() << std::endl;

    auto tag = World::GetDescriptor()->FindFieldByName("tag");
    World::GetReflection()->AddString(&wd, tag, "abc");
    World::GetReflection()->AddString(&wd, tag, "b");
    std::cout << wd.tag()[1] << std::endl;
    World::GetReflection()->SetRepeatedString(&wd, tag, 1, "c");
    std::cout << wd.tag()[1] << std::endl;
    std::cout << "name: " << wd.sea().name() << std::endl;
    wd.set_age(1);
    wd.mutable_sea()->set_name("go");

    auto f = World::GetDescriptor()->FindFieldByName("sea");
    auto &m = World::GetReflection()->GetMessage(wd, f);
    auto mp = &m;
    auto sf = m.GetDescriptor()->FindFieldByName("name");
    std::cout << "field name: " << sf->name() << std::endl;

    std::cout << wd.sea().GetDescriptor()->field_count() << std::endl;

    for (int i = 0; i < World::GetDescriptor()->field_count(); ++i) {
        auto f = World::GetDescriptor()->field(i);
        std::cout << "field name 2: " << f->name() << " - " << f->type_name() << std::endl;
    }

    for (int i = 0; i < World::GetDescriptor()->field_count(); ++i) {
        auto f = World::GetDescriptor()->field(i);
        if (f->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE) {
            auto mp = &World::GetReflection()->GetMessage(wd, f);
            std::cout << "kkk " << mp->GetDescriptor()->field_count() << std::endl;
            for (int j = 0; j < mp->GetDescriptor()->field_count(); ++j) {
                auto l2f = mp->GetDescriptor()->field(j);
                std::cout << "add field: " << f->name() << " - " << l2f->name() << std::endl;
            }
        }
    }

    m.GetReflection()->SetString(const_cast<google::protobuf::Message *>(mp), sf, "pacific");
//    m.GetReflection()->SetString(std::const_pointer_cast<google::protobuf::Message *>(&m), f, "no");
    m.PrintDebugString();

    std::string output;
    std::stringstream o;
    wd.SerializeToString(&output);
//    google::protobuf::TextFormat::PrintToString(wd, &output);
    std::cout << "output: " << output << std::endl;

    World wd2;
    wd2.ParseFromString(output);
    std::cout << wd2.age() << std::endl;


    SimpleRateLimit rt(1);
//    while (true) {
//        if (rt.TryAcquire()) {
//            std::cout << "ok " << std::chrono::duration_cast<std::chrono::milliseconds>(
//                    std::chrono::system_clock::now().time_since_epoch()).count() << std::endl;
//        }
//    }

//    auto f = [&]() {
//        while (true) {
//            if (rt.TryAcquire()) {
//                std::cout << "ok " << std::this_thread::get_id() << " "
//                          << std::chrono::duration_cast<std::chrono::milliseconds>(
//                                  std::chrono::system_clock::now().time_since_epoch()).count() << std::endl;
//            }
//        }
//    };
//
//    std::vector<std::thread> ts;
//    for (int i = 0; i < 10; ++i) {
//        ts.emplace_back(f);
//    }
//    for (auto &t: ts) {
//        t.join();
//    }
    return 0;
}