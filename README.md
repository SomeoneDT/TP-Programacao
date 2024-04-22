# TP-Programacao
Practical Project for the 1st year class of "Programing" from my Bachelors in Informatic Engineering, realised in the school year of 2022/23

This project is as submitted, it has problems and mistakes, which I've learned from since.

Grade obtained [93/100]

# Goal of the Project
A very basic simulation metro system inspired by a real-life project our city was planning and investing into at the time, the program allows for the addition of "stations" to the system which can then be linked up in lines
These can then be used to calculate routes between two stations, etc...

# Knowledge Learnt
The project allowed me to learn and consolidate my knowledge on the following topics:
-> Dynamic Memory in C
-> Linked Lists
-> File manipulation (Binary and .txt)
-> Organizing a project in headers (.h) and code (.c) files.

Aswell as more mundane skills like time managment and the thinking necessary to overcome challenges.

# Flaws with the project
Only includes those known either at the time of submission or during a very brief review right before I posted this

-> The route calculation is flawed, the stations are right, but the printfs aren't, might fix this in the future. [FIXED] 

-> A memory leak that originated from me not returning the pline variable in a function. [FIXED]

-> The variable names are at times confusing, I've improved a lot since then and it this project taught me a great deal on the topic


# Notes and considerations

-> The route planner was intended to give the user every possible route between two stations, not just the shortest one, as such, it was possible for the program to give some seemingly nonsensical routes such as the following scenario
Line 1 - Station Origin -> Station Goal
Line 3 - Station Goal
This makes no sense, obviously, and it was fixed with a simple check to ignore the cases where the "transfer station"

-> Station names may, at times, be in reverse order.

-> I didn't want to fix this as it didn't really impact the program's performance, I'd want to keep is a memento
