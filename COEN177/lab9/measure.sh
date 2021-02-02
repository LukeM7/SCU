#!/bin/bash

for file in file1.txt file2.txt file3.txt file4.txt
do
	for buffer in 100 1000 10000 100000
	do
		echo "Step2 $file $buffer"
		time ./step2 $file $buffer
		echo " "
		echo
		echo "Step3 $file $buffer"
		time ./step3 $file $buffer
		echo " "
		echo
		echo "Step4 $file $buffer"
		time ./step4 $file $buffer
		echo " "
		echo
		for thread in 2 8 32 64
		do
			echo "Step5 $file $buffer $thread"
			time ./step5 $file $buffer $thread
			echo " "
			echo
		done
	done
done
