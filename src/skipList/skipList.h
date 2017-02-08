#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

#define COUNT_SIZE(_K, _V, _L) (sizeof(_K)+sizeof(_V)+(_L)*sizeof(int*))
#define DEFAULT_LEVEL 5

template <class K, class V>
struct skNode {
    K key;
    V Val;
    skNode* link[0];
};

template <class K, class V>
struct skList {
public:
    skList();
    skList(int level);
    ~skList();
public:
    bool getValue(K key V& val) const;
    bool addTerm(K key, V val);
    bool delTerm(k key);
private:
    skNode<K, V>* m_head;
    int m_length;
    int m_level;
private:
    skList(const skList&);
    skList& operator=(const skList&);
};

template <class K, class V>
inline skList<K, V>::skList(){
    this.skList(DEFAULT_LEVEL);
}

template <class K, class V>
inline skList<K, V>::skList(int level){
    m_length = 0;
    m_level = level;
    m_head = (skNode*)malloc(COUNT_SIZE(K, V, level));
    for (int i = 0; i < m_level; ++i) {
        m_head->link[i] = 0;
    }
}

template <class K, class V>
inline skList<K, V>::~skList() {
    skNode<K, V> *tmp = m_head;
    while (m_head) {
        tmp = m_head;
        m_head = m_head->link[0];
        free(tmp);
    }
}

template <class K, class V>
inline bool skList<K, V>::getValue(K key, V& val) const {
    skNode<K, V> start = m_head;
    for (int i = m_level-1; i >= 0; --i) {
        skNode<K, V> p = start;
        while (p->link[i]) {
            if (p->link[i]->key == key) {
                val = p->val;
                return true;
            }
            if (p->link[i]->key > key) {
                break;
            }
            p = p->link[i];
        }
        start = p;
    }
    return false;
}

template <class K, class V>
inline bool skList<K, V>::addTerm(K key, V val) {
    if (getValue(key, V())) {
        return false;
    }
    int level = getlevel();
    skNode<K, V> *tmp = malloc(COUNT_SIZE(K, V, level));
    tmp->key = key;
    tmp->val = val;
    for (int i = 0; i < level; ++i) {
        tmp->link[i] = 0;
    }
    skNode<K, V> begin = m_head;
    for (int i = level-1; i >= 0; --i) {
        skNode<K, V> p = begin;
        while (p->link[i]) {
            if (p->link[i]->key > key) {
                break;
            }
            p = p->link[i];
        }
        begin = p;
        tmp->link[i] = p->link[i];
        p->link[i] = tmp;
    }
    m_length++;
    return true;
}

template <class K, class V>
inline bool skList<K, V>::delTerm(K key) {
    skNode<K, V>* start = m_head;
    skNode<K, V>* tmp = m_head;
    for (int i = m_level-1; i >= 0; --i) {
        skNode<K, V>* p = start;
        while (p->link[i]) {
            if (p->link[i]->key == key) {
                tmp = p->link[i];
                p->link[i] = tmp->link[i];
            }
            if (p->link[i]->key > key) {
                break;
            }
        }
        start = p;
    }
    return true;
}

#endif
