# 병행성
### Introduction
- - -
멀티 쓰레드는 멀티 프로세스와는 다르게 스택 이외의 주소 공간(프로그램 코드, 힙)을 공유한다.  
또한, 쓰레드끼리의 문맥 교환을 위해 `PCB`와는 별개로 `TCB(Thread Control Block)`이 필요하다.  
주소 공간을 공유하기 때문에, 쓰레드 끼리 같은 데이터를 편집하는 경우가 있는데, 이로 인해 비결정적인 결과가 발생할 수 있다.  
이를 `Race Condition`이라고 하며, `Race Condition`을 발생시키는 코드 부분을 `Critical Section`이라고 한다.  
이러한 문제에서 필요한 것은 `Mutual Exclusion`이라고 한다.
### Thread API
- - -
- `pthread_create(pthread_t *thread, const pthread_addr_t *attr, void *start_routine, void *arg)`
- `pthread_attr_init()`
- `pthread_join(pthread_t thread, void **value_prt)`
- `pthread_mutex_init(&lock, NULL)`
- `pthread_mutex_lock(pthread_mutex_t *mutex)`
- `pthread_mutex_unlock(pthread_mutex_t *mutex)` --> Lock을 획득한 쓰레드만이 Unlock을 호출해야 한다.
- `pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)`
- `pthread_cond_signal(pthread_cond_t *cond)`
### Lock
- - -
락은 Fairness, Starve, Performance의 관점에서 평가된다.  
- Interrupt Control
    - Mutual Exclusion: 확실하긴 함
    - Fairness(Starve): 운영체제마저 굶주릴 수 있음, 서로 신뢰할 수 있는 경우 사용 가능(커널)
    - Performance: CPU 낭비가 없긴 함
- Spin Lock(Test-And-Set, Compare-And-Swap)
  ```C
  int TestAndSet(itn *old_prt, int new) {
      int old = *old_ptr;
      *old_ptr = new;
      return old;
  }
  ```
  ```C
  int CompareAndSwap(int *ptr, int expected, int new) {
      int actual = *ptr;
      if (actual == expected) {
          *ptr = new;
      }
      return actual;
  }
  ```
    - Mutual Exclusion: 되긴 됨
    - Fairness(Starve): 문맥 교환 될때까지 계속 굶주림
    - Performance: 쓰레드 개수랑 CPU개수랑 비슷하면 낭비가 그나마 덜함
- Ticket Lock(Fetch-And-Add)
    ```C
  int FetchAndAdd(int *ptr) {
      int old = *ptr;
      *ptr = old + 1;
      return old;
  }
  ```
    - Mutual Exclusion: 확실하긴 함
    - Fairness(Starve): Ticket이 있어서 안 굶주림
    - Performance: Spin Lock과 매한가지
- Yield Lock(Test-And-Set)  
  자신이 할당받은 CPU 시간을 포기하고 다른 쓰레드가 실행될 수 있도록 하는 기법, deschedule
    - Mutual Exclusion: 확실하긴 함
    - Fairness(Starve): ??
    - Performance: Spin Lock보다 조금 나음
- Two Phase Lock
  락이 곧 해제될 것 같은 경우라면 회전 대기가 유용할 수 있다.
