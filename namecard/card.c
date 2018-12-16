#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 100

typedef struct card_struct{
	char name[16];
	char company[16];
	char tel[16];
	char position[16];
}Card;

Card card[MAX];

Card result_card;
int card_index = 0;
int write_file, read_file;
char temp_string[16];
char filename[]= "card.txt";

void showMenu();
void showAllCards();
void inputCard();
void searchCard();
void deleteCard();
void updateCard();
void sortCard(Card * data, int left, int right);

int binSrch(Card* scope, const int len, char* find);
char * deleteSpace(char * string, int size);
char * inputSpace(char * string, int length, int size);

main()
{
	char string[20];
	write_file = open(filename, O_WRONLY | O_CREAT, 0644);
	close(write_file);
	read_file = open(filename, O_RDONLY);
	while (1) {
		if (read(read_file, card[card_index].name, 16) == 0) {
			break;
		}
		read(read_file, card[card_index].company, 16);
		read(read_file, card[card_index].tel, 16);
		read(read_file, card[card_index].position, 16);
		lseek(read_file, (off_t) 1, SEEK_CUR);

		deleteSpace(card[card_index].name, 16);
		deleteSpace(card[card_index].company, 16);
		deleteSpace(card[card_index].tel, 16);
		deleteSpace(card[card_index].position, 16);
		card_index++;
	}
	close(read_file);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	while (1) {
		showMenu();
		scanf("%s", string);
		if(strcmp(string, "입력") == 0)
			inputCard();
		else if(strcmp(string, "출력") == 0)
			showAllCards();
		else if(strcmp(string, "검색") == 0)
			searchCard();
		else if(strcmp(string, "수정") == 0)
			updateCard();
		else if(strcmp(string, "삭제") == 0)
			deleteCard();
		else if(strcmp(string, "정렬") == 0)
		{
			int i;
			sortCard(card, 0, card_index-1);
			write_file = open(filename, O_WRONLY | O_TRUNC);
			for (i = 0; i<card_index; i++){
				write(write_file, inputSpace(card[i].name, strlen(card[i].name), 16), 16);
				write(write_file, inputSpace(card[i].company, strlen(card[i].company), 16), 16);
				write(write_file, inputSpace(card[i].tel, strlen(card[i].tel), 16), 16);
				write(write_file, inputSpace(card[i].position, strlen(card[i].position), 16), 16);
				write(write_file, "\n", 1);
			}
		}
		else if(strcmp(string, "종료") == 0)
			break;
		
	}
}


void showMenu() {
	printf("\n명함 관리 프로그램\n");
	printf("---------------------\n");
	printf("입력\n");
	printf("출력\n");
	printf("검색\n");
	printf("수정\n");
	printf("삭제\n");
	printf("정렬\n");
	printf("종료\n");
	fputs(" : ", stdout);
}


void showAllCards() {
	int i;
	puts("Name\tCompany\tTel\tPosition");
	for (i = 0; i < card_index; i++)
	{
		printf("%s\t%s\t%s\t%s\n", card[i].name, card[i].company, card[i].tel, card[i].position);
	}
}


void inputCard() {
	fputs("저장할 이름 입력 : ", stdout);
	scanf("%s", card[card_index].name);
	fputs("저장할 회사 입력 : ", stdout);
	scanf("%s", card[card_index].company);
	fputs("저장할 전화번호 입력 : ", stdout);
	scanf("%s", card[card_index].tel);
	fputs("저장할 직급 입력 : ", stdout);
	scanf("%s", card[card_index].position);

	write_file = open(filename, O_WRONLY | O_APPEND, 0644);
	lseek(write_file, 0, SEEK_END);
	write(write_file, inputSpace(card[card_index].name, strlen(card[card_index].name), 16), 16);
	write(write_file, inputSpace(card[card_index].company, strlen(card[card_index].company), 16), 16);
	write(write_file, inputSpace(card[card_index].tel, strlen(card[card_index].tel), 16), 16);
	write(write_file, inputSpace(card[card_index].position, strlen(card[card_index].position), 16), 16);
	write(write_file, "\n", 1);
	close(write_file);
	card_index++;
}


void searchCard() {
	char name[30];
	fputs("검색할 이름 입력 : ", stdout);
	scanf("%s", name);
	if(binSrch(card, card_index, name))
		printf("이름:%s 회사:%s 전화번호:%s 직급:%s\n", result_card.name, result_card.company, result_card.tel, result_card.position);
	else
		printf("검색할 이름이 존재하지 않습니다.\n");

}


