#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
PATTERN1="ra"
PATTERN2="lol"
TEST_FILE="test.txt"
echo "" > log.txt

echo "Testing..."
for var in -e -i -v -c -l -n 
do
          TEST1="$var $PATTERN1 $TEST_FILE"
#          echo "$TEST1"
          ../s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt
done

# for var in -e -i -v -c -l -n -h -s -o
# do
#   for var2 in -e -i -v -c -l -n -h -s -o
#   do
#         if [ $var != $var2 ]
#         then
#           TEST1="$var $var2 $PATTERN1 $TEST_FILE"
# #          echo "$TEST1"
#           ../s21_grep $TEST1 > s21_grep.txt
#           grep $TEST1 > grep.txt
#           DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#           if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#             then
#               (( COUNTER_SUCCESS++ ))
#             else
#               echo "$TEST1" >> log.txt
#               (( COUNTER_FAIL++ ))
#           fi
#           rm s21_grep.txt grep.txt
#         fi
#   done
# done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"