import os
import fnmatch
import sys
import subprocess

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
        print (complile_command)    
        print ('compile error')
        return False
    for (testcase, result) in testcases:
        run_command = './run'
        rp = subprocess.Popen (run_command, stdout = subprocess.PIPE, stderr = subprocess.PIPE, stdin = subprocess.PIPE, shell = True)
        out, err = rp.communicate (input = testcase + '\n')
        if err:
            print ('error while running')
            return False
        else:
            out = out.strip ()
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
    src = sys.argv [1]
    testcases = gen_testcases ('./testcases')
    print ('testing ' + src)
    if execute (src, testcases):
        print ('passed\n')
    remove_command = 'rm -f run'
    subprocess.Popen (remove_command, shell = True)

if __name__ == '__main__':
    if len (sys.argv) != 2:
        print ("Usage: python test_one.py <.c file>")
    else:
        main ()
