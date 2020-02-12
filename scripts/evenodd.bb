clear X
incr X
incr X
print X
clear Z
clear zaux
incr zaux
clear xaux
while X
	while Z
		clear Z
		clear zaux
		;
	while zaux
		incr Z
		decr zaux
		;
	decr X
	incr xaux
	incr zaux
	;
while xaux
	incr X
	decr xaux
	;
print Z
