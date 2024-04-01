#!/bin/bash

make s21_cat

# Common tests for all the flags
for i in -b -e -n -s -t
do
  ./s21_cat $i test_super_mega.txt > my_cat.txt
  cat $i test_super_mega.txt > actual_cat.txt
  diff actual_cat.txt my_cat.txt
  if [ $? -eq 0 ]; then
      echo "$i Cat test passed!"
  else
      echo "$i Cat test failed!"
  fi
done

rm -rf actual_cat.txt my_cat.txt out