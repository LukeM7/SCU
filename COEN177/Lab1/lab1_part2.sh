me: Luke Manzitto
# Date: 9/24/20
# Title: Lab1 - Task
# Description: This program computes the HOME,USER,PATH,PWD, and current process id of the program. 
# It then checks a whether the current user matches the authorized one to run the rest of the script.
# If so it then allows the user to enter the radius of an arbitrary circle and will compute and print the area. The user can do this as much as they want.

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
	echo "Enter radius of the circle"
	read radius
	PI=3.1415
	area=`echo "$PI * $radius * $radius" | bc`
	echo "The area of the circle is $area"

	echo "Would you like to repeat for another circle [Yes/No]?"
	read response
done
