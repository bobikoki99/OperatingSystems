// cat /etc/passwd | sort | uniq
//.................a......b.....
/*
	init
	fork
		child cat
	init2
	fork
		child sort
	init3
	uniq
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
int main(void)
{
	int a[2];
	pipe(a);
	pid_t p = fork();
	if (p < 0)
	{
		err(2, "failed to fork");
	}

	if ( p == 0 )
	{
		close(a[0]);
		dup2(a[1],1);
		execlp("cat", "cat", "/etc/passwd", 0);
	} 
	close (a[1]);
	int b[2];
	pipe(b);
	p=fork();
	
	if ( p < 0) 
	{
		err(2, "failed to fork");
	}
	
	if (p == 0) 
	{
		dup2(a[0], 0);
		close(b[0]);
		dup2(b[1], 1);
		execlp("sort", "sort", 0);
	} 
	
	close (b[1]);
	dup2(b[0], 0);
	execlp("uniq", "uniq", 0);

	exit(0);
}
