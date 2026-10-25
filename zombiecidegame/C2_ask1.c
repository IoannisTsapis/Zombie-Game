// C2_project_1_tsapis_kontos.c
/* Giannis Tsapis 
AM:2022202000214
dit20214@go.uop.gr

Dimitris Kontos
AM: 2022202100093
dit21093@go.uop.gr

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define PANO		0
#define KATO		1
#define DEKSIA		2
#define ARISTERA	3

#define COMMAND_ERROR	-1
#define COMMAND_EXIT	0
#define COMMAND_BOMB	1
#define COMMAND_NEURO	2
#define COMMAND_WIN		100
#define COMMAND_VICTORY 101

#define START_N	7
#define START_M	7
#define END_N	20
#define END_M	20

#define SIZE1	50

void move_zombies(char** table, int N, int M, int sound){
	int i, j, ii, jj;
	
	if (sound == PANO){
		for (j = 0 ; j < M ; j++){
			for (i = 0 ; i < N - 1 ; i++){
				if (table[i][j] == '.'){
					for (ii = i + 1 ; ii < N ; ii++){
						if (isdigit(table[ii][j])){
							table[i][j] = table[ii][j];
							table[ii][j] = '.';
							break;
						}
						else if (table[ii][j] == '#') break;
					}
				}
			}
		}
	}
	else if (sound == KATO){
		for (j = 0 ; j < M ; j++){
			for (i = N - 1 ; i > 0 ; i--){
				if (table[i][j] == '.'){
					for (ii = i - 1 ; ii >= 0 ; ii--){
						if (isdigit(table[ii][j])){
							table[i][j] = table[ii][j];
							table[ii][j] = '.';
							break;
						}
						else if (table[ii][j] == '#') break;
					}
				}
			}
		}
		
	}
	else if (sound == DEKSIA){
		for (i = 0 ; i < N ; i++){
			for (j = M - 1 ; j > 0 ; j--){
				if (table[i][j] == '.'){
					for (jj = j - 1 ; jj >= 0 ; jj--){
						if (isdigit(table[i][jj])){
							table[i][j] = table[i][jj];
							table[i][jj] = '.';
							break;
						}
						else if (table[i][jj] == '#') break;
					}
				}
			}
		}
	}
	else {
		for (i = 0 ; i < N ; i++){
			for (j = 0 ; j < M - 1 ; j++){
				if (table[i][j] == '.'){
					for (jj = j + 1 ; jj < M ; jj++){
						if (isdigit(table[i][jj])){
							table[i][j] = table[i][jj];
							table[i][jj] = '.';
							break;
						}
						else if (table[i][jj] == '#') break;
					}
				}
			}
		}
	}
	
}

char** new_tablo(int N, int M){
	char** tablo = NULL;
	int i, j;
	
	tablo = (char**)malloc(sizeof(char*) * N);
	if (tablo == NULL){
		printf("malloc error\n");
		exit(1);
	}
	
	for (i = 0 ; i < N ; i++){
		tablo[i] = (char*)malloc(sizeof(char) * M);
		if (tablo[i] == NULL){
			printf("malloc error\n");
			exit(1);
		}
		
		for (j = 0 ; j < M ; j++){
			tablo[i][j] = '.';
		}
	}
	
	return tablo;
}

void show(char** tablo, int N, int M){
	int i, j;
	
	printf("   ");
	
	for (i = 1 ; i <= M ; i++){
		printf(" %2d", i);
	}
	
	printf("\n");
	
	for (i = 0 ; i <= M ; i++){
		printf("---");
	}
	
	printf("\n");
	
	for (i = 0 ; i < N ; i++){
		printf("%2d|", i+1);
		for (j = 0 ; j < M ; j++){
			printf(" %2c", tablo[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void add_hashes(char** tablo, int N, int M){
	int i, j;
	int plithos_ktirion = rand() % 8 + 1;
	int plithos_hashes;
	int ktiria = 0, hashes, prosanatolismos;
	
	//printf("ktiria: %d\n", plithos_ktirion);
	
	while (ktiria < plithos_ktirion){
		
		hashes = 0;
		
		do{
			i = rand() % N;
			j = rand() % M;
		} while (tablo[i][j] != '.');
		
		plithos_hashes = rand() % 8 + 1;
		
		tablo[i][j] = '#';
		hashes++;
		
		while (hashes < plithos_hashes){
			prosanatolismos = rand() % 4;
			
			if (prosanatolismos == KATO) i++;
			else if (prosanatolismos == PANO) i--;
			else if (prosanatolismos == DEKSIA) j++;
			else j--;
			
			if (i < 0 || i == N || j < 0 || j == M){
				if (prosanatolismos == KATO) i--;
				else if (prosanatolismos == PANO) i++;
				else if (prosanatolismos == DEKSIA) j--;
				else j++;
			}
			else if (tablo[i][j] == '.'){
				tablo[i][j] = '#';
				hashes++;
			}
				
		}
		if (hashes == plithos_hashes) ktiria++;
	}
	
}

void add_zombies(char** table, int N, int M, int Z){
	int i, j;
	
	for (i = 0 ; i < N ; i++){
		for (j = 0 ; j < M ; j++)
			

			if (table[i][j] == '.')
				table[i][j] = rand() % Z + 1 + '0';
	}
}

void print_info(int level, int score){
	printf("Level %d - Score %d\n", level, score);
	printf("The zombies overrun us, make your move: ");
}

void free_tablo(char** table, int N){
	int i;
	
	for (i = 0 ; i < N ; i++) free(table[i]);
	free(table);
}

void bomb(char** tablo, int N, int M, char* move, int *score){
	int i, j, row, col, killed_zombies = 0;
	char *comma = NULL;
	
	
	row = atoi(move);
	
	comma = strchr(move, ',');
	
	if (comma == NULL){
		printf("Wrong command! Not a bomb command!\n");
		return;
	}
	
	col = atoi(comma + 1);
	
	//printf("row: %d, col: %d\n", row, col);

	row--;
	col--;
	
	
	if (row < 0 || row >= N || col < 0 || col >= M){
		printf("Position out table!\n");
		return;
	}
	
	for (i = row - 1 ; i <= row + 1 ; i++){
		for (j = col - 1 ; j <= col + 1 ; j++){
			if (i >= 0 && i < N && j >= 0 && j < M){
				if (isdigit(tablo[i][j])){
					 killed_zombies++;
					 tablo[i][j] = '.';
				}
			}
			
		}
	}
	
	if (killed_zombies == 1) *score += 10;
	if (killed_zombies == 2) *score += 25;
	if (killed_zombies == 3) *score += 40;
	if (killed_zombies == 4) *score += 50;
	if (killed_zombies == 5) *score += 58;
	if (killed_zombies == 6) *score += 77;
	if (killed_zombies == 6) *score += 90;
	if (killed_zombies == 8) *score += 100;
	if (killed_zombies == 9) *score += 120;
	
	
}

void anadromiki_neuro(char** tablo, int N, int M, int row, int col, char hit_zombie, int *total_zombies){
	
	
	if (row < 0 || row >= N || col < 0 || col >= M) return;
	
	
	if (tablo[row][col] != hit_zombie) return;
	
	
	*total_zombies += 1;
	
	
	tablo[row][col] = '.';
	
	
	anadromiki_neuro(tablo, N, M, row+1, col, hit_zombie, total_zombies);
	anadromiki_neuro(tablo, N, M, row-1, col, hit_zombie, total_zombies);
	anadromiki_neuro(tablo, N, M, row, col+1, hit_zombie, total_zombies);
	anadromiki_neuro(tablo, N, M, row, col-1, hit_zombie, total_zombies);
}

void neuro(char** tablo, int N, int M, char* move, int *score){
	
	int row, col, can_hit = 0, total_zombies = 0;
	char *comma = NULL, hit_zombie;
	
	row = atoi(move);
	
	comma = strchr(move, ',');
	
	if (comma == NULL){
		printf("Wrong command! Not a bomb command!\n");
		return;
	}
	
	col = atoi(comma + 1);
	
	//printf("row: %d, col: %d\n", row, col);

	row--;
	col--;
	
	if (row < 0 || row >= N || col < 0 || col >= M){
		printf("Position out table!\n");
		return;
	}
	
	hit_zombie = tablo[row][col];
	
	if (isdigit(hit_zombie) == 0){
		printf("You must hit a zombie for neurogun!\n");
		return;
	}
	
	if (row - 1 >= 0 && tablo[row-1][col] == hit_zombie) can_hit++;
	if (row + 1 < N  && tablo[row+1][col] == hit_zombie) can_hit++;
	if (col - 1 >= 0 && tablo[row][col-1] == hit_zombie) can_hit++;
	if (col + 1 < M  && tablo[row][col+1] == hit_zombie) can_hit++;
	
	if (can_hit == 0){
		printf("You cannot hit lonely zombies!\n");
		return;
	}
	
	anadromiki_neuro(tablo, N, M, row, col, hit_zombie, &total_zombies);
	
	//printf("total zombies: %d\n", total_zombies);
	
	if (total_zombies == 1) *score += 10;
	else if (total_zombies == 2) *score += 25;
	else if (total_zombies == 3) *score += 40;
	else if (total_zombies == 4) *score += 50;
	else if (total_zombies == 5) *score += 58;
	else if (total_zombies == 6) *score += 77;
	else if (total_zombies == 7) *score += 90;
	else if (total_zombies == 8) *score += 100;
	else if (total_zombies == 9) *score += 120;
	else if (total_zombies <= 18) *score += 190;
	else if (total_zombies <= 25) *score += 210;
	else if (total_zombies > 25) *score += 100 + total_zombies * 10;
	
}

int no_more_zombies(char** tablo, int N, int M){
	int i, j, zombies = 0;
	
	for (i = 0 ; i < N ; i++){
		for (j = 0 ; j < M ; j++){
			if (isdigit(tablo[i][j])) zombies++;
		}
	}
	
	if (zombies == 0) return 1;
	
	return 0;
}

int main(){
	char** table = NULL;
	int N, M, Z, sound;
	
	int command_code;
	int level = 1;
	int score = 0;
	char move[SIZE1];
	char command[SIZE1];
	
	srand(time(NULL));
	
	
	
	do{
		printf("Enter rows and cols (%d-%d): ", START_N, END_N);
		scanf("%d%d", &N, &M);
	} while (N < START_N || N > END_N || M < START_M || M > END_M);
	
	do {
		printf("Enter max zombie number (1-9): ");
		scanf("%d", &Z);
	}while (Z < 1 || Z > 9);
	
	do {
	sound = rand() % 4;
	switch (sound){
		case PANO: printf("Sound top\n"); break;
		case KATO: printf("Sound bottom\n"); break;
		case DEKSIA: printf("Sound right\n"); break;
		case ARISTERA: printf("Sound left\n"); break;
	}

		table = new_tablo(N, M);
		add_hashes(table, N, M);
		add_zombies(table, N, M, Z);
	
		do {
			show(table, N, M);
			print_info(level, score);
			scanf("%s", command);
	
			if (strcmp(command, "x") == 0 || strcmp(command, "X") == 0){
				printf("Levels %d, Points %d\n", level - 1, score);
				printf("Game over\n");
				command_code = COMMAND_EXIT;
			}
			else if (strcmp(command, "b") == 0 || strcmp(command, "B") == 0){
				scanf("%s", move);
				//printf("move: %s\n", move);
				command_code = COMMAND_BOMB;
				bomb(table, N, M, move, &score);
				move_zombies(table, N, M, sound);
			}
			else if (strcmp(command, "n") == 0 || strcmp(command, "N") == 0){
				scanf("%s", move);
				//printf("move: %s\n", move);
				command_code = COMMAND_NEURO;
				neuro(table, N, M, move, &score);
				move_zombies(table, N, M, sound);
			}
			else {
				printf("Unknown command!\n");
				command_code = COMMAND_ERROR;
			}
			if (command_code != COMMAND_EXIT && command_code != COMMAND_ERROR && 
														no_more_zombies(table, N, M) == 1)
			{
				command_code = COMMAND_WIN;
			}
		} while (command_code != COMMAND_EXIT && command_code != COMMAND_WIN);

		free_tablo(table, N);
	
		if (command_code != COMMAND_EXIT){
			N++;
			M++;
			level++;

			if (N == END_N || M == END_M){
				printf("Levels %d, Points %d\n", level - 1, score);
				printf("All zombies are dead, the planet is safe!!!\n");
				command_code = COMMAND_VICTORY;
			}
		}
		
	} while (command_code != COMMAND_EXIT && command_code != COMMAND_VICTORY);
	
	
	return 0;
}