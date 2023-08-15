#include <iostream>
#include "sample_generated.h"
#include "flatbuffers/minireflect.h"

void TestA() {
    flatbuffers::FlatBufferBuilder fbb;
    std::vector<std::string> names = {"A", "B", "C"};
    auto names_offset = fbb.CreateVectorOfStrings(names);
    auto sample_table_builder = SampleTableBuilder(fbb);
    // 这一行放在 SampleTableBuilder(fbb) 之后会报错: Assertion `!nested' failed
    // auto names_offset = fbb.CreateVectorOfStrings(names);
    sample_table_builder.add_names(names_offset);
    sample_table_builder.Finish();
}

int main() {
    TestA();
    flatbuffers::FlatBufferBuilder fbb;
    auto name = fbb.CreateString("beta");
    auto so = CreateSampleTable(fbb, 0, 1, name);
    fbb.Finish(so);

    auto s = flatbuffers::GetRoot<SampleTable>(fbb.GetBufferPointer());
    std::cout << s->name()->c_str() << std::endl;

    SampleTableT st;
    s->UnPackTo(&st);

    auto r = flatbuffers::FlatBufferToString(fbb.GetBufferPointer(), SampleTableTypeTable());
    std::cout << r << std::endl;
    return 0;
}