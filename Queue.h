#pragma once
#ifndef QUEUE_H_
#define QUEUE_H_

#include "utility.h"

template <typename T>
class Queue {
	int size;
	T * que;
	int head;
	int tail;

public:

	Queue() {
		size = 0;
		que = NULL;
		head = tail = 0;
	}

	~Queue() {
		fout << size << "BYE" << std::endl;
		if (que) {
			delete [] que;
			que = NULL;
		}
	}

	void Resize(int size_) {
		if (que) {
			delete [] que;
		}
		size = size_ + 1;
		que = new T[size];
	}

	int Count() {
		return ((tail - head) + size) % size;
	}

	bool Push(T to_push) {
		if (Count() >= size - 1) {
			return false;
		}
		que[tail++] = to_push;
		if (tail == size) {
			tail = 0;
		}
		return true;
	}

	bool Pop() {
		if (Count() <= 0) {
			return false;
		}
		++head;
		if (head == size) {
			head = 0;
		}
		return true;
	}

	T GetLeft() {
		return que[head];
	}

	T GetRight() {
		return que[((tail - 1) + size) % size];
	}

	T Get(int idx) {
		return que[(head + idx) % size];
	}
};

#endif // !QUEUE_H_

