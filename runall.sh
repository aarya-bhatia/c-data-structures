#!/bin/sh
for file in $(ls bin/*); do
	valgrind $file >/tmp/null 2>/tmp/null && echo $file: $?
done
