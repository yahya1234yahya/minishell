import os
import sys

def run_echo_tests():
    echo_tests = {
        "echo 1": "echo",
        "echo 2": "echo echo",
        "echo 3": "eCho",
        "echo 4": "eChO",
        "echo 5": "eCHO",
        "echo 6": "ECHO",
        "echo 7": "echo rhobebou",
        "echo 8": "echo stop barking",
        "echo 9": 'echo "bonjour"',
        "echo 10": "echo bonjour",
        "echo 11": "echo 'bonjour'",
        "echo 12": "echo -n bonjour",
        "echo 13": "echo -nn bonjour",
        "echo 14": "echo -n -n -n bonjour",
        "echo 15": 'echo "-n" bonjour',
        "echo 16": 'echo -n"-n" bonjour',
        "echo 17": 'echo "-nnnn" bonjour',
        "echo 18": 'echo "-n -n -n"-n bonjour',
        "echo 19": 'echo "-n \'-n\'" bonjour',
        "echo 20": "echo ~",
        "echo 21": 'echo "~"',
        "echo 22": "echo '~'",
        "echo 23": "echo ~123",
        "echo 24": "echo 123~",
        "echo 25": "echo ~/123",
        "echo 26": "echo ~/123/456",
        "echo 27": "echo $USER",
        "echo 28": 'echo "$USER"',
        "echo 29": "echo \"'$USER'\"",
        "echo 30": 'echo " \'$USER\' "',
        "echo 31": 'echo text"$USER"',
        "echo 32": "echo text\"'$USER'\" ' $USER '",
        "echo 33": 'echo "text"   "$USER"    "$USER"',
        "echo 34": "echo '              $USER          '",
        "echo 35": 'echo               text "$USER"            "$USER"text',
        "echo 36": "echo ''''''''''$USER'''''''''",
        "echo 37": 'echo """"""""$USER""""""""',
        "echo 38": "echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''",
        "echo 39": "echo $USER '' $USER $USER '' $USER '' $USER -n $USER",
        "echo 40": "echo ' \' ' \\'",
        "echo 41": 'echo \\" \' "\\"\\"\\""',
        "echo 42": 'echo \\\\\\" \\\\\\" \\\\\\" \\\\\\"\\"\\" \\\\\\\'\\\\\\\'',
        "echo 43": 'echo "$USER""$USER""$USER"',
        "echo 44": 'echo text"$USER"test',
        "echo 45": 'echo \'$USER\' "$USER" "text \' text"',
        "echo 46": "echo '$USER'",
        "echo 47": 'echo $USER " "',
        "echo 48": 'echo "$USER""Users/$USER/file""\'$USER\'"\'$USER\'',
        "echo 49": 'echo "$USER$USER$USER"',
        "echo 50": 'echo \'$USER\'"$USER"\'$USER\'',
        "echo 51": 'echo \'"$USER"\'\'$USER\'"""$USER"',
        "echo 52": 'echo " $USER  "\'$PWD\'',
        "echo 53": 'echo " $USER  \$ "\'$PWD\'',
        "echo 54": "echo $USER=4",
        "echo 55": "echo $USER=thallard",
        "echo 56": "echo $USER",
        "echo 57": "echo $?",
        "echo 58": "echo $USER213",
        "echo 59": "echo $USER$12USER$USER=4$USER12",
        "echo 60": "echo $USER $123456789USER $USER123456789",
        "echo 61": "echo $USER $9999USER $8888USER $7777USER",
        "echo 62": "echo $USER $USER9999 $USER8888 $USER7777",
        "echo 63": 'echo "$USER=12$USER"',
        "echo 64": 'echo "$9USER" "\'$USER=12$SOMETHING\'"',
        "echo 65": "echo $PWD/file",
        "echo 66": 'echo "$PWD/file"',
        "echo 67": 'echo "text" "text$USER" ... "$USER"',
        "echo 68": "echo $PWD",
    }

    run_tests(echo_tests)

if __name__ == '__main__':
    if not os.path.exists("./minishell"):
        print("There is no 'minishell' in this directory")
        sys.exit(1)
    set_up()
    run_echo_tests()
    clean_up()
