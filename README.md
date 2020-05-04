# Flight Reservation System - FRS

With FRS you can build up a database with different aiports and flights and reserve seats in an airplane. You can show and edit all the reservations. Furthermore you can save all to different .txt files.

## Getting Started

To get started, download the project to your local machine. Extract the .zip archive. The archive includes a Visual Studio project file, which you have to open. If you dont want to open the whole project, you can just open the .exe file to run the program.

### Prerequisites

Before you run the program for the first time, let's have a look on the .txt files. They have the following structure:

airports.txt - includes Names of airports
```
Name of the City
Name of the City
Name of the City
....
```

flights.txt - includes all flights in the system
```
Flight ID, Number of Columns, Number of Rows, Index of Souceairport, Index of Destinationaiport
Flight ID, Number of Columns, Number of Rows, Index of Souceairport, Index of Destinationaiport
Flight ID, Number of Columns, Number of Rows, Index of Souceairport, Index of Destinationaiport
....
```

reservations.txt - includes all the reservations and the passengers
```
Flight ID, Row, Column, Surname, Firstname
Flight ID, Row, Column, Surname, Firstname
Flight ID, Row, Column, Surname, Firstname
Flight ID, Row, Column, Surname, Firstname
....
```

You can edit these files before starting the program or use the deafult files. It is important that there are no spaces in the files, otherwise the program can not read the files. When the program is running, the files are overwitten when the user saves all to the file system.

### Installing

No installations are needed.
If you use Visual Studio, Debug the project with the run button. 
If you just want to run the program, open the Flight_Reservation.exe file.

The Console should now open and load the data that is saved in in the .txt files. 

## Deployment

When the program is started, all possibilities and functions are shown and run depending on the user#s input to the command line.

## Built With

* [Visual Studio](https://visualstudio.microsoft.com/) - IDE


## Authors

* **Marco Kulla**  
* **Robin Weyand** 
* **David Lehr** 

The coding was done all together in the group.

## Acknowledgments

* Thanks to Corona, that gave us the idea to this project when we sat in the airplane on our way home


