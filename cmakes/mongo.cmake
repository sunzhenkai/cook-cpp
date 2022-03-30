find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)

add_executable(mongo src/sample/mongo/mongo.cpp)
target_link_libraries(mongo mongo::bsoncxx_shared mongo::mongocxx_shared)