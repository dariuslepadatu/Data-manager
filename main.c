#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "structs.h"
#define N 256
#define ZECE 10
#define MULT 170000

void elibereaza_data(data_structure *data) {
	free(data->header);
	free(data->data);
	free(data);
}

void cast_int1(int *nr, char tip) {
	if (tip == '1') {
		*nr = (int8_t)(*nr);
	} else if (tip == '2') {
		*nr = (int16_t)(*nr);
	} else {
		*nr = (int32_t)(*nr);
	}
	return;
}

void cast_int2(int *nr, char tip) {
	if (tip == '1') {
		*nr = (int8_t)(*nr);
	} else if (tip == '2') {
		*nr = (int32_t)(*nr);
	} else {
		*nr = (int32_t)(*nr);
	}
	return;
}

data_structure *AlocaDate(char *nume1, char *nume2, char tip,
int nr1, int nr2) {
	data_structure *D = NULL;
	void **p = NULL;
	int i = 0, j = 0;
	D = (data_structure*)calloc(1, sizeof(data_structure));
	D->header = (head*)calloc(1, sizeof(head));
	D->header->len = strlen(nume1) + strlen(nume2) + 4;
	D->data = calloc(ZECE * D->header->len,  sizeof(void));
	D->header->type = tip;
	cast_int1(&nr1, tip);
	cast_int2(&nr2, tip);
	p = D->data;
	for (i = 0; i < strlen(nume1); i++) {
		*(char*)&p[i] = nume1[i];
	}
	i++;
	*(int*)&p[i++] = nr1;
	*(int*)&p[i++] = nr2;
	for (j = 0; j < strlen(nume2); j++, i++) {
		*(char*)&p[i] = nume2[j];
	}
	return D;
}

int add_last(void **arr, int *len, data_structure *data) {	
	void **d = data->data;
	void **p = *arr;
	int i = 0;
	*(char*)&p[(*len)++] = data->header->type;
	*(int*)&p[(*len)++] = data->header->len;
	for (i = 0; i < data->header->len; i++, (*len)++) {
		p[*len] = d[i];
	}
	elibereaza_data(data);
	return 1;
}

int add_at(void **arr, int *len, data_structure *data, int index) {
	void **p = *arr, **d = data->data;
	int i = 0, conth = 0, j = 0, hlen = 0;
	if (*len < index) {
		*len = index;
		*(char*)&p[*len] = data->header->type;
		(*len)++;
		*(int*)&p[*len] = data->header->len;
		(*len)++;
		for (i = 0; i < data->header->len; i++, (*len)++) {
			p[*len] = d[i];
		}
		elibereaza_data(data);
		return 1;
	}
	for (i = 0; i < *len; conth++) {
		i++;
		hlen = (long)p[i];
		if (conth == index) break;
		for(i = i + 1, j = i; i < hlen + j; i++) {}
	}
	j = i - 1;
	*len = *len + data->header->len + 2;
	for (i = *len; i >= j + data->header->len + 2; i--) {
		p[i] = p[i - data->header->len - 2];
	}		
	*(char*)&p[j++] = data->header->type;
	*(int*)&p[j++] = data->header->len;
	for (i = 0; i < data->header->len; i++, j++) {
		p[j] = d[i];
	}
	elibereaza_data(data);
	return 1;
}

void printare_inturi(char tip, int nr1, int nr2) {
	if (tip == '1') {
		printf("\n%"PRId8"\n", nr1);
		printf("%"PRId8"\n", nr2);
	} else if (tip == '2') {
		printf("\n%"PRId16"\n", nr1);
		printf("%"PRId32"\n", nr2);
	} else {
		printf("\n%"PRId32"\n", nr1);
		printf("%"PRId32"\n", nr2);
	}		
	printf("\n");	
}

void find(void *data_block, int len, int index) {
	int i = 0, j = 0, cont = 0, conth = 0;
	int nr1 = 0, nr2 = 0, hlen = 0;
	char htype;
	void **p = data_block;
	for (i = 0; i < len; conth++) {
		if(!p[i]) {
			i++;
			continue;
		}
		htype = *(unsigned char*)&p[i++];
		hlen = (long)p[i];
		if (conth == index) {
			printf("Tipul %c\n", htype);
		}
		for(i = i + 1, j = i; i < hlen + j; i++) {
			if (conth == index) {
				if (p[i] == 0 && 
				(((int*)p[i-1] >= (int*)97 && (int*)p[i-1] <= (int*)122)
				|| ((int*)p[i-1] >= (int*)65 && (int*)p[i-1] <= (int*)90))) {
					cont++;
				} else if (cont == 0) {
					printf("%c", *(char*)&p[i]);
				} else if (cont == 1) {
					nr1 = (long)p[i];
					cont++;
				} else if (cont == 2) {
					printf(" pentru ");
					nr2 = (long)p[i];
					cont = 0;
				}
			}
		}
		if (conth == index) {
			printare_inturi(htype, nr1, nr2);
		}
	}
}

