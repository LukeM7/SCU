# Name: Luke Manzitto
# Date: 9/24/20
# Title: Lab1 - Task
# Description: This program computes the HOME,USER,PATH,PWD, and current process id of the program. 
# It then checks a whether the current user matches the authorized one to run the rest of the script.
# If so it then allows the user to enter the length and width of an arbitrary rectangle and will compute and print the area. The user can do this as much as they want.

#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$="$$

user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers logged on."
if [ $user = "lmanzitt" ]
then
	echo "Now you can proceed"
else
	echo "Check who logged in!"
	exit 1
fi

response="Yes"
while [ $response != "No" ]
do
	echo "Enter height of rectangle"
	read height
	echo "Enter width of rectangle"
	read width
	area=`expr $height \* $width`
	echo "The area of the rectangle is $area"

	echo "Would you like to repeat for another rectangle [Yes/No]?"
	read response
done

