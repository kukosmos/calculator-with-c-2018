import os
import util

def main(lec):
    path = os.path.dirname('./')
    path = os.path.join(path, lec)
    srcs = util.find_srcs(path)
    testcases = util.gen_testcases(lec, './testcases')
    for src in srcs:
        print('testing ' + src)
        if util.execute(src, testcases):
            print('passed\n')
    util.remove_target()
