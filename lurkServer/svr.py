from subprocess import call
import sys
while True:
	call(["./LurkServer", sys.argv[1]])