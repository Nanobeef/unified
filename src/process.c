

pid_t execute_create(String8 file, u32 arg_count, const String8* args)
{
	pid_t pid = fork();
	if(pid == 0)
	{
		//execvp();		
	}
	else if (pid < 0)
	{
		printf("Execute error for %s\n", file.data);
	}
	return 0;
}
pid_t execute_join(pid_t pid)
{
	return waitpid(pid, 0,0);
}
