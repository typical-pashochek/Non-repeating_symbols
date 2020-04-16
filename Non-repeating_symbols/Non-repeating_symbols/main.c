#include <stdio.h>
#include <locale.h>
#include <Windows.h>
void TextIntoMass(char*** mass, FILE** Text, int* rowsCount) {
	char symbol;
	symbol = fgetc(*Text);
	int rows = 2;
	while (!feof(*Text)) {
		if (symbol == '\n') {
			rows += 1;
		}
		symbol = fgetc(*Text);
	}
	*rowsCount = rows - 1;
	fseek(*Text, 0, SEEK_SET);
	(*mass) = (char**)malloc(rows * sizeof(char*));
	for (int i = 0; i < rows; i++) {
		int count = 0;
		symbol = fgetc(*Text);
		while (symbol != '\n' && !feof(*Text)) {
			count += 1;
			symbol = fgetc(*Text);
		}
		if (symbol == '\n') {
			fseek(*Text, -(count + 2), SEEK_CUR);
		}
		else {
			fseek(*Text, -(count), SEEK_CUR);
		}
		(*mass)[i] = (char*)malloc((count + 2) * sizeof(char));
		fgets((*mass)[i], count + 1, *Text);
		fgetc(*Text);
		(*mass)[i][count + 1] = 0;
	}
}
int length(char str[]) {
	int n = 0;
	while (str[n] != '\0') {
		n = n + 1;
	}
	return n;
}

int main() {
	FILE* f;
	fopen_s(&f, "input.txt", "r");
	if (f == NULL) {
		printf("File doesn't exist\n");
		exit(1);
	}
	char** mass;
	int rows;
	TextIntoMass(&mass, &f, &rows);
	fclose(f);
	puts(mass[0]);
	int flag = 0;
	int MaxBegin = 0, MaxEnd = 0;
	int begin = 0, end = 0;
	for (int i = 0; i < length(mass[0]); i++) {
		for (int j = begin; j < end; j++) {
			if (mass[0][i] == mass[0][j]) {
				flag = 1;
			}
		}
		if (flag == 1) {
			if (end - begin > MaxEnd - MaxBegin) {
				MaxEnd = end;
				MaxBegin = begin;
			}
			begin += 1;
			i = begin;
			end = begin;
			flag = 0;
		}
		else {
			end += 1;
		}
	}
	if (end - begin > MaxEnd - MaxBegin) {
		MaxEnd = end;
		MaxBegin = begin;
	}
	FILE* out;
	fopen_s(&out, "output.txt", "w");
	for (int i = MaxBegin; i <= MaxEnd; i++) {
		fprintf(out,"%c", mass[0][i]);
		
	}
	fprintf(out, "\nlength %d\n", MaxEnd - MaxBegin);
	fclose(out);
	return 0;
}