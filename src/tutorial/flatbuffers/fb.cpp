#include <iostream>
#include "sample_generated.h"
#include "flatbuffers/minireflect.h"


int main() {
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