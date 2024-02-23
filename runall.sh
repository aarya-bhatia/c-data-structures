#!/bin/sh
if ! make; then
	echo 'make error'
fi
for file in $(ls bin/*); do
	if valgrind $file 2>/tmp/null; then
		echo $file: pass
	else
		echo $file: fail
	fi
done
