# CMake generated Testfile for 
# Source directory: /home/m4kulatura/Documents/GitHub/kektech-c/deps/opus
# Build directory: /home/m4kulatura/Documents/GitHub/kektech-c/build/3rdParty/opus
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_opus_decode "/usr/bin/cmake" "-DTEST_EXECUTABLE=/home/m4kulatura/Documents/GitHub/kektech-c/build/bin/test_opus_decode" "-DCMAKE_SYSTEM_NAME=Linux" "-P" "/home/m4kulatura/Documents/GitHub/kektech-c/deps/opus/cmake/RunTest.cmake")
set_tests_properties(test_opus_decode PROPERTIES  _BACKTRACE_TRIPLES "/home/m4kulatura/Documents/GitHub/kektech-c/deps/opus/CMakeLists.txt;610;add_test;/home/m4kulatura/Documents/GitHub/kektech-c/deps/opus/CMakeLists.txt;0;")
add_test(test_opus_padding "/usr/bin/cmake" "-DTEST_EXECUTABLE=/home/m4kulatura/Documents/GitHub/kektech-c/build/bin/test_opus_padding" "-DCMAKE_SYSTEM_NAME=Linux" "-P" "/home/m4kulatura/Documents/GitHub/kektech-c/deps/opus/cmake/RunTest.cmake")
set_tests_properties(test_opus_padding PROPERTIES  _BACKTRACE_TRIPLES "/home/m4kulatura/Documents/GitHub/kektech-c/deps/opus/CMakeLists.txt;619;add_test;/home/m4kulatura/Documents/GitHub/kektech-c/deps/opus/CMakeLists.txt;0;")
add_test(test_opus_api "/usr/bin/cmake" "-DTEST_EXECUTABLE=/home/m4kulatura/Documents/GitHub/kektech-c/build/bin/test_opus_api" "-DCMAKE_SYSTEM_NAME=Linux" "-P" "/home/m4kulatura/Documents/GitHub/kektech-c/deps/opus/cmake/RunTest.cmake")
set_tests_properties(test_opus_api PROPERTIES  _BACKTRACE_TRIPLES "/home/m4kulatura/Documents/GitHub/kektech-c/deps/opus/CMakeLists.txt;632;add_test;/home/m4kulatura/Documents/GitHub/kektech-c/deps/opus/CMakeLists.txt;0;")
add_test(test_opus_encode "/usr/bin/cmake" "-DTEST_EXECUTABLE=/home/m4kulatura/Documents/GitHub/kektech-c/build/bin/test_opus_encode" "-DCMAKE_SYSTEM_NAME=Linux" "-P" "/home/m4kulatura/Documents/GitHub/kektech-c/deps/opus/cmake/RunTest.cmake")
set_tests_properties(test_opus_encode PROPERTIES  _BACKTRACE_TRIPLES "/home/m4kulatura/Documents/GitHub/kektech-c/deps/opus/CMakeLists.txt;642;add_test;/home/m4kulatura/Documents/GitHub/kektech-c/deps/opus/CMakeLists.txt;0;")
