#! /bin/bash

gcc test$1.c -o test$1.exe && ./test$1.exe && rm test$1.exe
