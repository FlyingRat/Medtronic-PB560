import os
import re
import sys
import logging
import subprocess
from optparse import OptionParser
from optparse import OptionGroup
import _winreg as wreg

TEMP_FILE = 'temp_test_result.txt'
OUTPUT_FILE = 'index.html'
DEFAULT_OUTPUT_DIR = 'auto_tu_results'
TU_OUTPUT_DIR = 'unit_tests'
METRICS_OUTPUT_DIR = 'metrics'
TU_PATH = 'tu'
SOURCES_PATH = 'src'
DEFAULT_METRICS_REQUIRED_LIST = 'NestedLevel Statements VG Total Comment1'
CODE_COVERAGE_FILE = r'Test.atc.txt'
REV_INFO_PATTERN = 'who comments branch revision'
PROJECT_CONVERT_LIST = {'PB520': 'LEGENDAIR_S2', 
                        'PB540': 'LEGENDAIR_US', 
                        'PB560': 'LEGENDAIR_XL2'}

TU_HEADER = os.path.join('scripts', 'auto_tu_templates', 'tu_header.html')
TU_FOOTER = os.path.join('scripts', 'auto_tu_templates', 'tu_footer.html')
METRICS_HEADER = os.path.join('scripts', 'auto_tu_templates', 'metrics_header.html')
METRICS_FOOTER = os.path.join('scripts', 'auto_tu_templates', 'metrics_footer.html')

LOGGER_LEVELS = {'debug': logging.DEBUG,
                'info': logging.INFO}

def html_table_add(l_c, content, html_table):
    if l_c is 'line':
        html_table.append('<tr><td>' + content + '</td></tr>\n')
    if l_c is 'column':
        line_list = list(html_table[len(html_table)-1].rpartition('</td>'))
        line_list.insert(len(line_list) - 1, '<td align="center">' + content + '</td>')
        html_table[len(html_table)-1] = ''.join(line_list)
    return html_table

def create_html_file(content, header, footer, output_dir, replacements):
    content.insert(0, open(header).read())
    for replacement in replacements:
        content[0] = content[0].replace(replacement[0], replacement[1])
    content.append(open(footer).read())
    html_result_file = open(os.path.join(output_dir, OUTPUT_FILE), 'w')
    html_result_file.writelines(content)
    html_result_file.close() 

def create_dir(directory):
    if not os.path.isdir(directory):
        os.mkdir(directory)
    return directory

def list_files(directory, files_extension, ignore_files_string, scope):
    result_files_list = []
    for root, dirs, files in os.walk(directory):
        for file in files:
            if (file.split('.')[-1] == files_extension\
            and (scope is 'all' or re.search(file.split('.')[0] + '\.', str(scope)))\
            and (not re.search(ignore_files_string, os.path.join(root, file))\
                or ignore_files_string == '')\
            and not re.search(file, str(result_files_list))):
                result_files_list.append(os.path.join(root, file))
    return result_files_list

def get_install_path(software_name):
    try:
        key = wreg.HKEY_LOCAL_MACHINE
        if software_name is 'rational':
            sub_key = "SOFTWARE\\Rational Software"
            k = wreg.OpenKey(key, sub_key)
            reg_entry = wreg.QueryValueEx(k, 'RSINSTALLDIR')
        elif software_name is 'tasking':
            i = 0
            k1 = wreg.OpenKey(key, "SOFTWARE\\TASKING")
            while not re.search('\ASW\d+', wreg.EnumKey(k1, i)):
                i += 1
            k2 = wreg.OpenKey(k1,wreg.EnumKey(k1,i))
            i = 0
            while not re.search('\Av', wreg.EnumKey(k2,i)):
                i += 1
            k3 = wreg.OpenKey(k2,wreg.EnumKey(k2,i)) 
            reg_entry = wreg.QueryValueEx(k3, 'InstallDir')
        return reg_entry[0]
    except:
        raise Exception("Couldn't read the registery key")

class AutoTuError(Exception):
    pass

