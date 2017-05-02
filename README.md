# Analysis of Algorithms II, Project 2
Analysis of Algorithms II, 2016-2017 Spring Semester Project 2. Parsing Tree.

---

### Information
From the project description
```
 Input:  [W1 W2 W3 (W4 W5)] 
 
 Check if there is a suitable transformation rule (R1 → W4 W5) for the sequence [W4 W5]. 
 
 If so, form a sub-tree with them and merge them into a single constituent. 
 Continue testing windows starting from the rightmost pair in the current input [W1 W2 (W3 R1)]. 
 Otherwise, shift the window to the left as in [W1 W2 (W3 W4) W5], and keep testing transformation rules. 
 
 If no transformation rule can be applied, trace back from the recursion and keep testing windows. 
 If you trace back to the input and cannot find any other sub-trees, this means that there is no solution. 
 In this case, you will print a syntax error message. 
```
In my implementation the 'solve' function is doing the whole job. But there is no structure as tree in my implementation, I was just using vectors with decreasing order. 
```
std::string Parser::solve(std::vector<word> window, int current)
```



