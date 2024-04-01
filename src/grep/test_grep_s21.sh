#!/bin/bash

make s21_grep

#1 test for several -e flags
./s21_grep -e ':[1-100]' -e ^Lorem mega_test.txt > my_grep.txt
grep -e ':[1-100]' -e ^Lorem mega_test.txt > actual_grep.txt
diff actual_grep.txt my_grep.txt
if [ $? -eq 0 ]; then
      echo "Grep -e test passed!"
  else
      echo "Grep -e test failed!"
fi


#2 tests for -i flag
./s21_grep -i LOREME mega_test.txt > my_grep.txt
grep -i LOREME mega_test.txt > actual_grep.txt
diff actual_grep.txt my_grep.txt
if [ $? -eq 0 ]; then
      echo "Grep 1st -i test passed!"
  else
      echo "Grep 1st -i test failed!"
fi

./s21_grep -v 'j is 106 6a' mega_test.txt > my_grep.txt
grep -v 'j is 106 6a' mega_test.txt > actual_grep.txt
diff actual_grep.txt my_grep.txt
if [ $? -eq 0 ]; then
      echo "Grep 2nd -v test passed!"
  else
      echo "Grep 2nd -v test failed!"
fi

#3 test for -v flag
./s21_grep -c "char:1" mega_test.txt > my_grep.txt
grep -c "char:1" mega_test.txt > actual_grep.txt
diff actual_grep.txt my_grep.txt
if [ $? -eq 0 ]; then
      echo "Grep -c test passed!"
  else
      echo "Grep -c test failed!"
fi

#4 test for -l flag
./s21_grep -l "test test" mega_test.txt > my_grep.txt
grep -l "test test" mega_test.txt > actual_grep.txt
diff actual_grep.txt my_grep.txt
if [ $? -eq 0 ]; then
      echo "Grep -l test passed!"
  else
      echo "Grep -l test failed!"
fi

#5 test for -n flag
./s21_grep -n 'g' mega_test.txt > my_grep.txt
grep -n 'g' mega_test.txt > actual_grep.txt
diff actual_grep.txt my_grep.txt
if [ $? -eq 0 ]; then
      echo "Grep -n test passed!"
  else
      echo "Grep -n test failed!"
fi

rm -rf actual_grep.txt my_grep.txt
