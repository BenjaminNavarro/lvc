# CMAKE_MODULE_PATH is passed in CI with backslashes but is difficult to fix on the CI side
string(REPLACE "\\" "/" CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH})