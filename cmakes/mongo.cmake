find_package(bsoncxx CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Snappy CONFIG REQUIRED)

find_library(LZ4_LIBRARY NAMES lz4d lz4)
find_library(ZSTD_LIBRARY NAMES zstd)
find_library(ORC_LIBRARY NAMES orc)

add_executable(mongo src/sample/mongo/mongo.cpp)
target_link_libraries(mongo
        $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>
        $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>
)

add_executable(bson src/sample/mongo/bsoncxx.cpp)
target_link_libraries(bson
        $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>
        ${ORC_LIBRARY} protobuf::libprotoc protobuf::libprotobuf Snappy::snappy ${LZ4_LIBRARY} ${ZSTD_LIBRARY} ZLIB::ZLIB
)