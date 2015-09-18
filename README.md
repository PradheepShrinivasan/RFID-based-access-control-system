# RFID-based-access-control-system
  An example RFID based access control system that i completed during my 3rd year of Engineering
  
## Overview 
  A RFID is similar to the NFC tags that are now present in almost all of the modern cellphones.Using RFID its possible to uniquely identify an item.
  
  As I was studying my bachelor degree,i was introduced to micro controller(8051) and i used 8051 micro controller to build an RFID based access control system.
  
  TODO add image
  
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
                	+----------+-----------+                                                         
               		|                      |                  
                 	|    Matrix Keyboard   |                  
                 	|                      |                  
                 	+----------------------+                  



## Software

The hardware was written in c using Keil uVision.

## why add it to Github

The reason i have added to github is that its one of the first full fledged project that i wrote.I learned a lot from it such as 
  1. I2C bus using bit banging
  2. Interfacing to DS1307 and EEPROM
  3. How to serialize a int/long to character using unions and store into EEPROM
  4. Spliting code into multiple files 
  5. Much more
  
So its a project that i have a emotional attachment. Thats the reason why this is currently in github.

### Current status

I am not sure that the project would compile as i dont have a keil compiler anymore  and this project is **DEAD**. However one can look at the code to get ideas of using I2C and other stuff. But be warned this is one of my first codes and there are loads of things that could have been better and totally wrong. So you are warned.

##Presentation
As part of the project development i created  a presentation during long back and you can find it [here](http://www.slideshare.net/pradheepshrinivasan/rfid-based-access-control-ppt)
