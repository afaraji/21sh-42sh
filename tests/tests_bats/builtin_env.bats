#! / Usr / bin / env bats

load test_helper

#######################################################################
#                            SIMPLE                                   #
#######################################################################

@test "BUILTIN_ENV: Testing [cmd_cd] for 'env cd folder_not_exist'" {
    expect="/usr/bin/cd: line 4: cd: folder_not_exist: No such file or directory"
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'env cd folder_not_exist'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->$expect"
    echo
    [ "${lines[0]}" = "$expect" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [double_assign] for 'env myvar=aaa myvar=123 bash -c 'echo 111$myvar; bash -c "echo 222$myvar"''" {
    val2exec="env myvar=aaa myvar=123 bash -c 'echo 111$myvar; bash -c \"echo 222$myvar\"'"
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c '$val2exec'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->111123"
    echo "                     222123"
    echo
    [ "${lines[0]}" = "111123" ]
    [ "${lines[1]}" = "222123" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}


@test "BUILTIN_ENV: Testing [double_dash] for 'env -- myvar_aa=bb env | grep myvar_aa='" {
    expect=`env -- myvar_aa=bb env | grep myvar_aa=`
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'env -- myvar_aa=bb env | grep myvar_aa='
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->$expect"
    echo
    [ "${lines[0]}" = "$expect" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [echo] for 'echo \"start\"; env myvar1=11 myvar2=22 echo aaa bbb ccc; env | grep myvar; echo \"end\"'" {
    expect=`echo "start"; env myvar1=11 myvar2=22 echo aaa bbb ccc; env | grep myvar; echo "end"`
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'echo "start"; env myvar1=11 myvar2=22 echo aaa bbb ccc; env | grep myvar; echo "end"'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->$expect"
    echo
    [ "${lines[0]}" = "start" ]
    [ "${lines[1]}" = "aaa bbb ccc" ]
    [ "${lines[2]}" = "end" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [env_env_env_env] for 'env myvar=aa env myvar=ab env | grep myvar; env myvar2=bb env myvar3=cc env | grep myvar | sort; env | grep myvar | sort'" {
    expect=`env myvar=aa env myvar=ab env | grep myvar; env myvar2=bb env myvar3=cc env | grep myvar | sort; env | grep myvar | sort`
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'env myvar=aa env myvar=ab env | grep myvar; env myvar2=bb env myvar3=cc env | grep myvar | sort; env | grep myvar | sort'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->$expect"
    echo
    [ "${lines[0]}" = "myvar=ab" ]
    [ "${lines[1]}" = "myvar2=bb" ]
    [ "${lines[2]}" = "myvar3=cc" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [env_spec] for 'setenv hello=pouet; setenv ahah=hehe; env | grep hello | cat -e; env | grep ahah | cat -e; unsetenv hello; env | grep hello | cat -e; env temporary=hello | grep temporary | cat -e'" {
    expect=`setenv hello=pouet; setenv ahah=hehe; env | grep hello | cat -e; env | grep ahah | cat -e; unsetenv hello; env | grep hello | cat -e; env temporary=hello | grep temporary | cat -e`
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'setenv hello=pouet; setenv ahah=hehe; env | grep hello | cat -e; env | grep ahah | cat -e; unsetenv hello; env | grep hello | cat -e; env temporary=hello | grep temporary | cat -e'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->$expect"
    echo
    [ "${lines[0]}" = "hello=pouet$" ]
    [ "${lines[1]}" = "ahah=hehe$" ]
    [ "${lines[2]}" = "temporary=hello$" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [exit_code_error] for 'env echo a | grep b'" {
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'env echo a | grep b'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->"
    echo
    [ "${lines[0]}" = "" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [exit_code_invalid_var_name] for 'env ='" {
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'env ='
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->env: setenv =: Invalid argument"
    echo
    [ "${lines[0]}" = "env: setenv =: Invalid argument" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [exit_code_ok] for 'env echo a | grep a'" {
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'env echo a | grep a'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->a"
    echo
    [ "${lines[0]}" = "a" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [invalid_var_name] for 'env 42SHTESTS1=TOKEN1 42SHTESTS2=TOKEN2 42SHTESTS3=TOKEN3 ls; env =1 echo abc; env =; env 0=0; env echo abc'" {
    expect=`env 42SHTESTS1=TOKEN1 42SHTESTS2=TOKEN2 42SHTESTS3=TOKEN3 ls; env =1 echo abc; env =; env 0=0; env echo abc`
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'env 42SHTESTS1=TOKEN1 42SHTESTS2=TOKEN2 42SHTESTS3=TOKEN3 ls; env =1 echo abc; env =; env 0=0; env echo abc'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->$expect"
    echo
    [ "${lines[0]}" = "$expect" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [modify_var] for 'setenv env_foo_1=bar1; echo ===== 1; env env_foo_2=bar2 env | grep env_foo_; echo ===== 2; env -i env_foo_2=bar3 env | grep env_foo_'" {
    expect=`setenv env_foo_1=bar1; echo ===== 1; env env_foo_2=bar2 env | grep env_foo_; echo ===== 2; env -i env_foo_2=bar3 env | grep env_foo_`
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'setenv env_foo_1=bar1; echo ===== 1; env env_foo_2=bar2 env | grep env_foo_; echo ===== 2; env -i env_foo_2=bar3 env | grep env_foo_'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->$expect"
    echo
    [ "${lines[0]}" = "===== 1" ]
    [ "${lines[1]}" = "env_foo_1=bar1" ]
    [ "${lines[2]}" = "env_foo_2=bar2" ]
    [ "${lines[3]}" = "===== 2" ]
    [ "${lines[4]}" = "env_foo_2=bar3" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [opt_i_assign] for 'env -i aa=bb cc=dd; env -i aaa=bbb'" {
    expect=`env -i aa=bb cc=dd; env -i aaa=bbb`
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'env -i aa=bb cc=dd; env -i aaa=bbb'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->$expect"
    echo
    [ "${lines[0]}" = "aa=bb" ]
    [ "${lines[1]}" = "cc=dd" ]
    [ "${lines[2]}" = "aaa=bbb" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [opt_i_path] for 'env ls; env PATH= ls; env PATH=\'\' ls; env PATH=/bin ls; env route; env PATH= route; env PATH=\'\' route; env PATH=/sbin route; env -i ls; env -i PATH= ls; env -i PATH=\'\' ls; env -i PATH=/bin ls; env -i route; env -i PATH= route; env -i PATH=\'\' route ; env -i PATH=/sbin route'" {
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'env ls; env PATH= ls; env PATH="" ls; env PATH=/bin ls; env route; env PATH= route; env PATH="" route; env PATH=/sbin route; env -i ls; env -i PATH= ls; env -i PATH="" ls; env -i PATH=/bin ls; env -i route; env -i PATH= route; env -i PATH="" route ; env -i PATH=/sbin route'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->21sh: execution: command not found: ls"
    echo "$name_exec EXPECTED ->21sh: execution: command not found: ls"
    echo "$name_exec EXPECTED ->usage: route [-dnqtv] command [[modifiers] args]"
    echo "$name_exec EXPECTED ->21sh: execution: command not found: route"
    echo "$name_exec EXPECTED ->21sh: execution: command not found: route"
    echo "$name_exec EXPECTED ->usage: route [-dnqtv] command [[modifiers] args]"
    echo "$name_exec EXPECTED ->21sh: execution: command not found: ls"
    echo "$name_exec EXPECTED ->21sh: execution: command not found: ls"
    echo "$name_exec EXPECTED ->21sh: execution: command not found: route"
    echo "$name_exec EXPECTED ->21sh: execution: command not found: route"
    echo "$name_exec EXPECTED ->21sh: execution: command not found: route"
    echo "$name_exec EXPECTED ->usage: route [-dnqtv] command [[modifiers] args]"

    echo
    [ "${lines[0]}" = "21sh: execution: command not found: ls" ]
    [ "${lines[1]}" = "21sh: execution: command not found: ls" ]
    [ "${lines[2]}" = "usage: route [-dnqtv] command [[modifiers] args]" ]
    [ "${lines[3]}" = "21sh: execution: command not found: route" ]
    [ "${lines[4]}" = "21sh: execution: command not found: route" ]
    [ "${lines[5]}" = "usage: route [-dnqtv] command [[modifiers] args]" ]
    [ "${lines[6]}" = "21sh: execution: command not found: ls" ]
    [ "${lines[7]}" = "21sh: execution: command not found: ls" ]
    [ "${lines[8]}" = "21sh: execution: command not found: route" ]
    [ "${lines[9]}" = "21sh: execution: command not found: route" ]
    [ "${lines[10]}" = "21sh: execution: command not found: route" ]
    [ "${lines[11]}" = "usage: route [-dnqtv] command [[modifiers] args]" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}


@test "BUILTIN_ENV: Testing [opt_i_simple] for 'setenv foo=bar; echo ===== 1; env env | grep foo; echo ===== 2; env -i env | grep foo; env -i echo bla; echo bli'" {
    expect=`setenv foo=bar; echo ===== 1; env env | grep foo; echo ===== 2; env -i env | grep foo; env -i echo bla; echo bli`
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'setenv foo=bar; echo ===== 1; env env | grep foo; echo ===== 2; env -i env | grep foo; env -i echo bla; echo bli'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->$expect"
    echo
    [ "${lines[0]}" = "===== 1" ]
    [ "${lines[1]}" = "foo=bar" ]
    [ "${lines[2]}" = "===== 2" ]
    [ "${lines[3]}" = "bla" ]
    [ "${lines[4]}" = "bli" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [subshell] for '(env -i A=1 B=2 C=3| cat -e) | wc'" {
    expect=`(env -i A=1 B=2 C=3| cat -e) | wc`
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c '(env -i A=1 B=2 C=3| cat -e) | wc'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->$expect"
    echo
    [ "${lines[0]}" = "$expect" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [with_builtin_spec] for 'env echo abc'" {
    expect=`env echo abc`
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'env echo abc'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->$expect"
    echo
    [ "${lines[0]}" = "$expect" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [with_variable_assign_and_expan_spec] for 'setenv myvar=456; env myvar=123 bash -c \'echo \$myvar\''" {
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'setenv myvar=456; env myvar=123 bash -c "echo $myvar"'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->123"
    echo
    [ "${lines[0]}" = "123" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}

@test "BUILTIN_ENV: Testing [with_variable_assign_spec] for 'setenv env_test_var=456; env env_test_var=123 bash -c \'env | grep env_test_var\''" {
    run $val_cmd ${BATS_TEST_DIRNAME}/../../$name_exec -c 'setenv env_test_var=456; env env_test_var=123 bash -c "env | grep env_test_var"'
    echo "ERROR:"
    display_line_output
    echo "$name_exec EXPECTED ->env_test_var=123"
    echo
    [ "${lines[0]}" = "env_test_var=123" ]
    [ "$status" -eq 0 ]
    check_leaks_function exec
}