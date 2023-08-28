#!/bin/bash
filename = "Employee.txt"
echo "Select the option";
echo "1. Insert a record"
echo "2. Search"
echo "3. Display specific employee record"
echo "4. Delete the records"
echo "5. List the records"
echo "6. Sort record "
echo "7. Exit from menu "
echo -n "Enter your menu choice [1-6]: "

Insert()
{
	echo "Enter Employee Name: \c"
	read ename
        echo "Enter Employee id: \c"
        read eid
        echo "Enter Employee mobile number \c"
        read eno
        echo "$eid $ename $eno" >> Employee.txt
        echo "Record Inserted Successfully"
}

Search()
{
	echo "Enter the Employee ID"
	read eid

        flag=0
        for j in `cat Employee.txt`
        do
                    eno=$(echo "$j")
                    enm=$(echo "$j")
                    if [ $eid -eq $eno ]
                    then
                            flag=1
                            echo "Employee Name : $enm            "
                    fi
        done
        if [ $flag = 0 ]
        then
             echo "No Record Found"
        fi
}

Display()
{
	echo "Enter the Employee ID"
	read eid

        flag=0
        for j in `cat Employee.txt`
        do
                    eid1=$(echo "$j")                  
		    if [ $inp -eq $eid1 ]
		    then 
		    	enm1=$(echo "$j")
                    	eno1=$(echo "$j")  
                    	echo "Name: $enm1"
                    	echo "Employee id: $eid1"
                    	echo "Employee number: $eno1"
		    fi
        done
}

Delete()
{
	echo "Enter the Employee ID"
	read eid
	sed "/^$inp/d" Employee.txt
}

List()
{
	for j in `cat Employee.txt`
        	do
                    	eid1=$(echo "$j")                  
		    	enm1=$(echo "$j")
                    	eno1=$(echo "$j")  
                    	echo -n "Name: $enm1  "
                    	echo -n "Employee id: $eid1  "
                    	echo -n "Employee number: $eno1"
                    	echo ""
        done
}

Sort()
{
	sort -k Employee.txt
}
while true;
	do
		read choice
		case $choice in
			1)  Insert;;
			2)  Search;;
			3)  Display;;
			4)  Delete;;
			5)  List;;
			6)  Sort;;
			7)  echo "Exit"
      			    exit;;
			*) echo "invalid option";;

		esac
  	echo -n "Enter your menu choice [1-6]: "
done
