# Projekt no. 3 for the Data Structures course at Wrocław University of Science and Technology
## Authors:
- Adrian Goral
- Paulina Szulc

## Description
As part of the mini-projects, it is necessary to implement your own `Hash-Based Dictionaries` and conduct their research, which will mainly be based on measuring the time complexity of basic operations that can be performed on a given data structure.

# Compiling and running (Linux)

## Requirements
- `g++` compiler
- `ncurses` library
- `menu` library

To install the required libraries, you need to run the following command in the terminal:
```bash
sudo apt-get install libncurses5-dev libmenu-dev g++
```

## Compiling and running
In order to compile the program, you need to run the following command in the main directory of the project:
```bash
g++ -o main main.cpp -lncurses -lmenu -std=c++17
```
then you can run the program by executing the following command:
```bash
./main
```

moreover, the program [cpplint](https://github.com/cpplint/cpplint) was used to check the code style, you can run it by executing the following command:
```bash
cpplint <filename>
```
Make sure you have `cpplint` installed on your machine:
```bash
pip install cpplint
```


# PC Conducting research specification
The research was conducted on the following Virtual Machine:

- VMWare Workstation 16 Player
- Ubuntu 64-bit 22.04.4-desktop
- 2 CPU cores
- 12 GB RAM
