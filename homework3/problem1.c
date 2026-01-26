#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 16
#define SENT_BUFF_SIZE 4096

#define ERR_OK              (-100)
#define ERR_INVALID_INPUT   (-101)

int isChar(const char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

int isDelimiter(char c) {
    return c == ' ' || c == ',' || c == '.';
}

int translateSentence(const char *sentence, char **dictionary, const int n, char **translated) {
    if (!sentence || !dictionary || !translated) {
        return ERR_INVALID_INPUT;
    }

    size_t cap = strlen(sentence) + 1;
    char *buffer = malloc(cap);
    if (!buffer) {
        return ERR_INVALID_INPUT;
    }

    size_t resLen = 0;
    int pos = 0;
    char word[MAX_WORD_LEN] = {0};

    while (sentence[pos]) {
        if (isDelimiter(sentence[pos])) {
            buffer[resLen++] = sentence[pos++];
            continue;
        }

        size_t len = 0;
        while (sentence[pos + len] && !isDelimiter(sentence[pos + len])) {
            if (len >= MAX_WORD_LEN - 1) { break; }
            word[len++] = sentence[pos + len];
        }
        word[len] = '\0';

        const char *toAdd = word;
        for (int i = 0; i < n; i++) {
            if (strcmp(word, dictionary[2 * i]) == 0) {
                toAdd = dictionary[2 * i + 1];
                break;
            }
        }

        size_t addLen = strlen(toAdd);
        memcpy(buffer + resLen, toAdd, addLen);
        resLen += addLen;

        pos += (int) len;
    }

    buffer[resLen] = '\0';

    char *shrunk = realloc(buffer, resLen + 1);
    *translated = shrunk ? shrunk : buffer;

    return ERR_OK;
}


void freeDictionary(char **dictionary, const int n) {
    if (!dictionary) { return; }

    for (int i = 0; i < n * 2; i++) { free(dictionary[i]); }
    free(dictionary);
}

int inputDictionary(char **dictionary, const int n) {
    assert(dictionary);

    for (int i = 0; i < n * 2; i++) {
        if (scanf("%15s", dictionary[i]) != 1) { return ERR_INVALID_INPUT; }
    }
    return ERR_OK;
}

int main() {
    int n;

    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input\n");
        return 1;
    }

    char **dictionary = calloc(2 * n, sizeof(char *));
    if (!dictionary) { return 1; }


    for (int i = 0; i < n * 2; i++) {
        dictionary[i] = calloc(MAX_WORD_LEN, sizeof(char));
        if (!dictionary[i]) {
            freeDictionary(dictionary, i);
            return 0;
        }
    }

    if (inputDictionary(dictionary, n) != ERR_OK) {
        freeDictionary(dictionary, n);
        return 1;
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    printf("Please add space as the end of the sentence");
    char sentence[SENT_BUFF_SIZE];
    if (!fgets(sentence, SENT_BUFF_SIZE, stdin)) {
        freeDictionary(dictionary, n);
        return 1;
    }

    char *translated = NULL;

    if (translateSentence(sentence, dictionary, n, &translated) != ERR_OK) {
        freeDictionary(dictionary, n);
        return 1;
    }

    printf("%s", translated);
    free(translated);

    freeDictionary(dictionary, n);
    return 0;
}