def send_cmd(cmd, args):
    full_cmd = cmd
    for arg in args:
        full_cmd += ' ' + arg
    logging.debug('command : %s' %full_cmd)
    process = subprocess.Popen(full_cmd, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    result = process.communicate()
    logging.debug('output : %s' %str(result))
    logging.debug('return code : %s' %process.returncode)
    if (process.returncode and os.path.basename(cmd) != "attolpreproC") or process.returncode > 3:
        raise AutoTuError("Execution failed for instruction %s" %full_cmd)

def format_rev_info(rev_info_list):
    rev_info_string = ''
    if rev_info_list:
        for info_index in range(len(rev_info_list)):
            rev_info_string += '<h3>' + REV_INFO_PATTERN.split()[info_index] + ': ' + rev_info_list[info_index] +'</h3>\n'
    else:
        rev_info_string = '<h3>On demand test.</h3>'
    return rev_info_string

def print_metrics_file(metrics_file, metrics_files_list):
    metrics_name = os.path.splitext(re.search('\w+\.c',metrics_file).group())[0]
    logging.info(str(metrics_files_list.index(metrics_file) + 1) + ' / ' + str(len(metrics_files_list)) + ' : ' + metrics_name)

def run_metrics(project_path, scope, metrics_output_dir,project):
    sources_path = os.path.join(project_path,SOURCES_PATH)
    include_paths_list = list_dirs(sources_path)
    metrics_path = os.path.join(project_path,SOURCES_PATH)
    if not os.path.isdir(metrics_path):
        raise Exception("No source directory found in <project_directory>.")
    rational_path = get_install_path('rational')
    logging.info('METRICS:')
    metrics_files_list = list_files(metrics_path, 'c', '', scope)
    for metrics_file in metrics_files_list:
        arg_file = metrics_file
        atus_path = os.path.join(rational_path, 'TestRealTime', 'targets', 'PBXXX_CPU_Tasking_regf276e', 'ana', 'atus_c.def')
        std_define_option = '-STD_DEFINE="%s"' %atus_path
        define_option = '-define="_TASKING","%s"' %project 
        metrics_option = '-METRICS="%s"' %metrics_output_dir
        include_paths_metrics = ''
        for path in include_paths_list:
            include_paths_metrics += ',"' + path + '"'
        includes = '-incl="."' + include_paths_metrics
        try:
            send_cmd('attolstartC', (arg_file, std_define_option, includes, define_option, metrics_option))
        except AutoTuError, e:
            f = open(os.path.join(metrics_output_dir,os.path.basename(metrics_file)) + '.met', 'w')
            f.write('error')
            f.close()
        print_metrics_file(metrics_file, metrics_files_list)

def format_metrics_result(project_directory, metrics_output_dir, metric_required_list, rev_info, format):
    html_table = []
    metrics_file_list = list_files(metrics_output_dir, 'met', '', 'all')
    for metrics_file in metrics_file_list:
        html_table = html_table_add('line', os.path.splitext(os.path.basename(metrics_file))[0], html_table)
        metrics_lines = open(os.path.join(metrics_output_dir, metrics_file)).readlines()
        if metrics_lines[0] == 'error':
            html_table = html_table_add('column', '<font color="red">ERROR</font>', html_table)
        else:
            for metric_required in metric_required_list:
                value = 0
                for metric in metrics_lines:
                    if re.search(metric_required, metric):
                        value += float(re.search('(Value=")([\d\.]+)', metric).group(2))
                html_table = html_table_add('column', re.split('\.0\Z', str(value))[0], html_table)
        os.remove(os.path.join(metrics_output_dir, metrics_file))   
    rev_info_string = format_rev_info(rev_info)
    replacement_list = [('<rev_info>', rev_info_string)]
    create_html_file(html_table, 
                     os.path.join(project_directory, METRICS_HEADER), 
                     os.path.join(project_directory, METRICS_FOOTER),
                     metrics_output_dir, 
                     replacement_list)
 

def write_tu_name(tu_file, tu_files_list, test_result_file):
    tu_name = os.path.splitext(os.path.basename(tu_file))[0]
    output = str(tu_files_list.index(tu_file) + 1) + ' / ' + str(len(tu_files_list)) + ' : ' + tu_name
    test_result_file.write(output + '\n')
    return (output)
 
def write_tu_status(test_result_file):
    if os.path.isfile('TTest.rod'):
        if re.search('INCORRECT', open('TTest.rod', 'r').read()):
            status = 'FAIL'
        else:
            status = 'PASS'
    else:
        status = 'ERROR'
    test_result_file.write(status + '\n')
    return status

def print_tu_status(tu_name, tu_status): 
    dot_number = 45 - len(tu_name)
    logging.info(tu_name + dot_number * '.' + tu_status)
    
def code_coverage(tu_file):
    code_coverage_file = open(CODE_COVERAGE_FILE)
    coverage_string = ''
    code_coverage_values = re.finditer(r'(\d+\.\d+%)* (none)*', code_coverage_file.read())
    for value in code_coverage_values:
        if value.group(1):
            coverage_string += str(value.group(1)) + ' '
        if value.group(2):
            coverage_string += str(value.group(1)) + ' '
    return coverage_string.strip()
    
def write_code_coverage(tu_file, tu_status, test_result_file):
    if os.path.isfile(CODE_COVERAGE_FILE) and open(CODE_COVERAGE_FILE).read().strip() != '':
        code_coverage_result = code_coverage(tu_file)
    else:
        code_coverage_result = 'ERROR'
    test_result_file.write(code_coverage_result + '\n')
    
def get_include_paths(sources_path, start_separator, end_separator):
    include_paths_string = ''
    for root, dirs, files in os.walk(sources_path):
        for dir in dirs:
            if not re.search(r'\.', os.path.join(root,dir)):
                include_paths_string += start_separator + os.path.join(root,dir) + end_separator
    return include_paths_string

def list_dirs(sources_path):
    include_paths_list = []
    for root, dirs, files in os.walk(sources_path):
        for dir in dirs:
            if not re.search(r'\.', os.path.join(root,dir)):
                include_paths_list.append(os.path.join(root,dir))
    return include_paths_list

def get_matching_source(file, sources_files_list):
    for f in sources_files_list:
        if re.search(os.path.basename(file).split('.')[0], f):
            return f
    raise Exception("No source file for %s." %file)

def instrument_and_compile(c_file, compiled_file, include_paths_list, rational_path, tasking_path, project, mcdc):
    rational_bin_path = os.path.join(rational_path, 'TestRealTime', 'bin', 'intel', 'win32')
    gcc_exe_path = os.path.join('C:\\', 'MinGW', 'bin', 'gcc')
    tasking_exe_path = os.path.join(tasking_path, 'bin', 'cc166.exe')
    tasking_include_path = os.path.join(tasking_path, 'include')
    tdp_path = os.path.join(rational_path, 'TestRealTime', 'targets', 'PBXXX_CPU_Tasking_regf276e')
    include_specific_path = os.path.join('..','..','TU','Rational_TDP','Additional_files','INCLUDE_SPECIFIC')
    #preprocessing
    logging.debug('preprocessing of %s'%c_file)
    cmd = gcc_exe_path
    #cmd = os.path.join(tasking_path, 'bin', 'cc166')       
    arguments = r'-E -D_TESTRT -D_TASKING -D%s' %PROJECT_CONVERT_LIST[project] 
    include_paths_preprocess = '-I"' + include_specific_path + '" -I"' + os.path.join(tasking_path, 'include') + '" '
    for path in include_paths_list:
        include_paths_preprocess += '-I"' + path + '" '
    output_file = r'-o ' + os.path.splitext(os.path.basename(c_file))[0] + '.i'
    send_cmd(cmd, (arguments, include_paths_preprocess, c_file, output_file))
    #fixlines
    logging.debug('fixlines of %s'%c_file)
    cmd = os.path.join(rational_bin_path, 'fixlines')
    input_file = os.path.splitext(os.path.basename(c_file))[0] + r'.i'
    output_file = os.path.splitext(os.path.basename(c_file))[0] + r'_fix.i'
    send_cmd(cmd, (input_file, output_file))
    #instrumentation
    logging.debug('instrumentation of %s'%c_file)
    cmd = os.path.join(rational_bin_path, r'attolcc1')
    input_file = output_file
    output_file = os.path.splitext(os.path.basename(c_file))[0] + r'_aug.c'
    arguments = r'atct.def -proc=ret -block=logical -cond=modified'
    if mcdc:
        exclude_file = ''
    else:
        exclude_file = r'@stubs_rename.opt -exfile=' + c_file
    exclude_path = r'-noinstrdir="' + tdp_path + '"'
    send_cmd(cmd, (input_file, output_file,  arguments, exclude_file, exclude_path))
    #compilation
    logging.debug('compilation of %s'%c_file)
    cmd = tasking_exe_path
    include_paths_compil = ''
    for path in include_paths_list:
        include_paths_compil += '-Wc "-I' + path + '" '
    arguments = r'-c -Mh -tmp -mPR=0,4000'
    c_args = r'-Wc"-I'+ tasking_include_path + r'" -Wc-xd -Wc-Bhoeufmknladij  -Wc-Drom= -Wc-Dfar= -Wc-D_sof_=_sof -Wc-D_nop_=_nop -Wc-Dxhuge=huge -Wc-Dbit=char -Wc-D_srvwdt_=_srvwdt -Wc-Didata=iram -Wc-OB -Wc-znocustack -Wc-OT -Wc-zautobitastruct-4 -Wc-zautobita-0 -Wc-T0,0 -FSC -Wc-A1 -Wc-zvolatile_union -Wc-u -Wc-Ov -Wc-O2 -Wc-gf -Wc-newerr -Wc-s'
    asm_args = r'-WaPL(60) -WaPW(120) -WaTA(8) -WaWA(1) -WaSG -WaNOM166 -WaSN(regf276e.def) -WaEXTMAC'
    prepross_args = r'-WmDEF(_EXT,1) -WmDEF(_EXT2,0) -WmDEF(_EXT22,0) -WmDEF(_EXTMAC,1) -WmDEF(MODEL,HUGE) -WmDEF(_USRSTACK,0) -WmDEF(_SINGLE_FP,1) -WmDEF(NOBITCLEAR) -WmPR("*.mpl") -WmPL(60) -WmPW(120) -WmTA(8) -WmWA(1) -WmINC("' + tasking_include_path + '")'
    defines = r'-D"_TESTRT" -D"_TASKING" -D"%s"' %PROJECT_CONVERT_LIST[project]
    input_file = output_file
    output_file = r'-o ' + compiled_file
    try:
        send_cmd(cmd, ('-Wc-Hregf276e.h', arguments, c_args, asm_args,prepross_args, include_paths_compil,defines,input_file, output_file))
    except:
        send_cmd(cmd, (arguments, c_args, asm_args,prepross_args, include_paths_compil,defines,input_file, output_file))

def convert_ptu(tu_file, test_file, include_paths_list, rational_path, tasking_path, project):
    rational_bin_path = os.path.join(rational_path, 'TestRealTime', 'bin', 'intel', 'win32')
    tasking_include_path = os.path.join(tasking_path, 'include')
    include_specific_path = os.path.join('..','..','TU','Rational_TDP','Additional_files','INCLUDE_SPECIFIC')
    logging.debug('ptu to c convertion of %s'%tu_file)
    cmd = os.path.join(rational_bin_path, 'attolpreproC')        
    input_file = tu_file
    output_file = test_file
    atus_path = '-STD_DEFINE="' + os.path.join(rational_path, 'TestRealTime', 'targets', 'PBXXX_CPU_Tasking_regf276e', 'ana', 'atus_c.def') + '"'
    stub_arg = '-RENAME=stubs_rename.opt'
    defines = '-define=_TESTRT,_TASKING,%s' %PROJECT_CONVERT_LIST[project]
    arguments = '-NOSIMULATION -FAST'
    include_paths_test_compil = ''
    for path in include_paths_list:
        include_paths_test_compil += ',"' + path + '"'
    includes = '-incl=".","' + include_specific_path + '","' + tasking_include_path + '"' + include_paths_test_compil
    send_cmd(cmd, (input_file, output_file, atus_path, stub_arg, includes, defines, arguments))

def linker(input_files, linked_file, rational_path, tasking_path): 
    target_path = os.path.join(rational_path,'TestRealTime','targets')
    logging.debug('linking of %s'%input_files)
    tasking_exe_path = os.path.join(tasking_path, 'bin', 'cc166.exe')
    cmd = tasking_exe_path
    arguments = '-Mh -xd -Bhoeufmknladij -WlHEAPSIZE(2) -ieee -cf'
    input_lib_files = '"' + os.path.join(target_path,'_legendair_us.ilo') + '" "' + os.path.join(target_path,'TP.obj') + '" "' + os.path.join(target_path,'start.obj') + '"'
    input_file = ''
    for file in input_files:
        input_file += (file + ' ') 
    output_file = r'-o ' + linked_file
    send_cmd(cmd, (output_file, arguments, input_lib_files,input_file))

def run_program(linked_file, tasking_path):
    logging.debug('running program')
    cmd = os.path.join(tasking_path, 'bin', 'xfw166.exe')
    script_files = r'-p "' + os.path.join(tasking_path, '..', 'TestRT.cmd') + '"'
    config = r'-tcfg "' + os.path.join(tasking_path, 'etc', 'simf276e.cfg') + '"'
    send_cmd(cmd, (linked_file, script_files, config))
  
def generate_reports(code_coverage_report, test_report, rational_path, source_file):
    rational_bin_path = os.path.join(rational_path, 'TestRealTime', 'bin', 'intel', 'win32')
    #trace file splitting
    logging.debug('trace file splitting')
    cmd = os.path.join(rational_bin_path, 'atlsplit')
    trace_file = r'TTest.rio'
    result = send_cmd(cmd, [trace_file])
    #trace file rename
    logging.debug('trace file rename')
    os.rename('atltest.rio', 'TTest.rio')
    #code coverage report generation
    logging.debug('code coverage report generation')
    cmd = os.path.join(rational_bin_path, 'attolcov')
    input_file = os.path.splitext(os.path.basename(source_file))[0] + '.fdc'
    tio_file = r'attolcov.tio'
    output_file = r'-output="Test.atc.txt"'
    arguments = r'-su=c -cio="atu.cio"'
    send_cmd(cmd, (input_file, tio_file, output_file, arguments))
    #report generation
    logging.debug('report generation')
    cmd = os.path.join(rational_bin_path, 'attolpostpro')
    trace_name = r'TTest'
    report_file = r'TTest.rod'
    arguments = r'-VA=EVAL -cio="atu.cio"'
    send_cmd(cmd, (trace_name, report_file, arguments))
            
def run_tu(project_path, scope, project):
    test_result_file = open(TEMP_FILE, 'w')
    tu_path = os.path.join(project_path,TU_PATH)
    sources_path = os.path.join(project_path,SOURCES_PATH)
    if not os.path.isdir(tu_path):
        raise Exception("No tu directory found in <project_directory>.")
    logging.info('TU:')
    tu_files_list = list_files(tu_path, 'ptu', r'\\ALL_UNIT_TESTS\\|\\FET-ptu\\|\\ptu\\', scope)
    sources_files_list = list_files(sources_path, 'c', '', 'all')
    include_paths_list = list_dirs(sources_path)
    tasking_path = get_install_path('tasking')
    rational_path = get_install_path('rational')
    for tu_file in tu_files_list:
        cwd = os.getcwd()
        os.chdir(create_dir('tmp'))
        tu_name = write_tu_name(tu_file, tu_files_list, test_result_file)
        try:
            #instrument and compile source file
            source_file = get_matching_source(tu_file, sources_files_list)
            compiled_source = 'source.obj'
            instrument_and_compile(source_file, compiled_source, include_paths_list, rational_path, tasking_path, project, mcdc = True)
            #convert test file
            test_file = 'TTest.c'
            convert_ptu(tu_file, test_file, include_paths_list, rational_path, tasking_path, project)
            #instrument and compile test file
            compiled_test = 'TTest.obj'
            instrument_and_compile(test_file, compiled_test, include_paths_list, rational_path, tasking_path, project, mcdc = False)
            #linking
            linked_file = 'TTest.abs'
            linker([compiled_source, compiled_test], linked_file, rational_path, tasking_path)
            #run program
            run_program(linked_file, tasking_path)
            #generate reports
            code_coverage_report = 'Test.atc.txt'
            test_report = 'Test.rod'
            generate_reports(code_coverage_report, test_report, rational_path, source_file)
        except AutoTuError, e:
            pass
        #convert reports
        tu_status = write_tu_status(test_result_file)
        print_tu_status(tu_name, tu_status)
        write_code_coverage(tu_file, tu_status, test_result_file)
        #tmp cleaning
        os.chdir(cwd)
        for file in os.listdir('tmp'):
            os.remove(os.path.join('tmp', file))
        os.rmdir('tmp')
    test_result_file.close()
    return os.path.join(os.getcwd(), TEMP_FILE)

def get_test_result_lines(input_file):
    test_result_file = open(input_file)
    test_result_lines = test_result_file.readlines()
    test_result_file.close()
    #os.remove(input_file)
    return test_result_lines

def write_html_tu_status(tu_status, global_test_result, html_table):
    if re.search('PASS', tu_status):
        html_tu_status = '<font color="green">PASS</font>'
    elif re.search('FAIL', tu_status): 
        html_tu_status = '<font color="red">FAIL</font>'
        global_test_result = '<font color="red">FAIL</font>'
    elif re.search('ERROR', tu_status): 
        html_tu_status = '<font color="orange">ERROR</font>'
        if not re.search('FAIL', global_test_result):
            global_test_result = '<font color="orange">ERROR</font>'
    html_table = html_table_add('column', html_tu_status, html_table)
    return global_test_result

def write_html_tu_code_coverage(tu_code_coverage, min_code_coverage, html_table):
    if not re.search(r'ERROR', tu_code_coverage):
        for code_coverage in tu_code_coverage.strip().split(' '):
            if not re.search(r'None', code_coverage):
                if int(re.search(r'\w+', code_coverage).group()) < min_code_coverage:
                    min_code_coverage = int(re.search(r'\w+', code_coverage).group())
                if int(re.search(r'\w+', code_coverage).group()) < 100:
                    code_coverage = '<font color="red">' + code_coverage + '</font>'
            html_table = html_table_add('column', code_coverage, html_table)
    else:
        html_table = html_table_add('column', '<font color="orange">ERROR</font>', html_table)
    return min_code_coverage

def format_tu_result(project_directory, input_file, tu_output_directory, rev_info, format):
    global_test_result = '<font color="green">PASS</font>'
    html_table = []
    min_code_coverage = 100
    test_result_lines = get_test_result_lines(input_file)
    for test_nbr in range(len(test_result_lines) / 3):
        tu_name = test_result_lines[test_nbr * 3]
        html_table = html_table_add('line', tu_name, html_table)
        tu_status = test_result_lines[test_nbr * 3 + 1]
        global_test_result = write_html_tu_status(tu_status, global_test_result, html_table)
        tu_code_coverage = test_result_lines[test_nbr * 3 + 2]
        min_code_coverage = write_html_tu_code_coverage(tu_code_coverage, min_code_coverage, html_table)
    if min_code_coverage < 100:
        min_code_coverage = '<font color="red">' + str(min_code_coverage) + '%</font>'
    else:
        min_code_coverage = '<font color="green">' + str(min_code_coverage) + '%</font>'
    if len(test_result_lines) == 0:
        global_test_result = 'No test done'
        min_code_coverage = 'No test done'
    rev_info_string = format_rev_info(rev_info)
    replacement_list = [('<pass_fail_criteria>', global_test_result), 
    ('<code_coverage>', min_code_coverage), 
    ('<rev_info>', rev_info_string)]
    create_html_file(html_table, os.path.join(project_directory, TU_HEADER),
                     os.path.join(project_directory, TU_FOOTER),
                     tu_output_directory,
                     replacement_list)

def get_options():
    usage = "usage: %prog <project_directory> [options]"
    parser = OptionParser(usage=usage)
    parser.add_option("-s", "--scope",action="store", default='all',
                  metavar="FILE",help="files to run tests on: one of 'path to files list file' or 'all' [default: '%default' (if option is not spacified or invalid file name)]")
    parser.add_option("-l", "--metricslist",action="store", default=DEFAULT_METRICS_REQUIRED_LIST,
                  metavar="FILE",help="path to metrics to be calculeted list file [default: '%default']")
    parser.add_option("-o", "--outputdir",action="store", default='.', 
                  help=r"tests results output directory [default: '<current_directory>']")
    parser.add_option("-p", "--project",action="store", default='PB520', 
                  help=r"project name: one of 'PB520', 'PB540' or 'PB560' [default: 'PB520']")
    parser.add_option("-v", "--verbose",action="store", default='info', 
                  help=r"verbose level: one of 'info' or 'debug' [default: 'info']")
    group = OptionGroup(parser, "At least one of these options is mandatory")
    group.add_option("-u", "--unittest",action="store_true", default=False,
                  help="run unit tests")
    group.add_option("-m", "--metrics",action="store_true", default=False,
                  help="compute metrics")
    parser.add_option_group(group)
    return parser

def check_options(options, arg, parser):
    if (not options.unittest and not options.metrics):
        parser.print_help()  
        raise Exception("At least one of --unittest and --metrics options is mandatory.")
    if (options.metricslist is not DEFAULT_METRICS_REQUIRED_LIST and not os.path.isfile(options.metricslist)):
        parser.print_help()  
        raise Exception("Specified metrics list file is invalid.")
    if not PROJECT_CONVERT_LIST.get(options.project):
        raise Exception("Invalid project name.")
    if len(arg) != 1 :
        parser.print_help()  
        raise Exception("<project_directory> parameter is mandatory.")
    elif os.path.isdir(arg[0]) == False:
        parser.print_help()
        raise Exception("Invalid project directory")
    options.scope = options.scope.split(',')
    for s in options.scope:
        if not os.path.isfile(s):
            options.scope = 'all'


def create_output_directory(options, project_directory):
    output_directory = os.path.abspath(os.path.join(options.outputdir, DEFAULT_OUTPUT_DIR))
    return create_dir(output_directory)

def create_files_scope(options):
    files_scope = options.scope
    if options.scope is not 'all' and re.search('\.txt\Z', options.scope[0]):
            files_list_file = open(options.scope[0])
            files_scope = files_list_file.readlines()[0].lstrip(r"[{'files': ['").split(r"'], ")[0].split(r"', '")
            files_list_file.close()
    return files_scope
 
def create_rev_info(options):
    rev_info = options.scope
    rev_info_list = []
    if rev_info is not 'all' and re.search('\.txt\Z', options.scope[0]):
        rev_info_file = open(options.scope[0])
        rev_info_string = rev_info_file.readlines()[0].split(r"'], ")[1]
        for info in REV_INFO_PATTERN.split(' '):
            if re.search(r"('" + info + "': ')", rev_info_string):
                rev_info_list.append(re.search(r"('" + info + "': ')([\s\w/]*)", rev_info_string).group(2))
            else:
                rev_info_list.append('None')
        rev_info_file.close()
    return rev_info_list

def create_metrics_list(options):
    metrics_list = options.metricslist.split(' ')
    if options.metricslist is not DEFAULT_METRICS_REQUIRED_LIST:
        metrics_list_file = open(options.metricslist)
        metrics_list = files_list_file.readlines().split(' ')
        metrics_list_file.close()  
    return metrics_list
           
if __name__ == "__main__":
    parser = get_options()
    (options, arg) =parser.parse_args()
    check_options(options, arg, parser)
    level = LOGGER_LEVELS.get(options.verbose, logging.NOTSET)
    logging.basicConfig(level=level, format='%(message)s')
    project_directory = os.path.abspath(arg[0])
    output_directory = create_output_directory(options, project_directory)
    files_scope = create_files_scope(options)
    rev_info = create_rev_info(options)
##    if options.scope is not 'all':
##        os.remove(options.scope)
    metrics_list = create_metrics_list(options)
   
    if options.unittest:
        tu_output_dir = create_dir(os.path.join(output_directory, TU_OUTPUT_DIR))
        temp_file = run_tu(project_directory,files_scope, options.project)
        format_tu_result(project_directory, temp_file, tu_output_dir, rev_info, 'html')
        
    if options.metrics: 
        metrics_output_dir = create_dir(os.path.join(output_directory, METRICS_OUTPUT_DIR))
        run_metrics(project_directory, files_scope, metrics_output_dir, options.project)
        format_metrics_result(project_directory, metrics_output_dir, metrics_list, rev_info, 'html')
    
    exit(0)