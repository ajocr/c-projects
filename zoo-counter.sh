#!/bin/bash

#Maame Adwoa Ocran
#Assignment 1- Count the zoo

bear_sum=0
dromedary_sum=0
aardvark_sum=0
genet_sum=0
lemur_sum=0
startDir="*"
metricFile=".KS_Dir"
animal=""

#argument verification
if [ $# -lt 1 ]; then
	echo "Enter measurement"
	exit 1
fi

#function to tally the animals in a specified directory
function tally () {
	#tally the animals
	for i in $1; do
		if [ -f "$i" ]; then
			if [ "$i" == "$metricFile" ]; then
				if [ "$animal" == "bear" ]; then
					if grep -q "bear" "$i"; then
						bear_sum=$(( bear_sum + $(grep "bear" "$i" | tr -s " " | cut -d " " -f 2)))
					else
						bear_sum=$(( bear_sum + 0 ))
                                	fi
				elif [ "$animal" == "dromedary" ]; then
					if grep -q "dromedary" "$i"; then
						dromedary_sum=$(( dromedary_sum + $(( $(grep "dromedary" "$i" | tr -s " " | cut -d " " -f 2)))))
                                        else
                                                dromedary_sum=$(( dromedary_sum + 0 ))
                                        fi
                        	elif [ "$animal" == "aardvark" ]; then
					if grep -q "aardvark" "$i"; then
                                                aardvark_sum=$(( aardvark_sum + $(grep "aardvark" "$i" | tr -s " " | cut -d " " -f 2)))
                                        else
                                                aardvark_sum=$(( aardvark_sum + 0 ))
                                        fi
				elif [ "$animal" == "genet" ]; then
                        	        if grep -q "genet" "$i"; then
                                                genet_sum=$(( genet_sum + $(grep "genet" "$i" | tr -s " " | cut -d " " -f 2)))
                                        else
                                                genet_sum=$(( genet_sum + 0 ))
                                        fi
                        	elif [ "$animal" == "lemur" ]; then
					if grep -q "lemur" "$i"; then
                                                lemur_sum=$(( lemur_sum + $(grep "lemur" "$i" | tr -s " " | cut -d " " -f 2)))
                                        else
                                                lemur_sum=$(( lemur_sum + 0 ))
                                        fi
                        	fi
      			fi
		fi
done
}

#function to traverse through subdirectories and count animals
function traverse {
	origin=$startDir
	for j in $origin; do
		tally "$j"
		 #subdirectory check
                if [ -d "$j" ]; then
                        currDir="$j"/
			echo "$currDir"
                        cd "$currDir" && traverse
			cd ".."
		
	
                fi
	done
}

#output function: formatting, etc
function output {
	if [ "$animal" == "bear" ]; then
		echo "bear $bear_sum"
	elif [ "$animal" == "dromedary" ]; then
                echo "dromedary $dromedary_sum"
	elif [ "$animal" == "aardvark" ]; then
                echo "aardvark $aardvark_sum"
	elif [ "$animal" == "genet" ]; then
                echo "genet $genet_sum"
	elif [ "$animal" == "lemur" ]; then
                echo "lemur $lemur_sum"
	fi	
}

#main: argument validation and prompts
if [ $# -eq 1 ]; then
	if [ "$1" == "bear" ] || [ "$1" == "dromedary" ] || [ "$1" == "aardvark" ] || [ "$1" == "genet" ] || [ "$1" == "lemur" ]; then
		animal="$1"
		traverse
		output
	else
		echo "Invalid Metric"
	fi
elif [ $# -eq 2 ]; then
	if [ -d "$1" ]; then
		startDir="$1"
		traverse
		output
	else
		echo "Invalid Directory"
	fi
	if [ "$2" == "bear" ] || [ "$2" == "dromedary" ] || [ "$2" == "aardvark" ] || [ "$2" == "genet" ] || [ "$2" == "lemur" ]; then
                animal="$2"
                traverse
                output
        else
                echo "Invalid Metric"
        fi
elif [ $# -eq 3 ]; then
	if [ "$1" == "-f" ]; then
		metricFile="$2"
		traverse
		output
	else
		echo "Invalid first argument"
	fi
	if [ "$3" == "bear" ] || [ "$3" == "dromedary" ] || [ "$3" == "aardvark" ] || [ "$3" == "genet" ] || [ "$3" == "lemur" ]; then
                animal="$3"
                traverse
                output
        else
                echo "Invalid Metric"
        fi
elif [ $# -eq 4 ]; then
	if [ "$1" == "-f" ]; then
                metricFile="$2"
                traverse
                output
        else
                echo "Invalid first argument"
	fi
	if [ -d "$3" ]; then
                startDir="$3"
                traverse
                output
        else
                echo "Invalid Directory"
        fi
	if [ "$4" == "bear" ] || [ "$4" == "dromedary" ] || [ "$4" == "aardvark" ] || [ "$4" == "genet" ] || [ "$4" == "lemur" ]; then
                animal="$4"
                traverse
                output
        else
                echo "Invalid Metric"
        fi
fi
