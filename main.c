#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "spelling_game.h"
#include "c_utils.h"

#define CVECTOR_IMPLEMENTATION
#include "cvector.h"


int main(int argc, char** argv)
{
	char delims[] = "\n";
	c_array file_contents;

	if (argc != 2) {
		printf("Usage: %s wordlist\n", argv[0]);
		return 0;
	}

	if (!file_open_read(argv[1], "r", &file_contents)) {
		perror("Could not open file name given");
		return 0;
	}

	vector_str wordlist;
	if (!vec_str(&wordlist, 0, 100000)) {
		perror(NULL);
		return 0;
	}
	
	char* result = strtok((char*)file_contents.data, delims);
	while (result != NULL) {
		if (is_good_word(result))
			push_str(&wordlist, result);
	
		result = strtok(NULL, delims);
	}

	free(file_contents.data);

	qsort(wordlist.a, wordlist.size, sizeof(char*), compare_strings);

	char prefix_buf[10];
	char entry_buf[300];
	char* prefix = prefix_buf;	
	int n_chars;
	char* suffix_entry = NULL;
	vector_i correct_guesses;
	vec_i(&correct_guesses, 0, 20);
	int i, total_score = 0;

	srand(time(NULL));
	while (1) {                    //main game loop
		puts(CLEAR_SCREEN);
		int first_match, last_match, initial;

		initial = rand() % wordlist.size; //check wordlist.size < RAND_MAX
		n_chars = rand() % 3 + 2;
		while (strlen(wordlist.a[initial]) < n_chars) {
			printf("trying %s\n", wordlist.a[initial++]);
			if (initial >= wordlist.size)
				initial = rand() % wordlist.size; //check wordlist.size < RAND_MAX
		}

		memset(prefix_buf, 0, sizeof(prefix_buf));
		for (int i=0; i<n_chars; ++i) {
			prefix_buf[i] = wordlist.a[initial][i];
		}

		find_match_range(&wordlist, n_chars, prefix, initial, &first_match, &last_match);

		int bad_tries = 0;
		c_array correct_c_array;

		while (1) {

			while (bad_tries < 3 && correct_guesses.size != last_match - first_match + 1) {
				puts(CLEAR_SCREEN);
				for (int j=0; j<correct_guesses.size; ++j) {
					printf("%s ", wordlist.a[correct_guesses.a[j]]);
				}
				puts("\n");
				printf("Score: %d\t Bad Guesses: %d\n", total_score, bad_tries);
				printf("Enter \"q!\" to quit\n");
				printf("Finish as many words as you can that start with the prefix \"%s\"\n", prefix_buf);
				printf("%s", prefix_buf);
				suffix_entry = freadline(stdin);
				if (!strncmp("q!", suffix_entry, 2)) {
					free(suffix_entry);
					goto exit;
				}
						
				int len = snprintf(entry_buf, 300, "%s%s", prefix_buf, suffix_entry);
				if (len > 299) {
					puts("Error, your entry was too long\n");
					++bad_tries;
					free(suffix_entry);
					continue;
				}
				printf("full word: %s\n", entry_buf);
				for (i=first_match; i<=last_match; ++i) {
					SET_C_ARRAY(correct_c_array, (byte*)correct_guesses.a, sizeof(int), correct_guesses.size);

					if (is_any(&correct_c_array, (byte*)&i, are_equal_int)) {
						if (!strcmp(entry_buf, wordlist.a[i])) {
							printf("You've already used that word!\n");
							++bad_tries;
							break;
						}
						continue;
					}

					if (!strcmp(entry_buf, wordlist.a[i])) {
						printf("Good answer\n");
						push_i(&correct_guesses, i);
						++total_score;
						break;
					}
				}
				if (i > last_match) {
					printf("%s is not a word in the word list\n", entry_buf);
					++bad_tries;
				}

				getchar();
				free(suffix_entry);
			}
			
			int num_alternatives = 3;
			if (bad_tries == 3) {
				for (i=first_match; i<=last_match && num_alternatives; ++i) {
					SET_C_ARRAY(correct_c_array, (byte*)correct_guesses.a, sizeof(int), correct_guesses.size);
					if (is_any(&correct_c_array, (byte*)&i, are_equal_int)) {
						continue;
					}
					printf("You could have used \"%s\"\n", wordlist.a[i]);
					--num_alternatives;
				}
			}
			getchar();

			--n_chars;
			if (!n_chars) {
				correct_guesses.size = 0;
				break;
			}
			prefix_buf[n_chars] = 0;
			find_match_range(&wordlist, n_chars, prefix, initial, &first_match, &last_match); 
			bad_tries = 0;
		}
	}  //end main game loop

exit:
	free_vec_i(&correct_guesses);
	free_vec_str(&wordlist);

	return 0;
}
