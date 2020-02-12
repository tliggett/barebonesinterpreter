clear X
incr X
incr X
incr X
incr X
incr X
clear Y
incr Y
incr Y
incr Y
clear Z
print X
print Y
print Z
clear xaux
clear yaux
while X
	print Z
	while Y
		incr Z
		decr Y
		incr yaux
		print Y
		print yaux
		;
	while yaux
		incr Y
		decr yaux
		;
	decr X
	incr xaux
	print X
	;
while xaux
	incr X
	decr xaux
	;
print X
print Y
print Z
