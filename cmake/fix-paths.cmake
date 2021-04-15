# CMAKE_MODULE_PATH is passed in CI with backslashes but is difficult to fix on the CI side
if(CMAKE_MODULE_PATH)
    string(REPLACE "\\" "/" CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH})
endif()