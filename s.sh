#!/bin/bash

# Paths to your minishell and bash
MINISHELL_PATH="./minishell"  # Path to your compiled minishell
BASH_PATH="/bin/bash"

# Temporary files for output comparison
MINISHELL_OUTPUT="minishell_output.txt"
BASH_OUTPUT="bash_output.txt"
DIFF_OUTPUT="diff_output.txt"

# Function to run a command in both shells and compare outputs
run_and_compare() {
    cmd="$1"
    echo -e "\033[1;34mRunning: $cmd\033[0m"

    # Run command in minishell and save output
    echo -e "$cmd" | $MINISHELL_PATH > $MINISHELL_OUTPUT 2>&1

    # Run command in bash and save output
    echo -e "$cmd" | $BASH_PATH > $BASH_OUTPUT 2>&1

    # Compare outputs and print results
    diff $MINISHELL_OUTPUT $BASH_OUTPUT > $DIFF_OUTPUT
    if [[ -s $DIFF_OUTPUT ]]; then
        echo -e "\033[0;31m[DIFFERENCE]\033[0m"
        echo -e "\033[1;31mMinishell Output:\033[0m"
        cat $MINISHELL_OUTPUT
        echo -e "\033[1;31mBash Output:\033[0m"
        cat $BASH_OUTPUT
        echo -e "\033[1;33mDifference:\033[0m"
        cat $DIFF_OUTPUT
    else
        echo -e "\033[0;32m[IDENTICAL]\033[0m"
    fi
    echo  # Empty line for readability
}

# List of commands
commands=(
    "echo hello world"
    "echo \"hello world\""
    "echo 'hello world'"
    "echo hello'world'"
    "echo hello\"\"world"
    "echo ''"
    "echo \"\$PWD\""
    "echo '\$PWD'"
    "echo \"aspas ->'\""
    "echo \"aspas -> ' \""
    "echo 'aspas ->\"'"
    "echo 'aspas -> \" '"
    "echo \"> >> < * ? [ ] | ; [ ] || && ( ) & # $ \\ <<\""
    "echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \\ <<'"
    "echo \"exit_code ->\$? user ->\$USER home -> \$HOME\""
    "echo 'exit_code ->\$? user ->\$USER home -> \$HOME'"
    "echo \"\$\""
    "echo '\$'"
    "echo \$"
    "echo \$?"
    "echo \$?HELLO"
    "pwd"
    "pwd oi"
    "export hello"
    "export HELLO=123"
    "export A-"
    "export HELLO=123 A"
    "export HELLO=\"123 A-\""
    "export hello world"
    "export HELLO-=123"
    "export ="
    "export 123"
    "unset"
    "unset HELLO"
    "unset HELLO1 HELLO2"
    "unset HOME"
    "unset PATH"
    "unset SHELL"
    "cd \$PWD"
    "cd \$PWD hi"
    "cd 123123"
    "exit 123"
    "exit 298"
    "exit +100"
    "exit \"+100\""
    "exit +\"100\""
    "exit -100"
    "exit \"-100\""
    "exit -\"100\""
    "exit hello"
    "exit 42 world"
)

# Loop over each command and run in both shells
for cmd in "${commands[@]}"; do
    run_and_compare "$cmd"
done

# Clean up temporary files
rm -f $MINISHELL_OUTPUT $BASH_OUTPUT $DIFF_OUTPUT