void deleteCard() {
	int i, j;
	char name[30];
	write_file = open(filename, O_WRONLY | O_TRUNC);
	fputs("삭제할 이름 입력 : ", stdout);
	scanf("%s", name);
	for (i = 0; i < card_index; i++)
	{
		if (strcmp(name, card[i].name) == 0) {
			for (j = i; j < card_index; j++)
			{
				card[j] = card[j + 1];
			}
			card_index--;
			for (i = 0; i<card_index; i++){
				write(write_file, inputSpace(card[i].name, strlen(card[i].name), 16), 16);
				write(write_file, inputSpace(card[i].company, strlen(card[i].company), 16), 16);
				write(write_file, inputSpace(card[i].tel, strlen(card[i].tel), 16), 16);
				write(write_file, inputSpace(card[i].position, strlen(card[i].position), 16), 16);
				write(write_file, "\n", 1);
			}
			return;
		}
	}
	close(write_file);
	printf("삭제할 이름이 존재하지 않습니다.\n");
}


void updateCard() {
	int i;
	char name[30];
	write_file = open(filename, O_WRONLY);
	fputs("검색할 이름 입력 : ", stdout);
	scanf("%s", name);
	for (i = 0; i < card_index; i++)
	{
		if (strcmp(name, card[i].name) == 0) {
			lseek(write_file, i * 16 * 4 + i, SEEK_SET);
			fputs("수정할 이름 : ", stdout);
			scanf("%s", card[i].name);
			fputs("수정할 회사 : ", stdout);
			scanf("%s", card[i].company);
			fputs("수정할 전화번호 : ", stdout);
			scanf("%s", card[i].tel);
			fputs("수정할 직급 : ", stdout);
			scanf("%s", card[i].position);
			write(write_file, inputSpace(card[i].name, strlen(card[i].name), 16), 16);
			write(write_file, inputSpace(card[i].company, strlen(card[i].company), 16), 16);
			write(write_file, inputSpace(card[i].tel, strlen(card[i].tel), 16), 16);
			write(write_file, inputSpace(card[i].position, strlen(card[i].position), 16), 16);
			write(write_file, "\n", 1);
			return;
		}
	}
	close(write_file);
	printf("수정할 이름이 존재하지 않습니다.\n");
}

char * inputSpace(char * string, int length, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		if(i < length)
		{
			temp_string[i] = string[i];
		}
		else 
			temp_string[i] = ' ';
	}
	return temp_string;
}

char * deleteSpace(char * string, int size)
{
	int i;
	for(i = 0; i < size; i++)
		if(string[i] == ' ')
		{
			string[i] = '\0';
		}
	return string;
}

int binSrch(Card* scope, const int len, char* find)
{
	int start = 0;
	int end = len;
	int i;
	Card temp_Card[MAX];
	for(i = 0; i < card_index; i++)
	{
		strcpy(temp_Card[i].name, scope[i].name);
		strcpy(temp_Card[i].company, scope[i].company);
		strcpy(temp_Card[i].tel, scope[i].tel);
		strcpy(temp_Card[i].position, scope[i].position);
	}
	sortCard(temp_Card, 0, card_index-1);

	while (start < end) {
		int middle = (start + end) / 2;
		int comp = strcmp(temp_Card[middle].name, find);
		if (comp < 0 ) {
			start = middle + 1;
		}
		else if (comp > 0) {
			end = middle;
		}
		else {
			strcpy(result_card.name, temp_Card[middle].name);
			strcpy(result_card.company, temp_Card[middle].company);
			strcpy(result_card.tel, temp_Card[middle].tel);
			strcpy(result_card.position, temp_Card[middle].position);
			return 1;
		}
	}
      return 0;
}

void sortCard(Card * data, int left, int right)
{
	int i, j;
 	Card x;
	Card temp;

	i = left;
	j = right;
	x = data[(left+right)/2];

	do {
		while((strcmp(data[i].name,x.name) < 0) && (i < right)) {
			i++;
		}
    	while((strcmp(data[j].name,x.name) > 0) && (j > left)) {
 			j--;
    		}
    	if(i <= j) {
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
 			i++;
			j--;
		}
	} while(i <= j);

	if(left < j) {
		sortCard(data, left, j);
	}
	if(i < right) {
		sortCard(data, i, right);
	}
}

