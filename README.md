# CS-300
# DSA: Analysis and Design

"What was the problem you were solving in the projects for this course?"

I needed to plan and create a course planner. It would need to fill two specifics tasks. Print a list of all the computer science courses in alphanumeric order and for a given course, print out its title and prerequisites. I also needed to understand which data structure would be best suited for the task based on performance and memory. Out of the three I had to choose, Vector, Hash Table, and BST, I had chosen BST. The main reason I had was that the in-order traversal made it easy to implement the needed sorted list while keeping an efficient search. 

"How did you approach the problem? Consider why data structures are important to understand."

I went through the three data structure, Vector, Hash Table, and BST and I specfically compared them based on a few different neccesities for a good performances. Those being, load cost, lookup, memory management, and sorting. I chose BST as those it suited those needs well. I also wrote helpers to help with input and case, Trim, ToUpper, and SplitCSV to compare courses well. I created Course and Node types, inserted by course number, and printed through in-order traversal. I then wrote a menu specific to this projects needs. The first being loading file data to structurea and two being printing a alphanumeric list of the course. Number three being printing the course title and the prerequisites for any individual course. Number nine would be the exit to get out of the application.

"How did you overcome any roadblocks you encountered while going through the activities or project?"

There were a few roadbloacks I had to overcome to complete this project. One being CSV lines and spaces being not consistent. It could cause issue to not have CS-300 written out but cs300. I did this by adding helpers to fix this like trim and ToUpper. Another roadblock was making sure there were no leaks in the data. I overcame this by destroying the now old BST before a new one was loaded in. Another roadblock was pointers, zybooks taought me a lot about pointers but it did get confusing. I overcame this by making sure to keep search and inserting simple, I then tested and went through it to make sure it went well. 

"How has your work on this project expanded your approach to designing software and developing programs?"

This project taught me many things. The first being the usefulness of psuedocode. It can be annoying and feel like a waste of time to write psuedocode, especially for more basic projects, but it puts things in order and lets you see the bigger picture. The second being data structures, I wasn't well versed in them until this project, except vectors but I woulnd't say I was too great with them. Learning about BSTs, Hash Tables, vectors was interesting and made me consider each of their strengths and weaknesses to best fit a specific situation. To add onto that I didn't know much about run times so it was helpful to see how that factored in especially when considering the magnitude of data these structure can handle efficiently or inefficiently. The third being the helpers I added, they were interesting to learn about and really helps in keeping things consistent. The fourth is more of a general skill improvement, I had a lot of practice with this project so it helped my code be more readable, reusable, and consider options like those helpers to improve the code.

"How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?"

This project evolved the way I write programs that are maintainable, readable, and adaptable in several different ways. One being is to keep a clear and consistent sense when naming. Another is making sure to check for errors early to make sure they don't become a bigger problem down the line. Another is keeping things to the point and simple if possible, you need to write a lot of code so this can help keep the clutter down. Another being is that I learned about was to improve my code that weren't neccesarily needed but helped a lot. DestroyTree was helpful to free up memory and not get bogged down by it. Helpers liek trim and ToUpper helped to keep things consistent. Thinsg like this helped me broden my perspective on how to best accomplish the task at hand. 
