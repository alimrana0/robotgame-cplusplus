#!/usr/bin/env python

import argparse, json, os, platform, shutil, subprocess, sys, threading



if sys.version_info.major != 3:
    print('ERROR: not using Python 3')
    sys.exit(-1)



VERSION = 1
IS_MACOS = platform.system() == 'Darwin'



print('CS3520 testing script version %d' % VERSION)

parser = argparse.ArgumentParser()
parser.add_argument('--tested-dir', help='tested implementation directory (default .)')
parser.add_argument('--ref-dir', help='reference implementation directory (default ref)')
parser.add_argument('--suite', help='suite to run (default all)')
args = parser.parse_args()

tested_dir = os.path.abspath('.') if not args.tested_dir else os.path.abspath(args.tested_dir)
ref_dir = os.path.abspath('ref') if not args.ref_dir else os.path.abspath(args.ref_dir)
runsuite = None if not args.suite else args.suite

specfile = ref_dir + '/tests.json'



if not os.path.exists(ref_dir):
    print('ERROR: ref directory %s not found' % ref_dir)
    sys.exit(-1)

if not os.path.exists(tested_dir):
    print('ERROR: tested directory %s not found' % tested_dir)
    sys.exit(-1)

if not os.path.exists(specfile):
    print('ERROR: unable to find test spec %s' % specfile)
    sys.exit(-1)



spec = json.load(open(specfile))

logfile = open('test.log', 'w')

os.chdir(tested_dir)



def runcmd(name, cmd, input=None):
    global logfile

    logfile.write('----- running ' + name + ': ' + ' '.join(cmd) + '\n')

    proc = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, encoding='utf-8')
    timer = threading.Timer(10, proc.kill)

    try:
        timer.start()
        stdout, stderr = '', ''
        stdout, stderr = proc.communicate(input)
    finally:
        timer.cancel()


    if len(stdout) > 4096:
        stdout = stdout[:4096] + '\n[output truncated due to length]\n'

    stdout_lines = stdout.split('\n')
    stdout_lines_filtered = []
    for stdout_line in stdout_lines:
        if 'PR_SET_PTRACER' in stdout_line:
            continue
        if 'dsymutil' in stdout_line:
            continue
        stdout_lines_filtered.append(stdout_line)

    stdout = '\n'.join(stdout_lines_filtered)
    if len(stdout) == 0 or stdout[-1] != '\n':
        stdout = stdout + '\n[output does not end in newline]\n'

    logfile.write(stdout)
    logfile.write('----- returncode: ' + str(proc.returncode) + '\n')

    return proc.returncode, stdout



suites = spec['suites']

for suite in suites:
    suite_name = suite['name']

    if runsuite != None and suite_name != runsuite:
        continue

    if 'program' in suite:
        suite_program = suite['program']
    else:
        suite_program = None

    suite_cases = suite['cases']

    if 'valgrind' in suite and suite['valgrind']:
        suite_valgrind = True
    else:
        suite_valgrind = False



    logfile.write('***** testing suite ' + suite_name + '\n\n')

    num_passed = 0

    for tt, case in enumerate(suite_cases):
        logfile.write('===== testing case ' + str(tt) + '\n\n')

        if 'program' in case:
            case_program = case['program']
        else:
            case_program = suite_program

        if case_program == None:
            print('ERROR: spec does not define program for case.')
            sys.exit(-1)

        if 'input' in case:
            case_input = case['input']
            case_input = '\n'.join(case_input) + '\n'
        else:
            case_input = '\n'



        ref_program = ref_dir + '/' + case_program

        if IS_MACOS:
            ref_program = ref_program + '-macos'
        else:
            ref_program = ref_program + '-linux'

        if not os.path.exists(ref_program):
            print('ERROR: cannot find reference program %s .' % ref_program)
            sys.exit(-1)



        if os.path.exists(case_program):
            os.unlink(case_program)

        build_result, _ = runcmd('build', ['make', case_program])

        if build_result != 0:
            logfile.write('----- program %s does not compile\n' % case_program)
            logfile.write('----- test failed\n')

        else:
            logfile.write('----- input\n')
            logfile.write(case_input)

            if suite_valgrind:
                tested_cmd = ['valgrind', '--quiet', '--leak-check=yes', './' + case_program]
            else:
                tested_cmd = ['./' + case_program]

            ref_cmd = [ref_program]

            _, tested_output = runcmd('tested implementation', tested_cmd, case_input)
            _, ref_output = runcmd('reference implementation', ref_cmd, case_input)

            if tested_output == ref_output:
                num_passed += 1
                logfile.write('----- output matches\n')
                logfile.write('----- test passed\n')
            else:
                logfile.write('----- output does not match\n')
                logfile.write('----- test failed\n')
        logfile.write('\n\n\n')

    logfile.write('\n\n')

    if num_passed == len(suite_cases):
        amount = 'all'
    elif num_passed > max(1, len(suite_cases) / 2):
        amount = 'most'
    elif num_passed > max(1, len(suite_cases) / 4):
        amount = 'some'
    elif num_passed > 0:
        amount = 'any'
    else:
        amount = 'none'

    print('Suite %s: %s (%d/%d) passed.' % (suite_name, amount, num_passed, len(suite_cases)))
