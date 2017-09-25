//LRU Cache

/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache(2);

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
*/

/*
设计一个LRU的类，要求完成key，value存取为O(1)的时间复杂度
----------------------------------------------------------------------------------------------------------------------------------------------------------
1.第一个想法是维护一个双向链表，链表头表示最近最少访问的节点，链表尾部表示最近访问的节点。链表的数据存的是key-value值。然后维护一个hashmap，hashmap的键是key，值是链表的节点指针。
进行get操作，查找hashmap，找到对应节点指针，取出值，然后将这个节点挂载到链表的尾部;进行put操作时，判断是否大于缓存的容量 a)小于的情况简单，添加一个节点到链表尾部，添加hashmap
b)大于或者等于的情况，找到链表的头节点，根据key删除hashmap中对应项，插入新项，将头节点挂载到链表的尾部
*/
class LRUCache 
{
private:
	struct ListNode 
	{
		int key;
		int value;
		ListNode *next;
		ListNode *pre;
		ListNode(int x, int y) : key(x), value(y), next(0), pre(0) {}
	};
	int cap;
	int size;
	unordered_map<int, ListNode *> mp;
	ListNode *head, *tail;
	//将p节点调整到链表尾部
	inline void move_to_tail(ListNode *p)
	{
		//已经在尾部
		if(p == tail) return;
		//调整的节点是头节点
		if(p == head)
		{
			head = head->next;
			head->pre = 0;
		}
		else
		{
			p->pre->next = p->next;
			p->next->pre = p->pre;
		}
		tail->next = p;
		p->pre = tail;
		p->next = 0;
		tail = p;
	}
public:
    LRUCache(int capacity) 
	{
		this->cap = capacity;
		size = 0;
		head = 0, tail = 0;
    }
    
    int get(int key) 
	{
		ListNode *p;
		if(!mp.count(key)) return -1;
		move_to_tail(mp[key]);
		return mp[key]->value;
    }
    
    void put(int key, int value) 
	{
		/*
		*相同的key已经在cache中, e.g. put(1, 1), put(1, 2)
		*需要做的是更新链表的value，然后调整到链表的尾部
		*/
		if(mp.count(key))
		{
			move_to_tail(mp[key]);
			mp[key]->value = value;
			return;
		}
		//小于目前的缓存容量
		if(size < cap)
		{
			mp[key] = new ListNode(key, value);
			++size;
			if(!head)
				head = tail = mp[key];
			else
			{
				tail->next = mp[key];
				tail->next->pre = tail;
				tail = tail->next;
			}
			return;
		}
		//最少访问的删除
		mp.erase(head->key);
		//重新利用原来链表的节点，加快速度
		head->key = key;
		head->value = value;
		mp[key] = head;
		move_to_tail(head);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */


/*
这才是标准的c++代码，人家说的好，上面的一百多行c++代码都不够简洁，属于重复造车轮子。
上面的链表完全可以用stl的list代替，然后代码就简单很多了

*/
class LRUCache {
public:
    LRUCache(int capacity) : _capacity(capacity) {}
    
    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end()) return -1;
        touch(it);
        return it->second.first;
    }
    
    void set(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end()) touch(it);
        else {
			if (cache.size() == _capacity) {
				cache.erase(used.back());
				used.pop_back();
			}
            used.push_front(key);
        }
        cache[key] = { value, used.begin() };
    }
    
private:
    typedef list<int> LI;//需要存储的key的list
    typedef pair<int, LI::iterator> PII;
    typedef unordered_map<int, PII> HIPII;//map的键是需要存储的key，值是pair类型(需要存储的value，在list中迭代器的位置) 这里需要注意的是list的迭代器不会失效，除非这个元素被删除了
    
    void touch(HIPII::iterator it) {
        int key = it->first;
        used.erase(it->second.second);
        used.push_front(key);
        it->second.second = used.begin();
    }
    
    HIPII cache;
    LI used;
    int _capacity;
};