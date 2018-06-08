import os
import subprocess
from script import util

def main(lec, sol):
    path = os.path.dirname('./')
    test_path = os.path.join(path, 'testcases')
    lec_path = os.path.join(path, lec)
    sol_file = os.path.join(lec_path, sol)
    sol_list_file = os.path.join(lec_path, 'solution.list')
    testcases = util.find_testcases(test_path)
    compile_command = 'gcc -o run -w ' + sol_file
    subprocess.Popen(compile_command, shell = True)
    f = open(sol_list_file, 'w')
    for testcase in testcases:
        run_command = './run ' + testcase
        rp = subprocess.Popen(run_command, stdout = subprocess.PIPE, stderr = subprocess.PIPE, shell = True)
        out, err = rp.communicate()
        out = out.decode().strip()
        input_line = 'input: ' + testcase + '\n'
        output_line = 'output: ' + out + '\n'
        f.write(input_line)
        f.write(output_line)
    f.close()
    rm_command = 'rm -f run'
    subprocess.Popen(rm_command, shell = True)