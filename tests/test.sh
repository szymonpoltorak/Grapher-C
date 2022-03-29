#!/bin/bash

ok="echo OK!"
fail="echo FAILED!"

#no arguments
echo "--------------Testing no arguments--------------"
./grapher 2> temp
T=$?; printf "Test[1]: "; [[ $T -eq 226 ]] && $ok || $fail ; echo 

#no file
echo "-------------Testing not giving file------------"
./grapher -wm -file 2> temp
T=$?; printf "Test[2]: "; [[ $T -eq 225 ]] && $ok || $fail ; echo 

#multiple modes test
echo "----------Testing multiple modes given----------"
./grapher -wm -rm 2> temp
T=$?; printf "Test[3]: "; [[ $T -eq 230 ]] && $ok || $fail ; echo 

#extended flag without readmode
echo "------Testing extended flag with read mode------"
./grapher -wm -extended 2> temp
T=$?; printf "Test[4]: "; [[ $T -eq 229 ]] && $ok || $fail ; echo 

#columns equal to 0
echo "----------Testing columns with 0 value----------"
./grapher -wm -columns 0 2> temp
T=$?; printf "Test[5]: "; [[ $T -eq 233 ]] && $ok || $fail ; echo 

#rows in read mode
echo "----------Testing rows in read mode-------------"
./grapher -rm -rows 0 2> temp
T=$?; printf "Test[6]: "; [[ $T -eq 227 ]] && $ok || $fail ; echo 

#odd number of points
echo "---------Testing odd number of points-----------"
./grapher -rm -points 1,2,3 2> temp
T=$?; printf "Test[7]: "; [[ $T -eq 236 ]] && $ok || $fail ; echo 

#letters not numbers in points
echo "------------Testing letters as points-----------"
./grapher -rm -points a,b,c,d 2> temp
T=$?; printf "Test[8]: "; [[ $T -eq 236 ]] && $ok || $fail ; echo 

#higher start than end
echo "----------Testing start higher than end---------"
./grapher -wm -start 10 -end 3 2> temp
T=$?; printf "Test[9]: "; [[ $T -eq 234 ]] && $ok || $fail ; echo 

#end equal of 0
echo "-------------Testing end equal of 0-------------"
./grapher -wm -end 0 2> temp
T=$?; printf "Test[10]: "; [[ $T -eq 235 ]] && $ok || $fail ; echo 

#start is negative
echo "------------Testing start as negative-----------"
./grapher -wm -start -1 2> temp
T=$?; printf "Test[11]: "; [[ $T -eq 234 ]] && $ok || $fail ; echo 

#end declared in read mode
echo "-------Testing end declared in read mode--------"
./grapher -rm -start 10 2> temp
T=$?; printf "Test[12]: "; [[ $T -eq 227 ]] && $ok || $fail ; echo 

#start declared in read mode
echo "-----Testing start declared in read mode--------"
./grapher -rm -end 20 2> temp
T=$?; printf "Test[13]: "; [[ $T -eq 227 ]] && $ok || $fail ; echo 

#wage mode proper use
echo "---------Testing wage mode proper use----------"
./grapher -wm -file tests/data/data.test -start 10 -end 20 -rows 3 -columns 3 1>&2 2> temp
T=$?; printf "Test[14]: "; [[ $T -eq 0 ]] && $ok || $fail ; echo 

#edge mode proper use
echo "---------Testing edge mode proper use----------"
./grapher -em -file tests/data/data.test -start 0 -end 11 -rows 4 -columns 5 1>&2 2> temp
T=$?; printf "Test[15]: "; [[ $T -eq 0 ]] && $ok || $fail ; echo 

#random mode proper use
echo "---------Testing radnom mode proper use----------"
./grapher -rem -file tests/data/data.test -start 2 -end 14 -rows 6 -columns 8 1>&2 2> temp
T=$?; printf "Test[16]: "; [[ $T -eq 0 ]] && $ok || $fail ; echo 