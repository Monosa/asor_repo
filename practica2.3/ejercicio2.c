#include <sched.h>
#include <stdio.h>


int main(int argc, char *argv[]){
	
	int policy;
	policy = sched_getscheduler(getpid());
	
	if(policy == -1){
	 	perror("Error get scheduler");
		return -1;
	}

	switch(policy){
		case SCHED_OTHER:
			printf("SCHED_OTHER\n");
		break;
		case SCHED_FIFO:
			printf("SCHED_FIFO\n");
		break;
		case SCHED_RR:
			printf("SCHED_RR\n");
		break;
		default:
			printf("SCHED_ERROR\n");
		break;
	}

	int param;
	struct sched_param p;
	param = sched_getparam(getpid(), &p);

	if(param == -1){
	 	perror("Error get param");
		return -1;
	}

	printf("Prioridad: %i\n", p.sched_priority);

	int max = sched_get_priority_max(policy);
	int min = sched_get_priority_min(policy);
	
	if(max == -1){
	 	perror("Error get priority max");
		return -1;
	}

	if(min == -1){
	 	perror("Error get priority min");
		return -1;
	}

	printf("Max: %i - Min: %i\n", max, min);
	
	return 0;
}