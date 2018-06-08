import sys
from script import test_all
from script import test_one
from script import gen_solution

if __name__ == '__main__':
    arg_err = True
    arg_help = False
    if len(sys.argv) == 2:
        if sys.argv[1] == '-h':
            arg_err = False
            arg_help = True
        elif sys.argv[1] == '--help':
            arg_err = False
            arg_help = True
        else:
            arg_err = False
            test_all.main(sys.argv[1])
    elif len(sys.argv) == 3:
        arg_err = False
        test_one.main(sys.argv[1], sys.argv[2])
    elif len(sys.argv) == 4:
        if sys.argv[3] == '-g':
            arg_err = False
            gen_solution.main(sys.argv[1], sys.argv[2])
        elif sys.argv[3] == '--generate':
            arg_err = False
            gen_solution.main(sys.argv[1], sys.argv[2])
    if arg_err:
        print('\'python test.py -h\' for detailed usage')
    elif arg_help:
        print('Usage: python test.py -h')
        print('Usage: python test.py --help')
        print('    To see how to use python script')
        print('')
        print('Usage: python test.py <lecture>')
        print('    To test all files in lecture')
        print('')
        print('Usage: python test.py <lecture> <.c file>')
        print('    To test one file in lecture')
        print('')
        print('Usage: python test.py <lecture> <solution .c file> -g')
        print('Usage: python test.py <lecture> <solution .c file> --generate')
        print('    To generate solution.list file in lecture using solution file in lecture directory')