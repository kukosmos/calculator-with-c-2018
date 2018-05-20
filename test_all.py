import os
import fnmatch
import sys
import subprocess

def find_src (path):
    whole_list = os.listdir (path)
    result = []
    for name in whole_list:
        if fnmatch.fnmatch (name, '*.c'):
            full_path = os.path.join (path, name)
            result.append (full_path)
    return result

def gen_testcases (file):
    result = []
    f = open ('./testcases')
    while True:
        line = f.readline ()
        if not line:
            break
        tup = line.split ('=>')
        if len (tup) == 2:
            testcase = (tup[0].strip (), tup[1].strip ())
            result.append (testcase)
        else:
            print ('testcase parsing error')
            sys.exit (0)
    return result

def execute (src, testcases):
    complile_command = 'gcc -o run ' + src
    cp = subprocess.Popen (complile_command, stdout = subprocess.PIPE, stderr = subprocess.PIPE, shell = True)
    out, err = cp.communicate ()
    if err:
        print ('compile error')
        return False
    for (testcase, result) in testcases:
        run_command = './run'
        rp = subprocess.Popen (run_command, stdout = subprocess.PIPE, stderr = subprocess.PIPE, stdin = subprocess.PIPE, shell = True)
        out, err = rp.communicate (input = (testcase + '\n').encode ())
        if err:
            print ('error while running')
            return False
        else:
            out = out.decode ().strip ()
            if result == out:
                pass
            else:
                print ('failed')
                print ('intput: ' + testcase)
                print ('expected output: ' + result)
                print ('program output: ' + out)
                return False
    return True

def main():
    path = os.path.dirname('./')
    srcs = find_src (path)
    testcases = gen_testcases ('./testcases')
    for src in srcs:
        print ('testing ' + src)
        if execute (src, testcases):
            print ('passed\n')
    remove_command = 'rm -f run'
    subprocess.Popen (remove_command, shell = True)

if __name__ == '__main__':
    if len (sys.argv) != 1:
        print ("Usage: python test_all.py")
    else:
        main ()
