find_package(RapidJSON CONFIG REQUIRED)

add_executable(rapid_json_tu src/tutorial/rapidjson/rj.cpp)
target_link_libraries(rapid_json_tu rapidjson)