#!/bin/bash

try() {
    expected="$1"
    input="$2"

    ./olivCC "$input" > tmp.s
    gcc -o tmp tmp.s
    ./tmp
    actual="$?"

    if [ "$actual" = "$expected" ]; then
	echo "$input => $actual"
    else
	echo "$expected expected, but got $actual"
	exit 1
    fi

}

try 0 0
try 42 42
try 21 '5+20-4'
try 0 '1+2+3+4+5+6+7+8+9+10-55'
try 111 '1+(10*11)'
try 7 '1+4/2*3'
try 16 '(42+240)/141*8'
try 44 '(2+4)*(-1)+50'
try 6 '-3*-2'
try 1 '1*(-5+6)'



echo OK
