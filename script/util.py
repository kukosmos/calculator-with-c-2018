import os
import fnmatch
import sys
import subprocess

target = 'run'
ccopt = ' -w'

def find_srcs(path):
    whole_list = os.listdir(path)
    result = []
    for name in whole_list:
        if fnmatch.fnmatch(name, '*.c'):
            full_path = os.path.join(path, name)
            result.append(full_path)
    return result

def find_testcases(path):
    whole_list = os.listdir(path)
    result = []
    for name in whole_list:
        if fnmatch.fnmatch(name, '*.in'):
            full_path = os.path.join(path, name)
            result.append(full_path)
    return result

def gen_testcases(lec, test):
    result = {}
    f = open('./' + lec + '/solution.list')
    input = None
    output = None
    while True:
        line = f.readline()
        if not line:
            break
        if fnmatch.fnmatch(line, 'input: *'):
            input = line.strip()[7:]
        elif fnmatch.fnmatch(line, 'output: *'):
            output = line.replace('\\n', '\n').strip()[8:]
        else:
            print('parsing error: ' + lec + '/solution.list')
            sys.exit(0)
        if input is not None and output is not None:
            result.update({input: output})
            input = None
            output = None
    f.close()
    return result

def execute(src, testcases):
    complile_command = 'gcc -o '+ target + ' ' + src + ccopt
    cp = subprocess.Popen(complile_command, stdout = subprocess.PIPE, stderr = subprocess.PIPE, shell = True)
    out, err = cp.communicate()
    if err:
        print(err)
        print('compile error\n')
        return False
    keys = testcases.keys()
    for testcase in keys:
        result = testcases[testcase]
        run_command = './' + target + ' ' + testcase
        rp = subprocess.Popen(run_command, stdout = subprocess.PIPE, stderr = subprocess.PIPE, shell = True)
        out, err = rp.communicate()
        if err:
            print(err)
            print('runtime error\n')
            return False
        else:
            out = out.decode().strip()
            if out == result:
                pass
            else:
                print('failed')
                print('input: ' + testcase)
                print('expected output: ' + result)
                print('program output: ' + out + '\n')
                return False
    return True

def remove_target():
    remove_command = 'rm -f ' + target
    subprocess.Popen(remove_command, shell = True).communicate()
