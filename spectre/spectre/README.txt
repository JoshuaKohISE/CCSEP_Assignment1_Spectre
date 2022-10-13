!!!!PLS COMPILE THE CODE IN A INTEL AND LINUX ENVIROMENT, AS THIS EXPLOIT IS PROCESSOR SPECIFIC AND THE COMMAND USED IN THE PROGRAM ARE ALL INTEL DEDICATED.!!!!

to run the vulnerable code

1. COMPILE THE CODE USE THE LINE gcc spectre.c -o spectre
2. use ./spectre to run the code 

*you may change the Key in the code with any number between 10 and 256 on line 59*
*may uncomment line to have a clear representation about the time taken to load the data from cache(line 72)"

to run the patched code

1. COMPILE THE CODE USE THE LINE "gcc spectre_patched.c -o patched"
2. use ./patched to run the code

 
*you may change the Key in the code with any number between 10 and 256 on line 68*
*may uncomment line to have a clear representation about the time taken to load the data from cache(line 77)"


the only difference between the two code is the cache is constanly being flush in the patched program. By doing so, it will ensure the no data is being left int the cache unattained.
but it comes with a very costly price. this method will significanly lower the efficiency of the processor.  