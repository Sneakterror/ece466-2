
function(p1_failure name)
   add_test(NAME Fail-${name}
      COMMAND ${CMAKE_CURRENT_BINARY_DIR}/../p1 ${CMAKE_CURRENT_SOURCE_DIR}/${name}.p1 ${CMAKE_CURRENT_BINARY_DIR}/${name}.bc
      )
   set_tests_properties(Fail-${name} PROPERTIES WILL_FAIL TRUE)
endfunction(p1_failure)

p1_failure(fail_1)
p1_failure(fail_2)
p1_failure(fail_3)
p1_failure(fail_4)
p1_failure(fail_5)
p1_failure(fail_6)
p1_failure(fail_7)
p1_failure(fail_8)
p1_failure(fail_9)
p1_failure(fail_10)
p1_failure(fail_11)
p1_failure(fail_12)
p1_failure(fail_13)
p1_failure(fail_14)
p1_failure(fail_15)
p1_failure(fail_16)
p1_failure(fail_17)

add_executable(llvm-inst-count llvm-inst-count.cpp)
target_link_libraries(llvm-inst-count ${llvm_libs})

function(p1_compile_test name class)
   add_custom_command(
      OUTPUT ${name}.bc
      COMMAND p1 ${CMAKE_CURRENT_SOURCE_DIR}/${name}.p1 ${CMAKE_CURRENT_BINARY_DIR}/${name}.bc
      DEPENDS p1 ${CMAKE_CURRENT_SOURCE_DIR}/${name}.p1
      )
   add_custom_command(
      OUTPUT ${name}.bc.o
      COMMAND clang-19 -c -o ${CMAKE_CURRENT_BINARY_DIR}/${name}.bc.o ${CMAKE_CURRENT_BINARY_DIR}/${name}.bc
      DEPENDS ${name}.bc
      )

   add_test(NAME P1Compile-${name} COMMAND p1 ${CMAKE_CURRENT_SOURCE_DIR}/${name}.p1 ${CMAKE_CURRENT_BINARY_DIR}/${name}.bc)   
   add_test(NAME Disassemble-${name} COMMAND llvm-dis-19 ${CMAKE_CURRENT_BINARY_DIR}/${name}.bc)   
endfunction(p1_compile_test)

function(p1_run_test name class)
   add_custom_command(
      OUTPUT ${name}.bc
      COMMAND p1 ${CMAKE_CURRENT_SOURCE_DIR}/${name}.p1 ${CMAKE_CURRENT_BINARY_DIR}/${name}.bc
      DEPENDS p1 ${CMAKE_CURRENT_SOURCE_DIR}/${name}.p1
      )
   add_custom_command(
      OUTPUT ${name}.bc.o
      COMMAND clang-19 -c -o ${CMAKE_CURRENT_BINARY_DIR}/${name}.bc.o ${CMAKE_CURRENT_BINARY_DIR}/${name}.bc
      DEPENDS ${name}.bc
      )
   add_executable(${name} ${CMAKE_CURRENT_BINARY_DIR}/${name}.bc.o ${name}.c)
   target_link_libraries(${name} eigen_c stdc++)   
   add_test(NAME Run-${name} COMMAND ${name} )
   #add_test(NAME InstCount-${name} COMMAND ${CMAKE_CURRENT_BINARY_DIR}/llvm-inst-count ${CMAKE_CURRENT_BINARY_DIR}/${name}.bc)
endfunction(p1_run_test)


p1_compile_test(check_1 566)
p1_compile_test(check_2 566)
p1_compile_test(check_3 566)
p1_compile_test(check_4 566)
p1_compile_test(check_5 566)
p1_compile_test(check_6 566)

# just compile

p1_compile_test(test_0 566)
p1_compile_test(test_1 566)
p1_compile_test(test_2 566)
p1_compile_test(test_3 566)
p1_compile_test(test_4 566)
p1_compile_test(test_5 566)
p1_compile_test(test_6 566)
p1_compile_test(test_7 566)
p1_compile_test(test_8 566)
p1_compile_test(test_9 566)
p1_compile_test(test_11 566)
p1_compile_test(test_15 566)

p1_compile_test(test_10 566)
p1_compile_test(test_12 566)
p1_compile_test(test_13 566)
p1_compile_test(test_14 566)
p1_compile_test(test_16 566)
p1_compile_test(test_17 566)
p1_compile_test(test_18 566)

# run the code and test for correctness

p1_run_test(test_0 566)
p1_run_test(test_1 566)
p1_run_test(test_2 566)
p1_run_test(test_3 566)
p1_run_test(test_4 566)
p1_run_test(test_5 566)
p1_run_test(test_6 566)
p1_run_test(test_7 566)
p1_run_test(test_8 566)
p1_run_test(test_9 566)
p1_run_test(test_11 566)
p1_run_test(test_15 566)

p1_run_test(test_10 566)
p1_run_test(test_12 566)
p1_run_test(test_13 566)
p1_run_test(test_14 566)
p1_run_test(test_16 566)
p1_run_test(test_17 566)
p1_run_test(test_18 566)

#p1_run_test(test_mytest 566)
