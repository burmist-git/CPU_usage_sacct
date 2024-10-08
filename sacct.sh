#!/bin/bash

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -g : get data"
    echo " [0] -t : get time"
    echo " [0] -h : print help"
}

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-g" ]; then
	sacct -X --user=burmistr --starttime=2023-10-01 --endtime=2024-10-01 --format=JobID,AllocCPUs,Elapsed > sacct_output.csv
	grep -v - sacct_output.csv > sacct_output_clean.csv
    elif [ "$1" = "-t" ]; then
	python sacct.py
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi
