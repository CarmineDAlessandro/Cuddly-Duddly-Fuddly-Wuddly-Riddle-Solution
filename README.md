# Cuddly-Duddly-Fuddly-Wuddly-Riddle-Solution
A possible recursive general input solution for the homonym YouTube riddle

## Basis step
The algorithm ends when the number of eggs is 0 in two of the stacks and 1 in the third one. <br>
Both (0,0,1), (0,1,0) and (1,0,0) are valid output solutions.
If the remaining egg is in the red stack, the solution is considered valid, false otherwise. <br>

## Error case
In case more than 1 egg is remaining in the stack, the configuration leads to an error and a not valid solution is returned.
An error is actually triggered when the number of the eggs in a stack is lower than 0. <br>
For instance (-1,0,0), (2,0,-1) or (1,1,-2) will lead to an error and then a not valid solution.<br>

## Recursive step
The idea is to reduce by one the number of the two stacks which contain more eggs and increase the other stack by 1.<br>
It can be summarized as follows:<br>
<br>
function (red, purple, blue):<br>
&ensp;&ensp;(red + 1, purple - 1, blue - 1) &ensp; if: red &le; purple AND red &le; blue<br>
&ensp;&ensp;(red - 1, purple + 1, blue - 1) &ensp; if: purple &le; red AND purple &le; blue<br>
&ensp;&ensp;(red - 1, purple - 1, blue + 1) &ensp; if: blue &le; red AND blue &le; purple<br>

## (Dynamic) Optimization
Due to the obvious presence of a brute force approach, it was needed an optimization of the performance.<br>
It is necessary because the algorithm may compute the same recursive branch many times leading to an unnecessary calculation that
exponentially increases the execution time. To solve this problem, the algorithm stores the partial results previously calculated and 
uses the information when needed, cutting down the overall execution time.<br>

## Output
The (spoiler free) output of the program is an overview of the original number of the eggs in each stack and the correctness of 
adding an egg per color, as I show below. In case of an empty parameter list, the program runs with the values (43,33,23):<br>
<br>
&ensp;>cuddly.exe 2 3 4<br>
&ensp;Running the program for input: 2 red, 3 purple, 4 blue<br>
&ensp;Adding a red egg: correct<br>
&ensp;Adding a purple egg: incorrect<br>
&ensp;Adding a blue egg: incorrect
