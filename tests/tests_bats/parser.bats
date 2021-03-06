#! / Usr / bin / env bats

load test_helper

#######################################################################
#                            NO ERROR TESTS                           #
#######################################################################
@test "PARSER: Testing [OK] for NULL" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser ""
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->$name_exec: EXIT-ERROR: Fatal testing error: Couldn't catch the error."
  echo
  [ "${lines[0]}" = "$name_exec: EXIT-ERROR: Fatal testing error: Couldn't catch the error." ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for ' '" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser " "
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for ' ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser " ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls '" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls "
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls -l'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls -l"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls -l | cat -e'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls -l | cat -e"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls -l | cat -e | pleins | de | pipe'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls -l | cat -e | pleins | de | pipe"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls ; ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls ; ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'abc; ;abc'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "abc; ;abc"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${parser_error_simple_pv}"
  echo
  [ "${lines[0]}" = "${parser_error_simple_pv}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls ; ls ; ls ; ls ; ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls ; ls ; ls ; ls ; ls"
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls || ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls || ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls || ls || ls || ls || ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls || ls || ls || ls || ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls && ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls && ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls && ls && ls && ls && ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls && ls && ls && ls && ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls & ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls & ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->$name_exec: Lexing error."
  echo
  [ "${lines[0]}" = "$name_exec: Lexing error." ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls & ls & ls & ls & ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls & ls & ls & ls & ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->$name_exec: Lexer error."
  echo
  [ "${lines[0]}" = "$name_exec: Lexing error." ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls -l | cat -e | lol | maman'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls -l | cat -e | lol | maman"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls;'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls;"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls;toto;'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls;toto;"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls -l | cat -e; cat -e < lol; ls > toto.txt; rm toto.txt;'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls -l | cat -e; cat -e < lol; ls > toto.txt; rm toto.txt;"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for '<ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "<ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [OK] for 'ls -l | cat -e; cat -e < lol; toto && tata < ta > toto.txt; rm toto'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls -l | cat -e; cat -e < lol; toto && tata < ta > toto.txt; rm toto"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

######################################################################
######################################################################


#######################################################################
#                            ERROR TESTS                              #
#######################################################################
@test "PARSER: Testing [Error] for '|ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "|ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${parser_error_simple_p}"
  echo
  [ "${lines[0]}" = "${parser_error_simple_p}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for '||ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "||ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${parser_error_double_p}"
  echo
  [ "${lines[0]}" = "${parser_error_double_p}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for '&ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "&ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${parser_error_simple_es}"
  echo
  [ "${lines[0]}" = "${parser_error_simple_es}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for '&&ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "&&ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${parser_error_double_es}"
  echo
  [ "${lines[0]}" = "${parser_error_double_es}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for '&ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "&ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->$name_exec: Lexing error."
  echo
  [ "${lines[0]}" = "$name_exec: Lexing error." ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for 'ls>'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls>"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${parser_error_redir}"
  echo
  [ "${lines[0]}" = "${parser_error_redir}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for 'ls>>'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls>>"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${parser_error_redir_double}"
  echo
  [ "${lines[0]}" = "${parser_error_redir_double}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for ';ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser ";ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for ';;ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser ";;ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${parser_error_simple_pv}"
  echo
  [ "${lines[0]}" = "${parser_error_simple_pv}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for ls;; " {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser 'ls;;'
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${parser_error_simple_pv}"
  echo
  [ "${lines[0]}" = "${parser_error_simple_pv}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for ';'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser ";"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${okparser}"
  echo
  [ "${lines[0]}" = "${okparser}" ]
  [ "$status" -eq 0 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for ';;'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser ";;"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${parser_error_simple_pv}"
  echo
  [ "${lines[0]}" = "${parser_error_simple_pv}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for 'abc;;abc'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "abc;;abc"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${parser_error_simple_pv}"
  echo
  [ "${lines[0]}" = "${parser_error_simple_pv}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for 'abc&&&&'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "abc&&&&"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->${parser_error_double_es}"
  echo
  [ "${lines[0]}" = "${parser_error_double_es}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for 'ls |&|'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls |&|"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->$name_exec: Lexing error."
  echo
  [ "${lines[0]}" = "$name_exec: Lexing error." ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for 'ls ||&;ls'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls ||&;ls"
  echo "ERROR:"
  echo "$name_exec OUTPUT   ->${lines[0]}"
  echo "$name_exec EXPECTED ->$name_exec: Lexing error."
  echo
  [ "${lines[0]}" = "$name_exec: Lexing error." ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for 'ls|'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls|"
  [ "${lines[0]}" = "${parser_error_simple_p}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}

@test "PARSER: Testing [Error] for 'ls||'" {
  run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -t parser "ls||"
  [ "${lines[0]}" = "${parser_error_double_p}" ]
  [ "$status" -eq 1 ]
check_leaks_function parser
}
