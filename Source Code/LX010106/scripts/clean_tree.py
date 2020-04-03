import shutil
import os
import errno
import stat
import sys

# pierre.roth@covidien.com - 15/04/2010

def handleRemoveReadonly(func, path, exc):
    excvalue = exc[1]
    if func in (os.rmdir, os.remove) and excvalue.errno == errno.EACCES:
        os.chmod(path, stat.S_IRWXU| stat.S_IRWXG| stat.S_IRWXO) # 0777
        func(path)
    else:
        raise

def rm_full_tree(dir):

	print "Cleaning " + dir
	try:
		if os.path.isdir(dir) == True:
			shutil.rmtree(dir, ignore_errors=False, onerror=handleRemoveReadonly)
	except IOError, e:
		print "FAILED cleaning " + dir
		print >> sys.stderr, "Execution failed:", e
		exit(1)
	print "Cleaning " + dir + ": PASS"

if __name__ == "__main__":
   
    print sys.argv	
    rm_full_tree(sys.argv[1])    
    exit(0)