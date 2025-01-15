#include "laps.h"

/**
 * @param id: array of ids of cars
 * @param size: size of the array
 */
void race_state(int *id, size_t size)
{
	/* Define static pointers to store lap counts and car ids dynamically */
	static int *car_laps = NULL;
	static int *car_ids = NULL;
	static int num_cars = 0;

	/* If size is zero, free the allocated memory and stop */
	if (size == 0)
	{
		free(car_laps);
		free(car_ids);
		car_laps = NULL;
		car_ids = NULL;
		num_cars = 0;
		return;
	}

	size_t a;
	/* Process each car ID and add if not already present */
	for (a = 0; a < size; a++)
	{
		int car_id = id[a];
		int car_found = 0;

		size_t b;
		/* Check if car already exists */
		for (b = 0; b < num_cars; b++)
		{
			if (car_ids[b] == car_id)
			{
				car_found = 1;
				break;
			}
		}

		/* If the car is not found, allocate and initialize its lap count */
		if (!car_found)
		{
			car_ids = realloc(car_ids, (num_cars + 1) * sizeof(int));
			car_laps = realloc(car_laps, (num_cars + 1) * sizeof(int));
			if (car_ids == NULL || car_laps == NULL)
			{
				printf("Memory allocation failed\n");
				return;
			}

			car_ids[num_cars] = car_id;
			car_laps[num_cars] = -1;
			printf("Car %d joined the race\n", car_id);
			num_cars++;
		}
	}

	/* Increment laps for each car given in id */
	size_t i;
	for (i = 0; i < num_cars; i++)
	{
		size_t j;
		for (j = 0; j < size; j++)
		{
			if (car_ids[i] == id[j])
			{
				car_laps[i]++;
			}
		}
	}

	/* Print the state of the race sorted by car identifier */
	printf("Race state:\n");

	size_t k;
	/* Sort by car ID (ascending order) */
	for (k = 0; k < num_cars - 1; k++)
	{
		size_t l;
		for (l = k + 1; l < num_cars; l++)
		{
			if (car_ids[k] > car_ids[l])
			{
				/* Swap ids */
				int temp_id = car_ids[k];
				car_ids[k] = car_ids[l];
				car_ids[l] = temp_id;

				/* Swap lap counts */
				int temp_laps = car_laps[k];
				car_laps[k] = car_laps[l];
				car_laps[l] = temp_laps;
			}
		}
	}

	size_t m;
	/* Print the state of the race */
	for (m = 0; m < num_cars; m++)
	{
		printf("Car %d [%d laps]\n", car_ids[m], car_laps[m]);
	}
}
