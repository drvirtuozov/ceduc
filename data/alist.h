typedef struct alist_node_t {
  char *key;
  char *value;
  struct alist_node_t *next;
} alist_node_t;

alist_node_t *alist_node_new(char *key, char *val);
alist_node_t *alist_add(alist_node_t **node, char *key, char *val);
alist_node_t *alist_get(alist_node_t *node, char *key);
unsigned int alist_getlen(alist_node_t *node);