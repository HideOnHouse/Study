# Semaphore
lock과 condition 변수 모두 사용할 수 있는 방법.
### Definition
- - - 
```C
sem_init(sem_t *s, share, value);
sem_wait(sem_t *s); // 세마포어의 값을 1 감소시키고 음수면 wait
sem_post(sem_t *s); // 세마포어의 값을 1 증가시키고 기다리는 작업이 있으면 하나 깨움
```
### Consumer/Producer
- - -
```C
int buffer[MAX];
int fill = 0;
int use = 0;

void put(int value) {
	buffer[fill] = value;
	fill = (fill + 1) % MAX;
}

int get() {
	int tmp = buffer[use];
	use = (use + 1) % MAX;
	return tmp;
}

void *producer(void *arg) {
	int i;
	for (i = 0; i < loops; i++) {
		sem_wait(&empty);
		sem_wait(&mutex);
		put(i);
		sem_post(&mutex);
		sem_post(&full);
	}
}

void *consumer(void *arg) {
	int i;
	for (i = 0; i < loops; i++) {
		sem_wait(&full);
		sem_wait(&mutex);
		int tmp = get();
		sem_post(&mutex);
		sem_post(&empty);
		printf("%d\n", tmp);
	}
}
```
### Reader-Writer Lock
- - -
```C
typedef struct _rwlock_t {
	sem_t lock; // binary semaphore (basic lock)
	sem_t writelock; // allow ONE writer/MANY readers
	int readers; // #readers in critical section
} rwlock_t;

void rwlock_init(rwlock_t *rw) {
	rw->readers = 0;
	sem_init(&rw->lock, 0, 1);
	sem_init(&rw->writelock, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t *rw) {
	sem_wait(&rw->lock);
	rw->readers++;
	if (rw->readers == 1) // first reader gets writelock
		sem_wait(&rw->writelock);
	sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t *rw) {
	sem_wait(&rw->lock);
	rw->readers--;
	if (rw->readers == 0) // last reader lets it go
		sem_post(&rw->writelock);
	sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw) {
	sem_wait(&rw->writelock);
}

void rwlock_release_writelock(rwlock_t *rw) {
	sem_post(&rw->writelock);
}
```