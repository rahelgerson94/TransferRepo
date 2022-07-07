basketball: arrayz.o  #usuallly, first rule is the project file.
	gcc -Wall -Werror -std=c11 arrayz.o basketball.c -o basketball
#^this says that we need arrayz.o, basketball.o, and utils.o in order to compile the project file, main.c
#IN GENERAL: for each dependency, need a corrsponding rule.
#This is because make reads top to bottom, left to right. so it'll read basketball and
#see that it requires arrayz.o.
#It will then look for an arrayz.o rule.
#see that it requires basketball.o, and look for a basketball.o rule, etc.
#If it doesn't find a corresponding rule, it will complain:
	

arrayz.o: arrayz.c
		gcc -Wall -Werror -std=c11 arrayz.c -c
clean:
	rm -f basketball arrayz.o
