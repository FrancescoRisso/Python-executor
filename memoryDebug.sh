#!/bin/bash
clear && gcc -g -Og -Wunused-result *.c -o "valgrindDebug.exe" &&  valgrind --leak-check=full ./valgrindDebug.exe && rm  ./valgrindDebug.exe
