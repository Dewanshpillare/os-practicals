#!/bin/bash
while true
do
    # Display menu options
    echo -e "\n 1. Insert Record\n 2. Display Record\n 3. Search Record\n 4. Delete Record\n 5. Modify Record"
    
    # Prompt for user input
    echo -n "Enter your choice: "
    read ch

    # Use case statement to handle user choices
    case $ch in
        1) 
            # Insert Record
            echo -n "Enter employee id: "
            read eid
            echo -n "Enter employee name: "
            read ename
            echo -n "Enter employee phone no.: "
            read eph
            echo -n "Enter employee city: "
            read ecity
            echo "$eid\t$ename\t$eph\t$ecity" >> emp1.txt
            ;;
        2) 
            # Display Record
            cat emp1.txt
            ;;
        3) 
            # Search Record
            echo -n "Enter employee name to be searched: "
            read ename
            grep "$ename" emp1.txt
            ;;
        4) 
            # Delete Record
            echo -n "Enter employee name to be deleted: "
            read ename
            grep -v "$ename" emp1.txt >> temp.txt
            mv temp.txt emp1.txt
            ;;
        5) 
            # Modify Record
            echo -n "Enter employee name to modify: "
            read ename
            echo -n "Enter new name: "
            read name
            sed -i "s/$ename/$name/g" emp1.txt
            ;; 
        *) 
            # Handle invalid choices
            echo "Invalid choice. Please enter a number between 1 and 5."
            ;;
    esac
done
