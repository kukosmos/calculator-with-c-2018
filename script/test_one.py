import os
import util

def main(lec, file):
    path = os.path.dirname('./')
    path = os.path.join(path, lec)
    src = os.path.join(path, file)
    testcases = util.gen_testcases(lec, './testcases')
    print('testing ' + src)
    if util.execute(src, testcases):
        print('passed\n')
    util.remove_target()
