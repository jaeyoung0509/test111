#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct card {
	char name[30];
	char company[30];
	char tel[20];
	char position[20];
}CARD;

#define MAX 100
CARD ca[MAX];

int idx;
int w_fd, r_fd;
char *file = "namecard.txt";

void showMenu();
void showAllCards();
void inputCard();
void searchCard();
void deleteCard();
void updateCard();

main()
{
	char ch;
	w_fd = open(file, O_WRONLY | O_CREAT, 0644);
	r_fd = open(file, O_RDONLY);
	while (1) {
		if (read(r_fd, ca[idx].name, 30) == 0) {
			break;
		}
		read(r_fd, ca[idx].company, 30);
		read(r_fd, ca[idx].tel, 20);
		read(r_fd, ca[idx].position, 20);
		idx++;
	}
	close(r_fd);
	
	while (1) {
		showMenu();
		scanf("%c", &ch);
		puts("");
		switch (ch)
		{
			case 'I': inputCard();
			break;
			case 'O': showAllCards();
			break;
			case 'S':searchCard();
			break;
			case 'U':updateCard();
			break;
			case 'D':deleteCard();
			break;
			case 'E': puts("프로그램을 종료합니다.");
			close(w_fd);
			return;
		}
		getchar();
	}
}


void showMenu() {
	puts("\nBUSINESS CARD MANAGEMENT");
	puts("========================");
	puts("DATA INPUT (I)");
	puts("DATA OUTPUT (O)");
	puts("DATA SEARCH (S)");
	puts("DATA UPDATE (U)");
	puts("DATA DELETE (D)");
	puts("END (E)");
	fputs("Select(I, O, U, S, U, D, E) : ", stdout);
}


void showAllCards() {
	int i;
	puts("Name\tCompany\tTel\tPosition");
	for (i = 0; i < idx; i++)
	{
		printf("%s\t%s\t%s\n", ca[i].name, ca[i].company, ca[i].tel, ca[i].position);
	}
}


void inputCard() {
	fputs("저장할 이름 입력 : ", stdout);
	scanf("%s", ca[idx].name);
	fputs("저장할 회사 입력 : ", stdout);
	scanf("%s", ca[idx].company);
	fputs("저장할 전화번호 입력 : ", stdout);
	scanf("%s", ca[idx].tel);
	fputs("저장할 직급 입력 : ", stdout);
	scanf("%s", ca[idx].position);

	w_fd = open(file, O_WRONLY | O_APPEND, 0644);
	lseek(w_fd, 0, SEEK_END);
	write(w_fd, ca[idx].name, 30);
	write(w_fd, ca[idx].company, 30);
	write(w_fd, ca[idx].tel, 20);
	write(w_fd, ca[idx].position, 20);
	idx++;
}


void searchCard() {
	int result;
	char name[30];
	fputs("검색할 이름 입력 : ", stdout);
	scanf("%s", name);
	if(result = binSrch(ca, idx, name) != -1)
		printf("name:%s\ncompany:%s\ttel:%s\nposition:%s", ca[result].name, ca[result].company, ca[result].tel, ca[result].position);
	else
		puts("검색할 이름이 존재하지 않습니다.");

}


void deleteCard() {
	int i, j;
	char name[30];
	w_fd = open(file, O_WRONLY | O_TRUNC);
	fputs("삭제할 이름 입력 : ", stdout);
	scanf("%s", name);
	for (i = 0; i < idx; i++)
	{
		if (strcmp(name, ca[i].name) == 0) {
			for (j = i; j < idx; j++)
			{
				ca[j] = ca[j + 1];
			}
			idx--;
			for (i = 0; i<idx; i++){
				write(w_fd, ca[i].name, 30);
				write(w_fd, ca[i].company, 30);
				write(w_fd, ca[i].tel, 20);
				write(w_fd, ca[i].position, 20);
			}
			return;
		}
	}
	puts("삭제할 이름이 존재하지 않습니다.");
}


void updateCard() {
	int i;
	char name[30];
	w_fd = open(file, O_WRONLY);
	fputs("검색할 이름 입력 : ", stdout);
	scanf("%s", name);
	for (i = 0; i < idx; i++)
	{
		if (strcmp(name, ca[i].name) == 0) {
			lseek(w_fd, i * 60, SEEK_SET);
			fputs("수정할 이름 : ", stdout);
			scanf("%s", ca[i].name);
			fputs("수정할 회사 : ", stdout);
			scanf("%s", ca[i].company);
			fputs("수정할 전화번호 : ", stdout);
			scanf("%s", ca[i].tel);
			fputs("수정할 직급 : ", stdout);
			scanf("%s", ca[i].position);
			write(w_fd, ca[i].name, 30);
			write(w_fd, ca[i].company, 30);
			write(w_fd, ca[i].tel, 20);
			write(w_fd, ca[i].position, 20);
			return;
		}
	}
	puts("수정할 이름이 존재하지 않습니다.");
}


int binSrch(CARD* scope, const int len, char* find)
{
	int c, first, last, middle;

	first = 0;
	last = len - 1;
	middle = (first+last)/2;

	while( first <= last )
	{
		if (strcmp(scope[middle].name, find) < 0 )
			first = middle + 1;
		else if (strcmp(scope[middle].name, find) == 0)
		{
			return middle;
		}
		else
			last = middle - 1;
		middle = (first + last)/2;
	}
	if ( first > last )
      return -1;
}
