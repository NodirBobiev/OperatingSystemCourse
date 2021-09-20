#!/bin/bash
filename="file.txt"
filelock="file.lock"
if ln $filename $filelock;
then
	echo 'File Locked successfully'
	number=0
	while read x;
	do
		number=$x
	done < $filename
	let "number+=1"
	echo "$number" >> $filename
	sleep 5
	rm $filelock
else
	echo '***ERROR:Cannot use the file!'
fi

