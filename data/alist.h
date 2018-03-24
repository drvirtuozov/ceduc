#include <wchar.h>

typedef struct alist_node_t {
  wchar_t *key;
  wchar_t *value;
  struct alist_node_t *next;
} alist_node_t;

alist_node_t *alist_node_new(wchar_t *key, wchar_t *val);
alist_node_t *alist_add(alist_node_t **node, wchar_t *key, wchar_t *val);
alist_node_t *alist_get(alist_node_t *node, wchar_t *key);
alist_node_t *alist_delete(alist_node_t **node, wchar_t *key);
unsigned int alist_getlen(alist_node_t *node);