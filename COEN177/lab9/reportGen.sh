#!\bin\bash

echo "Step 2: " >> lab9.txt
echo "" >> lab9.txt

for file in file1.txt file2.txt file3.txt file4.txt
do
    echo "Step2 $file" >> lab9.txt
    (time ./step2 $file) 2>> lab9.txt
    echo " " >> lab9.txt
done

echo "" >> lab9.txt
echo "Step 3: " >> lab9.txt
echo "" >> lab9.txt

for file in file1.txt file2.txt file3.txt file4.txt
do
    for buffer in 100 1000 10000 100000
    do
        echo "Step3 $file $buffer" >> lab9.txt
        (time ./step3 $file $buffer) 2>> lab9.txt
        echo " " >> lab9.txt
    done
done

echo "" >> lab9.txt
echo "Step 4: " >> lab9.txt
echo "" >> lab9.txt

for file in file1.txt file2.txt file3.txt file4.txt
do
    for buffer in 100 1000 10000 100000
    do
        echo "Step4 $file $buffer" >> lab9.txt
        (time ./step4 $file $buffer) 2>> lab9.txt
        echo " " >> lab9.txt
    done
done

echo "" >> lab9.txt
echo "Step 5: " >> lab9.txt
echo "" >> lab9.txt

for file in file1.txt file2.txt file3.txt file4.txt
do
    for buffer in 100 1000 10000 100000
    do
        for thread in 2 8 32 64
        do
            echo "Step5 $file $buffer $thread" >> lab9.txt
            (time ./step5 $file $buffer $thread) 2>> lab9.txt
            echo " " >> lab9.txt
        done
    done
done