#include "ants.h"

Ants::Result Ants::Execute()
{
	Result result;
	result.max_value = 0;
	result.min_value = 0;

	for (int i = 0; i < N_; i++)
	{
		int l_r = L_ - v_[i];

		if (v_[i] > l_r)
		{
			if (result.min_value < l_r)
				result.min_value = l_r;
			if (result.max_value < v_[i])
				result.max_value = v_[i];
		}
		else
		{
			if (result.min_value < v_[i])
				result.min_value = v_[i];
			if (result.max_value < l_r)
				result.max_value = l_r;
		}
	}
	return result;
}