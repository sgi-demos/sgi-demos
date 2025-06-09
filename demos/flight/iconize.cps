% this generates the macro that will cause the program to be iconified
% thanks to Mark Callow for the code
% invoked from C as (void)flipiconic(window_id);
cdef flipiconic(int gid)
	/flipiconic gid gfsend
