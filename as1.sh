#!/bin/sh



create() {



	echo "Enter Address Book Name: "

	read adname

	

	if [ -e $adname ]; then

		echo "File Already Exists"

	else

		touch $adname

		echo "Address Book Created"

	fi

}



display() {



	echo "Enter Address Book Name: "

	read adname

	

	if [ -e $adname ]; then

	 	cat $adname

	 	echo "File Opened Successfully"

	else

		echo "File not found"

	fi



}



insert() {



	echo "Enter Address Book Name: "

	read adname

	

	if [ -e $adname ]; then

		echo "Enter Email: "

		read email

		len=`cat $adname | grep $email | wc -w`

		

		if [ $len -gt 0 ]; then

			echo "Email Already Exists"

		else

			echo "Enter FName,LName,Mob"

			read fname lname mob

			

			record=`echo $fname $lname $email $mob`

			echo $record >> $adname

			echo "Record Inserted Successfully"

		fi

	else

		echo "File does not Exist"

	fi

			

}



update() {



	echo "Enter Address Book Name: "

	read adname

	

	res=`ls | grep $adname | wc -w`

	if [ $res -gt 0 ]; then

		echo "Enter Email: "

		read email

		len=`cat $adname | grep $email | wc -w`

		if [ $len -gt 0 ]; then

			

			echo "Enter New FName,LName,Mob"

			read fname lname mob

			

			oldrecord=`cat $adname | grep $email`

			newrecord=`echo $fname $lname $email $mob`

			

			echo ""

			echo "Newrecord: $newrecord"

			echo "Oldrecord: $oldrecord"

			echo ""

			

			sed -i s/"$oldrecord"/"$newrecord"/g $adname

			echo "Record Updated Successfully"

		

		else

			echo "Email Not Found"

		fi

	else

		echo "File Does Not Exist"

	fi

}



delete() {



	echo "Enter Address Book Name: "

	read adname

	

	res=`ls | grep $adname | wc -w`

	if [ $res -gt 0 ]; then

	

		echo "Enter Email: "

		read email

		len=`cat $adname | grep $email | wc -w`

		if [ $len -gt 0 ]; then

			

			oldrecord=`cat $adname | grep $email`

			

			sed -i s/"$oldrecord"//g $adname

			sed -i /^$/d $adname

			echo "Record Deleted Successfully"

		else

			echo "Email Not Found"

		fi

	else

		echo "File Does Not Exist"

	fi

}



while [ true ]

do

	echo "Menu Driven"

	echo "1) Create Address Book"

	echo "2) Display Address Book"

	echo "3) Insert Records"

	echo "4) Modify Records"

	echo "5) Delete Records"

	echo "6) Exiting the Program"

	

	echo "Enter Choice: "

	read choice

	

	case $choice in

		1) create ;;

		2) display ;;

		3) insert ;;

		4) update ;;

		5) delete ;;

		6) exit ;;

		*) "invalid choice" ;;

		

	esac

	

done