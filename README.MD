# Requirements

  - g++ compiler
  - GNU Make

# Compilation

The code can be compiled using the provided makefile; simply type the command `make`.

After compiling the program, the executable file will appear; 
this file will be named `cpuScheduling`.

# Running the Program

The program, must be run with an input filename as 
the first command line argument. The program will **not** 
prompt the user for a filename.

The program can be executed as follows:
    `./cpuScheduling <input_file_name>`

where `<input_file_name>` is replaced by a .txt input file
containing CPU data in the format:

"Arrival time	CPU Burst length	Priority"

# Sample Execution & Output

When given the command:
    `./cpuScheduling Datafile1-txt.txt`

The output will be displayed on the console (terminal), and
the output will be stored in a .txt file named 
"cpu-output-data.txt"

The output is expected to be the following:
    ```
    FIFO Scheduling Statistics:
    Number of processes: 513
    Total elapsed time: 15182 units
    Throughput: 0.03 processes/unit time
    Average waiting time: 17.65 units
    Average turnaround time: 38.88 units
    Average response time: 17.65 units

    SJF Scheduling Statistics:
    Number of processes: 513
    Total elapsed time: 25408 units
    Throughput: 0.02 processes/unit time
    Average waiting time: 13868.99 units
    Average turnaround time: 13890.23 units
    Average response time: 13868.99 units

    Priority Scheduling Statistics:
    Number of processes: 513
    Total elapsed time: 15182 units
    Throughput: 0.03 processes/unit time
    Average waiting time: 17.22 units
    Average turnaround time: 38.45 units
    Average response time: 17.22 units
    ```

# Important Notes

 - "Datafile1-txt.txt" is the input file
 - "cpu-output-data.txt" is the output file

_____________________________________________________________________

The provided input .txt file (Datafile1-txt.txt) appears as follows:

```
Arrival time	CPU Burst length	Priority
10	22	1
68	12	6
98	34	8
148	28	10
192	3	3
223	8	3
266	18	2
268	14	10
268	30	4
296	10	7
354	6	3
375	2	8
377	31	2
406	10	4
457	21	9
469	1	10
529	9	6
559	12	5
581	39	1
...
...
...
15153	29	10
```

As you can see, the first line of Datafile1-txt.txt contains words. 
Therefore, the program **ignores** the first line of the .txt input file.

With that being said, if you use a different .txt file as input, other than 
Datafile1-txt.txt, please be advised that the program will ignore the 
first line of the input file.  

However, if you wish for the program to **not** ignore the first line of the input file,
navigate to the Process.cpp file, and comment out line 22.  

In Process.cpp, line 22 appears as follows:
    `getline(infile, ignoreFirstLine);  // Used to ignore the words in the input file`
