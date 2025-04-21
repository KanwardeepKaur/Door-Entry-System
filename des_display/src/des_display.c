#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/dispatch.h>
#include <sys/iofunc.h>
#include "../../des_controller/src/des-mva.h"

int main(void) {
	Person msg;
	int rcvid;
	name_attach_t *attach;
	//Phase I
	if ((attach = name_attach(NULL, "des_display", 0)) == NULL) {
		perror("name_attach failed");
		return EXIT_FAILURE;
	}

	printf("PID : %d\n", getpid());

	//Phase II
	while (1) {
		rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);
		if (rcvid == -1) {
			perror("MsgReceive failed");
			continue;
		}

		MsgReply(rcvid, EOK, NULL, 0);

		if (msg.message_type == LEFT_SCAN_MSG
				|| msg.message_type == RIGHT_SCAN_MSG) {
			printf("%s %d\n", outMessage[msg.message_type], msg.person_id);
		} else if (msg.message_type == WEIGHT_UPDATE_MSG) {
			printf("%s %d kg\n", outMessage[msg.message_type], msg.weight);
		} else if (msg.message_type == EXIT_MSG) {
			printf("%s\n", outMessage[msg.message_type]);
			break;
		} else {
			printf("%s\n", outMessage[msg.message_type]);
		}
	}

	//Phase III
	name_detach(attach, 0);
	return EXIT_SUCCESS;
}
