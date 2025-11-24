#!/bin/bash

echo "--- Small Numbers ---"
./rush-02 0
./rush-02 1
./rush-02 42
./rush-02 100
./rush-02 123
./rush-02 999

echo -e "\n--- Medium Numbers ---"
./rush-02 1000
./rush-02 2023
./rush-02 100000
./rush-02 123456

echo -e "\n--- Large Numbers ---"
./rush-02 1000000
./rush-02 123456789
./rush-02 1000000000
./rush-02 1234567890123456789

echo -e "\n--- Error Cases ---"
./rush-02 -1
./rush-02 abc
./rush-02
