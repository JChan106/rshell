Script started on Thu Aug 25 17:59:33 2016[?1034hbash-3.2$ ./bin/rshell
[?1034hbash-3.2$ ./bin/rshell
Makefile	bin		test
README.md	src		test_test.sh
kurtluu12@eduroam1-1-10-25-193-176.wnet.ucr.edu$ test -e Makefile
(True)
path exists
kurtluu12@eduroam1-1-10-25-193-176.wnet.ucr.edu$ test -f Makefile
(True)
path exists
kurtluu12@eduroam1-1-10-25-193-176.wnet.ucr.edu$ test -f src
(False)
kurtluu12@eduroam1-1-10-25-193-176.wnet.ucr.edu$ test -d Makefile
(False)
kurtluu12@eduroam1-1-10-25-193-176.wnet.ucr.edu$ test -d src
(True)
path exists
kurtluu12@eduroam1-1-10-25-193-176.wnet.ucr.edu$ exit
bash-3.2$ exit
exit

Script done on Thu Aug 25 18:01:47 2016
