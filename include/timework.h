#ifndef TIME_H
#define TIME_H

	struct local_time
	{
		int	hours,
			min,
			sec,
			mon,
			day,
			year;
	};

	local_time get_time_now();

#endif