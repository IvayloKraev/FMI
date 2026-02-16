#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 32
#define SENT_BUFF_SIZE 1024

#define ERR_OK          (-100)
#define ERR_MEMORY      (-101)

char toLowerChar(const char c) {
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

void toLower(char *c) {
    while (*c) {
        *c = toLowerChar(*c);
        ++c;
    }
}

int stricmp(const char *s1, const char *s2) {
    for (;; s1++, s2++) {
        const int diff = toLowerChar(*s1) - toLowerChar(*s2);
        if (diff != 0 || *s1 == '\0') return diff;
    }
}

int isChar(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '-';
}

int wordCount(const char *s) {
    int count = 0;
    while (*s) {
        if (isChar(*s)) {
            while (*s && isChar(*s)) {
                ++s;
            }
            ++count;
        } else {
            ++s;
        }
    }
    return count;
}

// *s must point to the first character of the word
// returns the size of the word
size_t getWord(const char *s, char *word, const int maxWordLen) {
    size_t wordLen = 0;
    while (*s && isChar(*s)) {
        if (wordLen >= maxWordLen) {
            word[0] = '\0';
            return 0;
        }
        word[wordLen++] = *s++;
    }
    word[wordLen] = '\0';
    return wordLen;
}

// returns the needed jump to skip whitespace
size_t whitespaceLen(const char *s) {
    size_t jump = 0;
    while (*(s + jump) && !isChar(*(s + jump))) {
        jump++;
    }
    return jump;
}


int compress(const char *sentence, const size_t numOfWords, int *compressed, char **legend, int *len) {
    assert(sentence != NULL);
    assert(compressed != NULL);
    assert(legend != NULL);

    char **words = (char **) malloc(sizeof(char *) * numOfWords);
    int *wordCounts = (int *) malloc(sizeof(int) * numOfWords);

    if (!words || !wordCounts) {
        free(words);
        free(wordCounts);
        return ERR_MEMORY;
    }


    int uniqueWords = 0;
    for (size_t i = 0, pos = 0; i < numOfWords; i++) {
        char word[MAX_WORD_LENGTH] = {};
        const size_t wordLen = getWord(sentence + pos, word, MAX_WORD_LENGTH);

        int found = 0;
        for (size_t j = 0; j < uniqueWords; j++) {
            if (stricmp(words[j], word) == 0) {
                ++wordCounts[j];
                found = 1;
                break;
            }
        }
        if (!found) {
            words[uniqueWords] = malloc(sizeof(char) * wordLen + 1);
            if (!words[uniqueWords]) {
                for (size_t k = 0; k < uniqueWords; k++) free(words[k]);
                free(words);
                free(wordCounts);
                return ERR_MEMORY;
            }

            toLower(word);
            memcpy(words[uniqueWords], word, sizeof(char) * wordLen + 1);
            wordCounts[uniqueWords] = 1;
            ++uniqueWords;
        }
        pos += wordLen;
        pos += whitespaceLen(sentence + pos);
    }
    *len = uniqueWords;

    for (size_t i = 0; i < uniqueWords; i++) {
        size_t maxIdx = i;

        for (size_t j = i + 1; j < uniqueWords; j++) {
            if (
                wordCounts[j] > wordCounts[maxIdx] ||
                (wordCounts[j] == wordCounts[maxIdx] &&
                 strcmp(words[j], words[maxIdx]) < 0)
            ) {
                maxIdx = j;
            }
        }

        if (maxIdx != i) {
            int tmpCount = wordCounts[i];
            wordCounts[i] = wordCounts[maxIdx];
            wordCounts[maxIdx] = tmpCount;

            char *tmpWord = words[i];
            words[i] = words[maxIdx];
            words[maxIdx] = tmpWord;
        }
    }


    for (size_t i = 0, pos = 0; i < numOfWords; i++) {
        char word[MAX_WORD_LENGTH] = {};
        const size_t wordLen = getWord(sentence + pos, word, MAX_WORD_LENGTH);

        for (size_t j = 0; j < uniqueWords; j++) {
            if (stricmp(words[j], word) == 0) {
                compressed[i] = j;
                break;
            }
        }

        pos += wordLen;
        pos += whitespaceLen(sentence + pos);
    }

    for (int i = 0; i < uniqueWords; i++) {
        legend[i] = words[i];
        words[i] = NULL;
    }


    for (int i = 0; i < uniqueWords; i++) {
        free(words[i]);
    }
    free(words);
    free(wordCounts);

    return ERR_OK;
}

int decompress(const int *compressed, const char **legend, const size_t sentenceLen, const size_t uniqueWords,
               char *sentence) {
    assert(sentence);
    assert(legend);
    assert(compressed);

    size_t pos = 0;
    for (size_t i = 0; i < sentenceLen; i++) {
        const char *w = legend[compressed[i]];
        size_t wl = strlen(w);

        memcpy(sentence + pos, w, wl);
        pos += wl;

        if (i + 1 < sentenceLen) {
            sentence[pos++] = ' ';
        }
    }
    sentence[pos] = '\0';
    return ERR_OK;
}


int main() {
    const char *sentence = "The quick brown fox jumped over the brown dog on the chair.";
    char *sentenceRes = malloc(sizeof(char) * SENT_BUFF_SIZE);
    const size_t numOfWords = wordCount(sentence);

    int *compressed = malloc(sizeof(int) * numOfWords);
    char **legend = malloc(sizeof(char *) * numOfWords);
    if (!compressed || !legend) {
        free(compressed);
        free(legend);
        free(sentenceRes);
        return 1;
    }
    int uniqueWords = 0;

    int err = compress(sentence, numOfWords, compressed, legend, &uniqueWords);
    if (err != ERR_OK) {
        free(compressed);
        for (size_t k = 0; k < uniqueWords; k++) free(legend[k]);
        free(legend);
        free(sentenceRes);
        return 1;
    }

    int err1 = decompress( compressed, (const char**)legend, numOfWords, uniqueWords, sentenceRes);

    for (int i = 0; i < numOfWords; i++) {
        printf("%d ", compressed[i]);
    }

    printf("\n");

    for (int i = 0; i < uniqueWords; i++) {
        printf("%s ", legend[i]);
    }
    printf("\n");

    puts(sentenceRes);


    for (size_t k = 0; k < uniqueWords; k++) free(legend[k]);
    free(legend);
    free(compressed);
    free(sentenceRes);

    return 0;
}
