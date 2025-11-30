#include <stdlib.h>
#include <string.h>
#include "struct.h"

static const uint32_t INITIAL_CAPACITY = 53;

#define HT_PRIME_1 151
#define HT_PRIME_2 163

static int Hash(const char *s, int a, int m) {
    long hash = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        hash = (hash * a + s[i]) % m;
    }

    return (int)hash;
}

static int GetHash(const char *s, int num_buckets, int attempt) {
    int hash_a = Hash(s, HT_PRIME_1, num_buckets);
    int hash_b = Hash(s, HT_PRIME_2, num_buckets);

    return (hash_a + attempt * (hash_b + 1)) % num_buckets;
}

static HashNode *CreateNode(const char *key, const char *value) {
    if (key == NULL || value == NULL) {
        return NULL;
    }

    HashNode *node = malloc(sizeof(HashNode));
    if (node == NULL) {
        return NULL;
    }

    node->key = strdup(key);
    node->value = strdup(value);

    if (node->key == NULL || node->value == NULL) {
        free(node->key);
        free(node->value);
        free(node);
        return NULL;
    }

    return node;
}

static void DeleteNode(HashNode *node) {
    if (node == NULL) {
        return;
    }

    free(node->key);
    free(node->value);
    free(node);
}

HashTable *CreateHashTable(void) {
    HashTable *table = malloc(sizeof(HashTable));
    if (table == NULL) {
        return NULL;
    }

    table->capacity = INITIAL_CAPACITY;
    table->size = 0;

    table->buckets = calloc(table->capacity, sizeof(HashNode *));
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }

    return table;
}

void DeleteHashTable(HashTable *table) {
    if (table == NULL) {
        return;
    }

    for (uint32_t i = 0; i < table->capacity; i++) {
        if (table->buckets[i] != NULL) {
            DeleteNode(table->buckets[i]);
        }
    }

    free(table->buckets);
    free(table);
}