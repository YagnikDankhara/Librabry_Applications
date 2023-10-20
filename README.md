# Library_Application

When Books and other publications arrive in the library, they should be tagged and put on shelves, so they are easily retrievable to be lent out to those who need them. The task is to design an application that receives the publications and stores them into the system with the information needed for their retrieval.

Later, each publication can be lent out to members of the library with a due date for return.

## Date Class
A class the encapsulates year, and month and day values for Date stamp, comparison and Date IO purposes.

## MenuItem Class
A class that hold a text Item; (an option or title to be displayed) in a menu to be selected by the user. This is a fully private class that is only accessible by Menu (see next class)

## Menu Class
A class that has several MenuItems to be displayed so the user can select one of them for an action to be executed in the program

## LibApp Class
The LibApp class demos the execution of the Seneca Library Application with printing messages instead of actually doing the tasks.

Later these messages are replaced with actual working modules to make the application functional.

Creating a mockup application before developing the main program helps to understand the entire system and also demonstrates the execution of the program to the client before the application is fully developed.

## Publication class
The publication class is responsible for handling the new data of the publication as well as updating them too.


## The Book class 
The Book class is derived from the Publication class. A book is a publication with an "Author name".

The book class only has one attribute that is a pointer to a character to hold an author's name Dynamically.

## The PublicationSelector class
The PublicationSelector module holds the addresses of a selection of the Publications in an array and lets the user select one of them. Upon user's selection, the Library Reference number of the selected publication is returned to the caller module for further actions.

For example, the array of Publications can be searched for a match to a specific title, and the matches found in the array can be inserted into the PublicationSelector. Then the PublicationSelector can be run to display the search results and ask the user to select one of them.
