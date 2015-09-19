# RFID-based-access-control-system
  An example RFID based access control system that i completed during my 3rd year of Engineering
  
## Overview 
  A RFID is similar to the NFC tags that are now present in almost all of the modern cellphones.Using RFID its possible to uniquely identify an item.
  
  As I was studying my bachelor degree,i was introduced to micro controller(8051) and i used 8051 micro controller to build an RFID based access control system.
  
  In this project,the user identifies himself/herself using a RFID tag. The RFID reader reads the tag and checks if a particular tag is one of the valid tag, and then opens the the door.The details of the user i.e the tag id and the time is stored into the EEPROM(24C512). The time keeping is done by RTC (DS1307) which is battery backed so that we keep track of time during a power shutdown too. Its possible to upload the data to the PC using RS232.

## Hardware
  
  Below is a block level diagram of the RFID based access control system

        		    +-----------------------+                  
                	|       16x2 LCD        |                  
                	|       JHD672a         |                  
                	+----------+------------+                  
                    	       |                               
        	        +----------+------------+                  
    		        |                       |                  
            		|                       |                  
           			|                       |
    +-----------+   |                       |   +-------------+
    |           |   |                       |   |             |
    | DS1307    +---+       89S52           +---+  RFID Reader|
    |   RTC     |   |   Micro controller    |   |             |
    |           |   |                       |   |             |
    +-----------+   |                       |   +-------------+
    				|                       |                  
            		|                       |   +-------------+
    +-----------+   |                       |   |             |
    |           |   |                       +---+    PC       |
    |  24C512   |   |                       |   |             |
    |  EEPROM   +---+                       |   +-------------+
    +-----------+   |                       |                  
    	            |                       |                  
        	        +-----------+-----------+                  
            	                |                              
                	+-----------+----------+                                                         
               		|                      |                  
                 	|    Matrix Keyboard   |                  
                 	|                      |                  
                 	+----------------------+                  

### Micro Controller (89s52)
  The micro controller that was chosen for this project was 89s52. The main reason for choosing this micro controller was because i had a paper in 8051 micro contoller and its better to use something you know.The good thing about 89s512 is that its programmable using ISP as its uses flash.

### RTC (DS1307)
  RTC stands for Real Time Clock.Though its possible to have the micro controller to track time, its hard to keep track of date, time and year. Also when the system loses power, someone has to reset the time. Its too choatic. A simpler solution is to use a RTC DS1307.It keeps track of time and has the option of attaching a backup power supply so  even when the main system power is down, DS1307 keeps runnning. DS1307 is connected to the micro controller via I2C bus.

### EEPROM (24C512)
  The micro controller has limited memory 128 bytes of RAM. In order to store all the data so that it can be uploaded to the PC after some time, an EEPROM is used. 24C512 is connected to the micro controller via the I2C bus.

### Matrix Keyboard 
  The keyboard is a 3x4 row scanning matrix. The user can enter numbers from 0-9 and also 2 additional buttons were used as OK and CANCEL to navigate the menus. 
    
### RFID Reader
  The RFID Reader that is used in this project, is a standard reader that interfaces with the micro controller using the serial port.
   
### LCD (JHD 672a)
  All the user interface is via the 16x2 LCD that is connected to the micro controller. It sure does takes a lot of pins to connect this LCD.
    
### PC
  User can upload the data to the PC , the details of which users were denied and users who were allowed, the time of entry to the PC using the serial port. Max232 IC was used for level conversion for TTL to RS232. 

The entire board was developed and fabricated using FREEPCB and photos are available in [here](https://picasaweb.google.com/116927737060766804834/RFIDBasedAccessControlSystem?authuser=0&feat=directlink)


## Software

The hardware was written in c using Keil uVision.

## why add it to Github

The reason i have added to github is that its one of the first full fledged project that i wrote.I learned a lot from it such as 
  1. I2C bus using bit banging
  2. Interfacing to DS1307 and EEPROM
  3. How to serialize a int/long to character using unions and store into EEPROM
  4. Spliting code into multiple files 
  5. Much more
  
So its a project that i have a emotional attachment. Thats the reason why this is currently in github so i dont lose it forever.

### Current status
  I am not sure that the project would compile as i dont have a keil compiler anymore  and this project is **DEAD**. However one can look at the code to get ideas of using I2C and other stuff. But be warned this is one of my first codes and there are loads of things that could have been better and totally wrong. So you are warned.

##Presentation
  As part of the project development i created  a presentation and is available in [slideshare](http://www.slideshare.net/pradheepshrinivasan/rfid-based-access-control-ppt)
    
