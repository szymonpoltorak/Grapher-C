#!/bin/bash

#no arguments

echo "--------------Testing no arguments--------------"
./grapher 2> temp

t=$(echo $?)

if [[ $t -eq 226 ]]; then
    echo Test[1]: OK!
else
    echo Test[1]: FAILED!
fi
echo

#no file

echo "-------------Testing not giving file------------"
./grapher -wm -file 2> temp

t=$(echo $?)

if [[ $t -eq 225 ]]; then
    echo Test[2]: OK!
else
    echo Test[2]: FAILED!
fi
echo

#multiple modes test

echo "----------Testing multiple modes given----------"
./grapher -wm -rm 2> temp

t=$(echo $?)

if [[ $t -eq 230 ]]; then
    echo Test[3]: OK!
else
    echo Test[3]: FAILED!
fi
echo

#extended flag without readmode

echo "------Testing extended flag with read mode------"
./grapher -wm -extended 2> temp

t=$(echo $?)

if [[ $t -eq 229 ]]; then
    echo Test[4]: OK!
else
    echo Test[4]: FAILED!
fi
echo

#columns equal to 0

echo "----------Testing columns with 0 value----------"
./grapher -wm -columns 0 2> temp

t=$(echo $?)

if [[ $t -eq 233 ]]; then
    echo Test[5]: OK!
else
    echo Test[5]: FAILED!
fi
echo

#rows in read mode

echo "----------Testing rows in read mode-------------"
./grapher -rm -rows 0 2> temp

t=$(echo $?)

if [[ $t -eq 227 ]]; then
    echo Test[6]: OK!
else
    echo Test[6]: FAILED!
fi
echo

#odd number of points

echo "---------Testing odd number of points-----------"
./grapher -rm -points 1,2,3 2> temp

t=$(echo $?)

if [[ $t -eq 236 ]]; then
    echo Test[7]: OK!
else
    echo Test[7]: FAILED!
fi
echo

#letters not numbers in points

echo "------------Testing letters as points-----------"
./grapher -rm -points a,b,c,d 2> temp

t=$(echo $?)

if [[ $t -eq 236 ]]; then
    echo Test[8]: OK!
else
    echo Test[8]: FAILED!
fi
echo

#higher start than end

echo "----------Testing start higher than end---------"
./grapher -wm -start 10 -end 3 2> temp

t=$(echo $?)

if [[ $t -eq 234 ]]; then
    echo Test[9]: OK!
else
    echo Test[9]: FAILED!
fi
echo

#end equal of 0

echo "-------------Testing end equal of 0-------------"
./grapher -wm -end 0 2> temp

t=$(echo $?)

if [[ $t -eq 234 ]]; then
    echo Test[10]: OK!
else
    echo Test[10]: FAILED!
fi
echo

#start is negative

echo "------------Testing start as negative-----------"
./grapher -wm -start -1 2> temp

t=$(echo $?)

if [[ $t -eq 234 ]]; then
    echo Test[11]: OK!
else
    echo Test[11]: FAILED!
fi
echo

#end declared in read mode

echo "-------Testing end declared in read mode--------"
./grapher -rm -start 10 2> temp

t=$(echo $?)

if [[ $t -eq 227 ]]; then
    echo Test[12]: OK!
else
    echo Test[12]: FAILED!
fi
echo

#start declared in read mode

echo "-----Testing start declared in read mode--------"
./grapher -rm -end 20 2> temp

t=$(echo $?)

if [[ $t -eq 227 ]]; then
    echo Test[13]: OK!
else
    echo Test[13]: FAILED!
fi
echo

#wage mode proper use

echo "---------Testing wage mode proper use----------"
./grapher -wm -file tests/data/data.test -start 10 -end 20 -rows 3 -columns 3 1>&2 2> temp

t=$(echo $?)

if [[ $t -eq 0 ]]; then
    echo Test[14]: OK!
else
    echo Test[14]: FAILED!
fi
echo

#edge mode proper use

echo "---------Testing edge mode proper use----------"
./grapher -em -file tests/data/data.test -start 0 -end 11 -rows 4 -columns 5 1>&2 2> temp

t=$(echo $?)

if [[ $t -eq 0 ]]; then
    echo Test[15]: OK!
else
    echo Test[15]: FAILED!
fi
echo

#random mode proper use

echo "---------Testing radnom mode proper use----------"
./grapher -rem -file tests/data/data.test -start 2 -end 14 -rows 6 -columns 8 1>&2 2> temp

t=$(echo $?)

if [[ $t -eq 0 ]]; then
    echo Test[16]: OK!
else
    echo Test[16]: FAILED!
fi
echo