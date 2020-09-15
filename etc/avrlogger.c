#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct instant {
	int SCLK;
	int MOSI;
	int CS_AD9833;
	int time;
    struct instant *next;
};

int i = 0;
struct instant *head = NULL;
struct instant *curr = NULL;

struct instant* create_list(int SCLK, int MOSI, int CS_AD9833, int time)
{
    printf("%d creating head node with SCLK=%d, MOSI=%d, CS_AD9833=%d, time=%d\n", i, SCLK, MOSI, CS_AD9833, time);
    struct instant *ptr = (struct instant*)malloc(sizeof(struct instant));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->SCLK = SCLK;
	ptr->MOSI = MOSI;
	ptr->CS_AD9833 = CS_AD9833;
	ptr->time = time;
    ptr->next = NULL;

    head = ptr;
    curr = head;
    return ptr;
}

struct instant* add_to_list(int SCLK, int MOSI, int CS_AD9833, int time)
{
    if(NULL == head)
    {
        return (create_list(SCLK, MOSI, CS_AD9833, time));
    }
	
    printf("%d adding new node with SCLK=%d, MOSI=%d, CS_AD9833=%d, time=%d\n", i, SCLK, MOSI, CS_AD9833, time);
    struct instant *ptr = (struct instant*)malloc(sizeof(struct instant));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->SCLK = SCLK;
	ptr->MOSI = MOSI;
	ptr->CS_AD9833 = CS_AD9833;
	ptr->time = time;
    ptr->next = NULL;

	curr->next = ptr;
	curr = ptr;
    return ptr;
}

void read_list(void)
{
    if (NULL == head) {
        printf("Head is null.\n");
        return;
    }
    struct instant *ptr = head;
    while (ptr != NULL) {
        printf("time: %d, SCLK: %d, MOSI: %d, CS_AD9833: %d\n", ptr->time, ptr->SCLK, ptr->MOSI, ptr->CS_AD9833);
        ptr = ptr->next;
    }
    return;
}

int main(int argc, char *argv[]) {
	FILE *fp;
	char *line = NULL;
	char *filename;
	size_t len = 0;
	size_t read;
	int totaltime = 0, globaltime = 0;
    unsigned char portchar = 0x00;
	int SCLK = 0, MOSI = 0, CS_AD9833 = 1;
	
	if (argc < 2) {
		printf("./avrlogger filename\n");
		return(1);
	} else {
		filename = argv[1];
	}
	
	fp = fopen(filename, "r");
	if (fp == NULL) 
		exit(EXIT_FAILURE);

	add_to_list(0, 0, 0, totaltime);
	
	while ((read = getline(&line, &len, fp)) != -1) {
		if (line[0] == '#') {
			line = &line[1];
			totaltime += atoi(line);
		} else {
			while(1) {
			if (globaltime == totaltime) {
				line = &line[10];
				portchar = (unsigned char)strtol(line, NULL, 16);

				if (portchar & 0x20)
					SCLK = 1;
				else
					SCLK = 0;
				
				if (portchar & 0x10)
					MOSI = 1;
				else
					MOSI = 0;
				
				if (portchar & 0x04)
					CS_AD9833 = 1;
				else
					CS_AD9833 = 0;
        			i++;
				break;
			} else {
				globaltime++;
			}
			add_to_list(SCLK, MOSI, CS_AD9833, globaltime);
			}
		}
	}
	fclose(fp);
    read_list();
	fp = fopen("avrsim.csv", "w");
	fprintf(fp, "Cycle, SCLK, MOSI, CS_AD9833\n");
	struct instant *ptr = head;
	while (ptr != NULL) {
		fprintf(fp, "%d,%d,%d,%d\n", ptr->time, ptr->SCLK, ptr->MOSI, ptr->CS_AD9833);
		ptr = ptr->next;
	}
	fclose(fp);
	return 0;
}
