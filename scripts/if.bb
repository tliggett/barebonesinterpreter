# TJ Liggett
# Bare Bones if functionality
clear s1
clear s2
clear aux
clear X
clear Y
# Shows x before if executed
print X
# X is incremented before loop
incr Y
# If X not 0:
while X
	clear Y
	clear X
	incr aux
	# s1 instruction executed
	print s1
	;
# else:
while Y
	clear Y
	# s2 instruction executed
	print s2
	;
# Ensures X is not effected by if statement
while aux
	incr X
	decr aux
	;
# X shouldn't be changed by if statement
print X
