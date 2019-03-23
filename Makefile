clean :
	find -name "*.out" -exec rm -f {} \;
	find -name "*.exe" -exec rm -f {} \; 
	find -name "*.o" -exec rm -f {} \; 