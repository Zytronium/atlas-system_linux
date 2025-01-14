#include "laps.h"

void race_state(int *id, size_t size)
{
	// Define a static pointer to store lap counts and car ids dynamically
	static int *car_laps = NULL;
	static int *car_ids = NULL;
	static int num_cars = 0;

	// If size is zero, free the allocated memory and stop
	if (size == 0)
	{
		free(car_laps);
		free(car_ids);
		car_laps = NULL;
		car_ids = NULL;
		num_cars = 0;
		return;
	}

	// Process each car ID and add if not already present
	for (int i = 0; i < size; i++)
	{
		int car_id = id[i];
		int car_found = 0;

		// Check if car already exists
		for (int j = 0; j < num_cars; j++)
		{
			if (car_ids[j] == car_id)
			{
				car_found = 1;
				break;
			}
		}

		// If the car is not found, allocate and initialize its lap count
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

	// Increment laps for each car given in id
	for (int i = 0; i < num_cars; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (car_ids[i] == id[j])
			{
				car_laps[i]++;
			}
		}
	}

	// Print the state of the race sorted by car identifier
	printf("Race state:\n");

	// Sort by car ID (ascending order)
	for (int i = 0; i < num_cars - 1; i++)
	{
		for (int j = i + 1; j < num_cars; j++)
		{
			if (car_ids[i] > car_ids[j])
			{
				// Swap ids
				int temp_id = car_ids[i];
				car_ids[i] = car_ids[j];
				car_ids[j] = temp_id;

				// Swap lap counts
				int temp_laps = car_laps[i];
				car_laps[i] = car_laps[j];
				car_laps[j] = temp_laps;
			}
		}
	}

	// Print the state of the race
	for (int i = 0; i < num_cars; i++)
	{
		printf("Car %d [%d laps]\n", car_ids[i], car_laps[i]);
	}
}
