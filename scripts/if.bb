clear s1
clear s2
clear aux
clear X
clear Y
print X
incr Y
while X
	clear Y
	clear X
	incr aux
	print s1
	;
while Y
	decr Y
	incr X
	print s2
	;
while aux
	incr X
	decr aux
	;
print X