int delete_at(void **arr, int *len, int index) {
	int i = 0, j = 0, conth = 0, hlen = 0;
	void **p = *arr;
	for (i = 0; i < *len; conth++) {
		i++;
		hlen = (long)p[i];
		if (conth == index) break;
		for(i = i + 1, j = i; i < hlen + j; i++) {}
	}
	for(i--; i < *len - hlen - 2; i++) {
		p[i] = p[i + hlen + 2];
	}
	*len = *len - hlen - 2;	
	return 1;
}

void print(void *arr, int len) {
	int i = 0, j = 0, cont = 0, nr1 = 0, nr2 = 0, hlen = 0;
	void **p = arr;
	char htype;
	for (i = 0; i < len; ) {
		if(!p[i]) {
			i++;
			continue;
		}
		cont = 0;
		htype = *(unsigned char*)&p[i++];
		hlen = (long)p[i];
		printf("Tipul %c\n", htype);
		for(i = i + 1, j = i; i < hlen + j; i++) {
		if (p[i] == 0 && 
		(((int*)p[i-1] >= (int*)97 && (int*)p[i-1] <= (int*)122)
		|| ((int*)p[i-1] >= (int*)65 && (int*)p[i-1] <= (int*)90))) {
				cont++;
			} else if (cont == 0) {
				printf("%c", *(char*)&p[i]);
			} else if (cont == 1) {
				nr1 = (long)p[i];
				cont++;
			} else if (cont == 2) {
				printf(" pentru ");
				nr2 = (long)p[i];
				cont = 0;
			}
		}
		printare_inturi(htype, nr1, nr2);
	}
}

int main() {
	data_structure *D = NULL;
	char *linie, *p, *nume1, *nume2;
	unsigned char tip;
	void *arr = NULL;
	int len = 0, index = 0, nr1 = 0, nr2 = 0;
	linie = (char*)calloc(N, sizeof(char));
	arr = calloc(MULT, sizeof(void));
	nume1 = (char*)calloc(N, sizeof(char));
	nume2 = (char*)calloc(N, sizeof(char));
	while(fgets(linie, N, stdin)) {
		if (linie[strlen(linie) - 1] == '\n') {
            linie[strlen(linie) - 1] = '\0';
        }
        p = strtok(linie, " ");
        if (strcmp(p, "insert") == 0) {
			p = strtok(NULL, " ");
			tip = (unsigned char)p[0];
			p = strtok(NULL, " ");
			strncpy(nume1, p, N);	
			p = strtok(NULL, " ");
			nr1 = atoi(p);
			p = strtok(NULL, " ");
			nr2 = atoi(p);
			p = strtok(NULL, " ");
			strncpy(nume2, p, N);
			D = AlocaDate(nume1, nume2, tip, nr1, nr2);
			add_last(&arr, &len, D);
        }
		if (strcmp(p, "insert_at") == 0) {
			p = strtok(NULL, " ");			
			index = atoi(p);
			p = strtok(NULL, " ");
			tip = (unsigned char)p[0];
			p = strtok(NULL, " ");
			strncpy(nume1, p, N);		
			p = strtok(NULL, " ");
			nr1 = atoi(p);
			p = strtok(NULL, " ");
			nr2 = atoi(p);
			p = strtok(NULL, " ");
			strncpy(nume2, p, N);
			D = AlocaDate(nume1, nume2, tip, nr1, nr2);
			add_at(&arr, &len, D, index);
		}
		if (strcmp(p, "delete_at") == 0) {
			p = strtok(NULL, " ");
			index = atoi(p);
			delete_at(&arr, &len, index);
		}
		if (strcmp(p, "find") == 0) {
			p = strtok(NULL, " ");
			index = atoi(p);
			find(arr, len, index);
		}
		if (strcmp(p, "print") == 0) {
			print(arr, len);
		}
		if (strcmp(p, "exit") == 0) break;
	}
	free(arr);
	free(linie);
	free(nume1);
	free(nume2);
	return 0;
}