### 락 기반의 병행 자료 구조
- - -
- 병행 카운터
```C
typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} __counter_t;

void init(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    int rc = c->value;
    pthread_mutex_unlock(&c->lock);
    return rc;
}
```
이런 식으로 코딩하면 `완벽한 확정성(perfect scaling)`을 보장하지 못한다. 단일 쓰레드보다도 늦다.  
이를 해결하기 위해서 `엉성한 카운터(sloppy counter)`기법을 사용한다.  
여러 개의 지역 카운터와 하나의 전역 카운터를 갖고 있는데, 주기적으로 지역 카운터의 값을 전역 카운터에 더하는 방식을 이용한다.
빈도 S 값이 작을수록 확장성 없는 카운터처럼 동작하며, 커질수록 실제 값과 차이가 생기게 된다.
```C
typedef struct __counter_t {
    int global;
    pthread_mutex_t glock;
    int local[NUMCPU];
    pthread_mutex_t local_lock[NUMCPU];
    int threshold; // refresh freq
}

void init(counter_t *c, init threshold) {
    c->threshold = threshold;
    c->global = 0;
    pthread_mutex_init(&c->glock, NULL);
    !init all local lock;
}

void update(coutner_t *c, int threadID, int amt) {
    pthread_mutex_lock(&c->local_lock[threadID];
    c->local[threadID] += amt;
    pthread_mutex_lock(&c->local_lock[threadID];
    if (c->local[threadID] >= c->threshold) {
        pthread_mutex_lock(&c->glock);
        c->global += c->local[threadID];
        pthread_mutex_unlock(&c->glock);
        c->local[threadID] = 0;
    }
    pthread_mutex_unlock(&c->local_lock[threadID]);
}

int get(counter_t *c) {
    pthread_mutex_lock(&c->glock);
    int val = c->global;
    pthread_mutex_unlcok(&c->glock);
    return val;
}
```
- 병행 연결 리스트  
  산입 연산이 병행하여 진행되는 상황에서 실패를 하더라도 락 해제를 호출하지 않으면서 삽입과 검색이 올바르게 동작하도록 할 수 있을까?  
  --> 공유 리스트 갱신 부분이 아니면 락이 필요 없다!
```C
typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;

typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L) {
    L->head = NULL;
    pthread_mutex_init(&L->lock, NULL);
}

int List_Insert(list_t *L, int key) {
    pthread_mutex_lock(&L->lock); // 여기부터 lock을 걸 필요가 있을까?
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
    perror("malloc");
    pthread_mutex_unlock(&L->lock);
    return -1;
    }
    new->key = key;
    ### pthread_mutex_lock(&L->lock);
    new->next = L->head;
    L->head = new;
    pthread_mutex_unlock(&L->lock);
    return 0;
}

int List_Lookup(list_t *L, int key) {
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr) {
        if (curr->key == key) {
            pthread_mutex_unlock(&L->lock);
            return 0;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return -1;
}
```
- 병행 큐
```C
typedef struct __node_t {
    int value;
    struct __node_t *next;
} node_t;

typedef struct __queue_t {
    node_t *head;
    node_t *tail;
    pthread_mutex_t head_lock, tail_lock;
} queue_t;

void Queue_Init(queue_t *q) {
    node_t *tmp = malloc(sizeof(node_t));
    tmp->next = NULL;
    q->head = q->tail = tmp;
    pthread_mutex_init(&q->head_lock, NULL);
    pthread_mutex_init(&q->tail_lock, NULL);
}

void Queue_Enqueue(queue_t *q, int value) {
    node_t *tmp = malloc(sizeof(node_t));
    assert(tmp != NULL);
    tmp->value = value;
    tmp->next = NULL;
    pthread_mutex_lock(&q->tail_lock);
    q->tail->next = tmp;
    q->tail = tmp;
    pthread_mutex_unlock(&q->tail_lock);
}

int Queue_Dequeue(queue_t *q, int *value) {
    pthread_mutex_lock(&q->head_lock);
    node_t *tmp = q->head;
    node_t *new_head = tmp->next;
    if (new_head == NULL) {
        pthread_mutex_unlock(&q->head_lock);
        return -1; // queue was empty
    }
    *value = new_head->value;
    q->head = new_head;
    pthread_mutex_unlock(&q->head_lock);
    free(tmp);
    return 0;
}
```
- 병행 해시 테이블 (using concurrent linked list)
```
#define BUCKETS (101)
typedef struct __hash_t {
    list_t lists[BUCKETS];
} hash_t;

void Hash_Init(hash_t *H) {
    int i;
    for (i = 0; i < BUCKETS; i++)
        List_Init(&H->lists[i]);
}

int Hash_Insert(hash_t *H, int key) {
    return List_Insert(&H->lists[key % BUCKETS], key);
}

int Hash_Lookup(hash_t *H, int key) {
    return List_Lookup(&H->lists[key % BUCKETS], key);
}
```
`미숙하게 최적화(premature optimization)`를 피해야 한다.