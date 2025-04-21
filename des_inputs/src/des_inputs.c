#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <errno.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include "../../des_controller/src/des-mva.h"

int get_command_index(const char *input) {
	for (int i = 0; i < TOTAL_INPUTS; i++) {
		if (strcmp(input, input_commands[i]) == 0) {
			return i;
		}
	}
	return -1; // Invalid command
}

int main(int argc, char *argv[]) {
	int coid;
	Person person_message;

	if ((coid = name_open("des_controller", 0)) == -1) {
		perror("name_open failed");
		return EXIT_FAILURE;
	}

	while (1) {
		printf("\nSelect event from the following list:\n");
		printf(" ls  - Left Scan\n");
		printf(" rs  - Right Scan\n");
		printf(" ws  - Weight Scale\n");
		printf(" lo  - Left Open\n");
		printf(" ro  - Right Open\n");
		printf(" lc  - Left Close\n");
		printf(" rc  - Right Close\n");
		printf(" grl - Guard Right Lock\n");
		printf(" gru - Guard Right Unlock\n");
		printf(" gll - Guard Left Lock\n");
		printf(" glu - Guard Left Unlock\n");
		printf(" Exit - Exit the program\n");
		printf("Enter choice: \n");

		char user_input[20];
		scanf("%19s", user_input);

		int cmd_index = get_command_index(user_input);

		switch (cmd_index) {
		case 0: // "ls"
			person_message.current_state = LEFT_SCAN;
			printf("Enter the Person's ID: ");
			fflush(stdout);
			scanf("%d", &person_message.person_id);
			printf("\n");
			break;
		case 1: // "rs"
			person_message.current_state = RIGHT_SCAN;
			printf("Enter the Person's ID: ");
			fflush(stdout);
			scanf("%d", &person_message.person_id);
			printf("\n");
			break;
		case 2: // "ws"
			person_message.current_state = WEIGHT_SCAN;
			printf("Enter the Person's Weight: ");
			fflush(stdout);
			scanf("%d", &person_message.weight);
			printf("\n");
			break;
		case 3: // "lo"
			person_message.current_state = LEFT_OPEN;
			break;
		case 4: // "ro"
			person_message.current_state = RIGHT_OPEN;
			break;
		case 5: // "lc"
			person_message.current_state = LEFT_CLOSE;
			break;
		case 6: // "rc"
			person_message.current_state = RIGHT_CLOSE;
			break;
		case 7: // "grl"
			person_message.current_state = GUARD_RIGHT_LOCK;
			break;
		case 8: // "gru"
			person_message.current_state = GUARD_RIGHT_UNLOCK;
			break;
		case 9: // "gll"
			person_message.current_state = GUARD_LEFT_LOCK;
			break;
		case 10: // "glu"
			person_message.current_state = GUARD_LEFT_UNLOCK;
			break;
		case 11: // "exit"
			person_message.current_state = EXIT;
			break;
		default:
			printf("Invalid command. Please try again.\n");
			continue;
		}

		// Send the Person object to the controller
		if (MsgSend(coid, &person_message, sizeof(person_message), NULL, 0)
				== -1) {
			perror("MsgSend failed");
			name_close(coid);
			return EXIT_FAILURE;
		}

		if (person_message.current_state == EXIT) {
			break;
		}
	}

	name_close(coid);
	printf("Disconnected from controller. Exiting...\n");
	return EXIT_SUCCESS;
}
