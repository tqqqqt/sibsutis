#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstring>
#include <conio.h>

const int field_size = 10;
const int need_live_plant = 2 + rand() % 3;
const int need_rabbit_move = 1 + rand() % 4;
const int need_wolf_move = 1 + rand() % 3;

struct field_data {
	int data = 0;
	char symbol[2] {};
	int count = 0;
};

struct delete_check {
	int x {};
	int y {};
};

class creature {
	protected:
		int x, y;
	public:
		creature(void) {
			x = rand() % field_size;
			y = rand() % field_size;
		}
		virtual void write(struct field_data field[field_size][field_size]) = 0;
		virtual void check(struct field_data field[field_size][field_size]) = 0;
};

class plant :public creature {
	protected:
		struct plant_data {
			int xx;
			int yy;
			int cikl;
			plant_data* next;
		};
		struct plant_data* p, * head, * tail, *q;
		bool new_plant;
	public:
		plant(struct field_data field[field_size][field_size]):q(NULL),head(new plant_data), p(new plant_data) {
			head->xx = -5;
			head->next = NULL;
			tail = head;
			p->xx = x;
			p->yy = y;
			if (field[p->yy][p->xx].data != 0) while (field[p->yy][p->xx].data != 0) {
					p->xx = rand() % field_size;
					p->yy = rand() % field_size;
				}
			field[p->yy][p->xx].data = 1;
			p->cikl = 5;
			p->next = NULL;
			tail->next = p;
			tail = p;
			new_plant = false;
		}
		void del_plant(int need_x, int need_y) {
			struct plant_data* d;
			d = head;
			for (q = head->next; q; q = q->next) {
				if (q->xx == need_x && q->yy == need_y && d->next == q) {
					d->next = q->next;
					delete(q);
					break;
				} else d = d->next;
			}
		}
		void check(struct field_data field[field_size][field_size]) {
			delete_check* mas;
			int count = 0, i = 0;
			for (p = head->next; p; p = p->next) {
				if (p) if (p->cikl == 0) count += 1;
			}
			mas = new delete_check[count];
			for (p = head->next; p; p = p->next) {
				if (p) if (p->cikl == 0) {
						mas[i].x = p->xx;
						mas[i].y = p->yy;
						i += 1;
						field[p->yy][p->xx].data = 0;
						field[p->yy][p->xx].count = 0;
						strcpy(field[p->yy][p->xx].symbol, " ");
					}
			}
			for (int j = 0; j < count; j++) del_plant(mas[j].x, mas[j].y);
			delete[] mas;
		}
		void add_plant(struct field_data field[field_size][field_size], int count=2) {
			for(int i=1; i<=count; i++) {
				p = new plant_data;
				p->xx = rand() % field_size;
				p->yy = rand() % field_size;
				if(field[p->yy][p->xx].data != 0) while (field[p->yy][p->xx].data != 0) {
						p->xx = rand() % field_size;
						p->yy = rand() % field_size;
					}
				field[p->yy][p->xx].data = 1;
				p->cikl = 5;
				p->next = NULL;
				tail->next = p;
				tail = p;
			}
			tail->next = NULL;
		}
		void write(struct field_data field[field_size][field_size]) {
			check(field);
			for (q = head->next; q; q = q->next) {
				q->cikl -= 1;
				field[q->yy][q->xx].data = 1;
				strcpy(field[q->yy][q->xx].symbol, "C");
				field[q->yy][q->xx].count = 1;
			}
		}
};

class rabbit :public creature {
	protected:
		struct rabit_data {
			int xx {};
			int yy {};
			int old_x {};
			int old_y {};
			double hunger {};
			struct rabit_data* next = NULL;
		};
		struct rabit_data* head, * tail, * p, * d, * q;
		const int ver = 25;
	public:
		rabbit(struct field_data field[field_size][field_size]):d(NULL), q(NULL), head(new rabit_data), p(new rabit_data) {
			head->next = NULL;
			tail = head;
			p->xx = x;
			p->yy = y;
			if (field[p->yy][p->xx].data != 0) while (field[p->yy][p->xx].data != 0) {
					p->xx = rand() % field_size;
					p->yy = rand() % field_size;
				}
			field[p->yy][p->xx].data = 2;
			p->old_x = p->xx;
			p->old_y = p->yy;
			p->next = NULL;
			p->hunger = 1.0;
			tail->next = p;
			tail = p;
		}
		void rabbit_add(struct field_data field[field_size][field_size], int count=2) {
			for (int i = 1; i <= count; i++) {
				p = new rabit_data;
				p->xx = rand() % field_size;
				p->yy = rand() % field_size;
				if (field[p->yy][p->xx].data != 0) while (field[p->yy][p->xx].data != 0) {
						p->xx = rand() % field_size;
						p->yy = rand() % field_size;
					}
				field[p->yy][p->xx].data = 2;
				p->old_x = p->xx;
				p->old_y = p->yy;
				p->hunger = 1.0;
				p->next = NULL;
				tail->next = p;
				tail = p;
			}
			tail->next = NULL;
		}
		void rabbit_add(struct field_data field[field_size][field_size], int need_x, int need_y) {
			p = new rabit_data;
			p->xx = need_x;
			p->yy = need_y;
			field[p->yy][p->xx].data = 2;
			p->old_x = p->xx;
			p->old_y = p->yy;
			p->hunger = 1.0;
			p->next = NULL;
			tail = head;
			while (tail->next) tail = tail->next;
			tail->next = p;
			tail = p;
			tail->next = NULL;
		}
		void del_rabit(int need_x, int need_y) {
			struct rabit_data* d;
			d = head;
			for (q = head->next; q; q = q->next) {
				if (q->xx == need_x && q->yy == need_y && d->next == q) {
					d->next = q->next;
					delete q;
					break;
				} else d = d->next;
			}
		}
		void write(struct field_data field[field_size][field_size]) {
			int chance = 0;
			p = head->next;
			while (p) {
				chance = 1 + rand() % 100;
				if (chance <= ver) rabbit_add(field, p->old_x, p->old_y);
				p->hunger -= 0.4;
				p = p->next;
			}
			for (p = head->next; p; p = p->next) {
				if (p->old_x != p->xx || p->old_y != p->yy) {
					field[p->old_y][p->old_x].data = 0;
					strcpy(field[p->old_y][p->old_x].symbol, " ");
					field[p->old_y][p->old_x].count = 0;
					p->old_x = p->xx;
					p->old_y = p->yy;
				}
				field[p->yy][p->xx].data = 2;
				strcpy(field[p->yy][p->xx].symbol, "R");
				field[p->yy][p->xx].count = 1;
			}
		}
		void check(struct field_data field[field_size][field_size]) {
			delete_check* mas;
			int count = 0, i = 0;
			for (p = head->next; p; p = p->next) {
				if (p) if (p->hunger <= 0) count += 1;
			}
			mas = new delete_check[count];
			for (p = head->next; p; p = p->next) {
				if (p) if (p->hunger <= 0) {
						mas[i].x = p->xx;
						mas[i].y = p->yy;
						i += 1;
						field[p->yy][p->xx].data = 0;
						field[p->yy][p->xx].count = 0;
						strcpy(field[p->yy][p->xx].symbol, " ");
					}
			}
			for (int j = 0; j < count; j++) del_rabit(mas[j].x, mas[j].y);
			delete[] mas;
		}
		int rabit_situation(struct field_data field[field_size][field_size], class plant plant) {
			if (field[p->yy][p->xx].data == 1) {
				plant.del_plant(p->yy, p->xx);
				field[p->yy][p->xx].data = 2;
				p->hunger += 0.2;
				return 1;
			} else if (field[p->yy][p->xx].data == 2 || field[p->yy][p->xx].data == 3) {
				p->yy = p->old_y;
				p->xx = p->old_x;
				return 2;
			} else if (field[p->yy][p->xx].data == 0) {
				field[p->yy][p->xx].data = 2;
				return 1;
			} else return 2;
		}
		void move(struct field_data field[field_size][field_size], class plant plant) {
			int ran_move = 0;
			int try_move = 0;
			p = head -> next;
			if (p) check(field);
			p = head->next;
			while(p) {
				if (p->xx == 0) {
					if (p->yy == 0) {
						ran_move = 1 + rand() % 3;
						switch (ran_move) {
							case 1:
								p->xx += 1;
								break;
							case 2:
								p->xx += 1;
								p->yy += 1;
								break;
							case 3:
								p->yy += 1;
								break;
						}
					} else if (p->yy == field_size - 1) {
						ran_move = 1 + rand() % 3;
						switch (ran_move) {
							case 1:
								p->yy -= 1;
								break;
							case 2:
								p->xx += 1;
								p->yy -= 1;
								break;
							case 3:
								p->xx += 1;
								break;
						}
					} else if (p->yy > 0 && p->yy < field_size - 1) {
						ran_move = 1 + rand() % 5;
						switch (ran_move) {
							case 1:
								p->yy -= 1;
								break;
							case 2:
								p->yy -= 1;
								p->xx += 1;
								break;
							case 3:
								p->xx += 1;
								break;
							case 4:
								p->xx += 1;
								p->yy += 1;
								break;
							case 5:
								p->yy += 1;
								break;
						}
					}
				} else if (p->xx == field_size - 1) {
					if (p->yy == 0) {
						ran_move = 1 + rand() % 3;
						switch (ran_move) {
							case 1:
								p->xx -= 1;
								break;
							case 2:
								p->xx -= 1;
								p->yy += 1;
								break;
							case 3:
								p->yy += 1;
								break;
						}
					} else if (p->yy == field_size - 1) {
						ran_move = 1 + rand() % 3;
						switch (ran_move) {
							case 1:
								p->yy -= 1;
								break;
							case 2:
								p->xx -= 1;
								p->yy -= 1;
								break;
							case 3:
								p->xx -= 1;
								break;
						}
					} else if (p->yy > 0 && p->yy < field_size - 1) {
						ran_move = 1 + rand() % 5;
						switch (ran_move) {
							case 1:
								p->yy -= 1;
								break;
							case 2:
								p->yy += 1;
								break;
							case 3:
								p->xx -= 1;
								p->yy += 1;
								break;
							case 4:
								p->xx -= 1;
								break;
							case 5:
								p->xx -= 1;
								p->yy -= 1;
								break;
						}
					}
				} else if (p->xx > 0 && p->xx < field_size - 1 && (p->yy == 0 || p->yy == field_size - 1)) {
					if (p->yy == 0) {
						ran_move = 1 + rand() % 5;
						switch (ran_move) {
							case 1:
								p->xx += 1;
								break;
							case 2:
								p->xx += 1;
								p->yy += 1;
								break;
							case 3:
								p->yy += 1;
								break;
							case 4:
								p->xx -= 1;
								p->yy += 1;
								break;
							case 5:
								p->xx -= 1;
								break;
						}
					} else if (p->yy == field_size - 1) {
						ran_move = 1 + rand() % 5;
						switch (ran_move) {
							case 1:
								p->xx -= 1;
								break;
							case 2:
								p->xx -= 1;
								p->yy -= 1;
								break;
							case 3:
								p->yy -= 1;
								break;
							case 4:
								p->xx += 1;
								p->yy -= 1;
								break;
							case 5:
								p->xx += 1;
								break;
						}
					}
				} else {
					ran_move = 1 + rand() % 8;
					switch (ran_move) {
						case 1:
							p->yy -= 1;
							break;
						case 2:
							p->xx += 1;
							p->yy -= 1;
							break;
						case 3:
							p->xx += 1;
							break;
						case 4:
							p->xx += 1;
							p->yy += 1;
							break;
						case 5:
							p->yy += 1;
							break;
						case 6:
							p->xx -= 1;
							p->yy += 1;
							break;
						case 7:
							p->xx -= 1;
							break;
						case 8:
							p->xx -= 1;
							p->yy -= 1;
							break;
					}
				}
				if (rabit_situation(field, plant) == 1) {
					p->hunger -= 0.20;
					field[p->old_y][p->old_x].data = 0;
					p = p->next;
				} else try_move += 1;
				if (try_move >= 6) {
					p = p->next;
					try_move = 0;
				}
			}
		}
};

class wolf :public creature {
	protected:
		struct wolf_data {
			int xx {};
			int yy {};
			int old_x {};
			int old_y {};
			double hunger=1.0;
			int flag_move=0;
			int kils =0;
			bool live = false;
			wolf_data* next = NULL;
		};
		struct wolf_data* head, * tail, * p, * q, * d;
		static int count_wolf;
	public:
		wolf(struct field_data field[field_size][field_size]): q(NULL), d(NULL), head(new wolf_data), p(new wolf_data) {
			head->next = NULL;
			tail = head;
			p->xx = x;
			p->yy = y;
			if (field[p->yy][p->xx].data != 0) while (field[p->yy][p->xx].data != 0) {
					p->xx = rand() % field_size;
					p->yy = rand() % field_size;
				}
			field[p->yy][p->xx].data = 3;
			p->old_x = p->xx;
			p->old_y = p->yy;
			p->hunger = 1.0;
			p->kils = 0;
			p->flag_move = 0;
			p->live = false;
			p->next = NULL;
			tail->next = p;
			tail = p;
			count_wolf += 1;
		}
		void wolf_add(struct field_data field[field_size][field_size], int count=2) {
			for (int i = 1; i <= count; i += 1) {
				p = new wolf_data;
				p->xx = rand() % field_size;
				p->yy = rand() % field_size;
				if (field[p->yy][p->xx].data != 0) while (field[p->yy][p->xx].data != 0) {
						p->xx = rand() % field_size;
						p->yy = rand() % field_size;
					}
				field[p->yy][p->xx].data = 3;
				p->old_x = p->xx;
				p->old_y = p->yy;
				p->hunger = 1.0;
				p->kils = 0;
				p->flag_move = 0;
				p->next = NULL;
				tail->next = p;
				tail = p;
				count_wolf += 1;
			}
			tail->next = NULL;
		}
		void wolf_delete(int need_x, int need_y) {
			struct wolf_data* d;
			d = head;
			for (q = head->next; q; q = q->next) {
				if (q->xx == need_x && q->yy == need_y && d->next == q) {
					d->next = q->next;
					delete(q);
					count_wolf -= 1;
					break;
				} else d = d->next;
			}
		}
		void wolf_add(struct field_data field[field_size][field_size], int need_x, int need_y) {
			p = new wolf_data;
			p->xx = need_x;
			p->yy = need_y;
			field[p->yy][p->xx].data = 3;
			p->old_x = p->xx;
			p->old_y = p->yy;
			p->hunger = 1.0;
			p->kils = 0;
			p->flag_move = 0;
			p->next = NULL;
			tail = head;
			while (tail->next) tail = tail->next;
			tail->next = p;
			tail = p;
			count_wolf += 1;
		}
		void check(struct field_data field[field_size][field_size]) {
			delete_check* mas;
			int count = 0, i = 0;
			for (p = head->next; p; p = p->next) {
				if (p) if (p->hunger <= 0) count += 1;
			}
			mas = new delete_check[count];
			for (p = head->next; p; p = p->next) {
				if (p) if (p->hunger <= 0) {
						mas[i].x = p->xx;
						mas[i].y = p->yy;
						i += 1;
						field[p->yy][p->xx].data = 0;
						field[p->yy][p->xx].count = 0;
						strcpy(field[p->yy][p->xx].symbol, " ");
					}
			}
			for (int j = 0; j < count; j++) wolf_delete(mas[j].x, mas[j].y);
			delete[] mas;

			while (count_wolf < 5) {
				for (int i = 0; i < field_size; i += 9) {
					for (int j = 0; j < field_size; j += 1) {
						if (count_wolf >= 5) break;
						if (field[i][j].data == 0) wolf_add(field, j, i);
						if (field[j][i].data == 0) wolf_add(field, i, j);
					}
					if (count_wolf >= 5) break;
				}
			}
		}
		void write(struct field_data field[field_size][field_size]) {
			for (p = head->next; p; p = p->next) {
				if (p && (p->xx >= 0 && p->xx <= 9) && (p->yy >= 0 && p->yy <= 9)) {
					if (p->old_x != p->xx || p->old_y != p->yy) {
						if ((p->old_x>=0 && p->old_x<=9) && (p->old_y>=0 && p->old_y<=9)) {
							field[p->old_y][p->old_x].data = 0;
							strcpy(field[p->old_y][p->old_x].symbol, " ");
							field[p->old_y][p->old_x].count = 0;
						}
						p->old_x = p->xx;
						p->old_y = p->yy;
					}
					field[p->yy][p->xx].data = 3;
					strcpy(field[p->yy][p->xx].symbol, "W");
					field[p->yy][p->xx].count = 1;
				}
			}
		}
		int wolf_situation(struct field_data field[field_size][field_size], class rabbit rabit) {
			if (field[p->yy][p->xx].data == 3) {
				p->yy = p->old_y;
				p->xx = p->old_x;
				return 2;
			} else if (field[p->yy][p->xx].data == 2) {
				rabit.del_rabit(p->xx, p->yy);
				p->kils += 1;
				p->hunger += 0.2;
				field[p->yy][p->xx].data = 3;
				if (p) if (p->kils == 2 && p->live == false) {
						wolf_add(field, p->old_x, p->old_y);
						p->live = true;
					}
				return 1;
			} else if (field[p->yy][p->xx].data == 1) {
				return 1;
			} else if (field[p->yy][p->xx].data == 0) {
				field[p->yy][p->xx].data = 3;
				return 1;
			} else return 2;
		}
		virtual void move(struct field_data field[field_size][field_size], class rabbit rabit) {
			int ran_move = 0;
			int try_move = 0;
			check(field);
			p = head->next;
			while(p) {
				if (p->hunger < 0.5) p->flag_move = 1;
				if (p->xx == 0) {
					if (p->yy == 0) {
						ran_move = 1 + rand() % 3;
						switch (ran_move) {
							case 1:
								if (p->flag_move == 0) p->xx += 1;
								else p->xx += 2;
								break;
							case 2:
								if (p->flag_move == 0) {
									p->xx += 1;
									p->yy += 1;
								} else {
									p->xx += 2;
									p->yy += 2;
								}
								break;
							case 3:
								if (p->flag_move == 0) {
									p->yy += 1;
								} else p->yy += 2;
								break;
						}
					} else if (p->yy == field_size - 1) {
						ran_move = 1 + rand() % 3;
						switch (ran_move) {
							case 1:
								if (p->flag_move == 0) p->yy -= 1;
								else p->yy -= 2;
								break;
							case 2:
								if (p->flag_move == 0) {
									p->xx += 1;
									p->yy -= 1;
								} else {
									p->xx += 2;
									p->yy -= 2;
								}
								break;
							case 3:
								if (p->flag_move == 0) p->xx += 1;
								else p->xx += 2;
								break;
						}
					} else if (p->yy > 0 && p->yy < field_size - 1 ) {
						ran_move = 1 + rand() % 5;
						switch (ran_move) {
							case 1:
								if (p->flag_move == 0 || (p->flag_move==1 && p->xx>7)) p->xx += 1;
								else if(p->xx <=7) p->xx += 2;
								break;
							case 2:
								if (p->flag_move == 0 || (p->flag_move==1 && (p->xx>7 || p->yy>7 ))) {
									p->xx += 1;
									p->yy += 1;
								} else {
									p->xx += 2;
									p->yy += 2;
								}
								break;
							case 3:
								if (p->flag_move == 0 || (p->flag_move==1 && p->yy>7)) p->yy += 1;
								else p->yy += 2;
								break;
							case 4:
								if (p->flag_move == 0 || (p->flag_move==1 && (p->xx>7 || p->yy<2) )) {
									p->xx += 1;
									p->yy -= 1;
								} else {
									p->xx += 2;
									p->yy -= 2;
								}
								break;
							case 5:
								if (p->flag_move == 0 || (p->flag_move==1 && p->yy<2)) p->yy -= 1;
								else p->yy -= 2;
								break;
						}
					}
				} else if (p->xx == field_size - 1) {
					if (p->yy == 0) {
						ran_move = 1 + rand() % 3;
						switch (ran_move) {
							case 1:
								if (p->flag_move == 0) p->xx -= 1;
								else p->xx -= 2;
								break;
							case 2:
								if (p->flag_move == 0) {
									p->xx -= 1;
									p->yy += 1;
								} else {
									p->xx -= 2;
									p->yy += 2;
								}
								break;
							case 3:
								if (p->flag_move == 0) p->yy += 1;
								else p->yy += 2;
								break;
						}
					} else if (p->yy == field_size - 1) {
						ran_move = 1 + rand() % 3;
						switch (ran_move) {
							case 1:
								if (p->flag_move == 0) p->yy -= 1;
								else p->yy -= 2;
								break;
							case 2:
								if (p->flag_move == 0) {
									p->xx -= 1;
									p->yy -= 1;
								} else {
									p->xx -= 2;
									p->yy -= 2;
								}
								break;
							case 3:
								if (p->flag_move == 0) p->xx -= 1;
								else p->xx -= 2;
								break;
						}
					} else if (p->yy > 0 && p->yy < field_size - 1) {
						ran_move = 1 + rand() % 5;
						switch (ran_move) {
							case 1:
								if (p->flag_move == 0 || (p->flag_move==1 && p->xx<2)) p->xx -= 1;
								else p->xx -= 2;
								break;
							case 2:
								if (p->flag_move == 0 || (p->flag_move==1 && (p->xx<2 || p->yy<2))) {
									p->xx -= 1;
									p->yy -= 1;
								} else {
									p->xx -= 2;
									p->yy -= 2;
								}
								break;
							case 3:
								if (p->flag_move == 0 || (p->flag_move==1 && p->yy<2)) p->yy -= 1;
								else p->yy -= 2;
								break;
							case 4:
								if (p->flag_move == 0 || (p->flag_move==1 && (p->xx<2 || p->yy>7))) {
									p->xx -= 1;
									p->yy += 1;
								} else {
									p->xx -= 2;
									p->yy += 2;
								}
								break;
							case 5:
								if (p->flag_move == 0 || (p->flag_move==1 && p->yy>7)) p->yy += 1;
								else p->yy += 2;
								break;
						}
					}
				} else if (p->xx > 0 && p->xx < field_size - 2 && (p->yy == 0 || p->yy == field_size - 1)) {
					if (p->yy == 0) {
						ran_move = 1 + rand() % 5;
						switch (ran_move) {
							case 1:
								if (p->flag_move == 0 || (p->flag_move==1 && p->xx>7)) p->xx += 1;
								else p->xx += 2;
								break;
							case 2:
								if (p->flag_move == 0 || (p->flag_move==1 && (p->xx>7 || p->yy>7))) {
									p->xx += 1;
									p->yy += 1;
								} else {
									p->xx += 2;
									p->yy += 2;
								}
								break;
							case 3:
								if (p->flag_move == 0 || (p->flag_move==1 && p->yy>7)) p->yy += 1;
								else p->yy += 2;
								break;
							case 4:
								if (p->flag_move == 0 || (p->flag_move==1 && (p->xx<2 || p->yy>7))) {
									p->xx -= 1;
									p->yy += 1;
								} else {
									p->xx -= 2;
									p->yy += 2;
								}
								break;
							case 5:
								if (p->flag_move == 0 || (p->flag_move==1 && p->xx<2)) p->xx -= 1;
								else p->xx -= 2;
								break;
						}
					} else if (p->yy == field_size - 1) {
						ran_move = 1 + rand() % 5;
						switch (ran_move) {
							case 1:
								if (p->flag_move == 0 || (p->flag_move==1 && p->xx<2)) p->xx -= 1;
								else p->xx -= 2;
								break;
							case 2:
								if (p->flag_move == 0 || (p->flag_move==1 && (p->xx<2 || p->yy<2))) {
									p->xx -= 1;
									p->yy -= 1;
								} else {
									p->xx -= 2;
									p->yy -= 2;
								}
								break;
							case 3:
								if (p->flag_move == 0 || (p->flag_move==1 && p->yy<2)) p->yy -= 1;
								else p->yy -= 2;
								break;
							case 4:
								if (p->flag_move == 0 || (p->flag_move==1 && (p->xx>7 || p->yy<2))) {
									p->xx += 1;
									p->yy -= 1;
								} else {
									p->xx += 2;
									p->yy -= 2;
								}
								break;
							case 5:
								if (p->flag_move == 0 || (p->flag_move==1 && p->xx>7)) p->xx += 1;
								else p->xx += 2;
								break;
						}
					}
				} else {
					ran_move = 1 + rand() % 8;
					if (p->flag_move == 1 && (p->xx == 1 || p->yy == 1 || p->xx == field_size - 2 || p->yy == field_size - 2)) {
						if (p->xx == 1 && p->yy == 1) while (ran_move == 1 || ran_move == 2 || ran_move == 6 || ran_move == 7 || ran_move == 8) ran_move = 1 + rand() % 8;
						else if (p->xx == 1 && (p->yy > 1 && p->yy < field_size - 2)) while (ran_move == 6 || ran_move == 7 || ran_move == 8)  ran_move = 1 + rand() % 8;
						else if (p->xx == 1 && p->yy == field_size - 2) while (ran_move == 4 || ran_move == 5 || ran_move == 6 || ran_move == 7 || ran_move == 8) ran_move = 1 + rand() % 8;
						else if (p->yy == field_size - 2 && (p->xx > 1 && p->xx < field_size - 2)) while (ran_move == 4 || ran_move == 5 || ran_move == 6) ran_move = 1 + rand() % 8;
						else if (p->xx == field_size - 2 && p->yy == field_size - 2) while (ran_move == 2 || ran_move == 3 || ran_move == 4 || ran_move == 5 || ran_move == 6) ran_move = 1 + rand() % 8;
						else if (p->xx == field_size - 2 && (p->yy > 1 && p->yy < field_size - 2)) while (ran_move == 2 || ran_move == 3 || ran_move == 4) ran_move = 1 + rand() % 8;
						else if (p->xx == field_size - 2 && p->yy == 1) while (ran_move == 1 || ran_move == 2 || ran_move == 3 || ran_move == 4 || ran_move == 8) ran_move = 1 + rand() % 8;
						else if (p->yy == 1 && (p->xx > 1 && p->xx < field_size - 2)) while (ran_move == 1 || ran_move == 2 || ran_move == 8) ran_move = 1 + rand() % 8;
					}
					switch (ran_move) {
						case 1:
							if (p->flag_move == 0) p->yy -= 1;
							else p->yy -= 2;
							break;
						case 2:
							if (p->flag_move == 0) {
								p->xx += 1;
								p->yy -= 1;
							} else {
								p->xx += 2;
								p->yy -= 2;
							}
							break;
						case 3:
							if (p->flag_move == 0) p->xx += 1;
							else p->xx += 2;
							break;
						case 4:
							if (p->flag_move == 0) {
								p->xx += 1;
								p->yy += 1;
							} else {
								p->xx += 2;
								p->yy += 2;
							}
							break;
						case 5:
							if (p->flag_move == 0) p->yy += 1;
							else p->yy += 2;
							break;
						case 6:
							if (p->flag_move == 0) {
								p->xx -= 1;
								p->yy += 1;
							} else {
								p->xx -= 2;
								p->yy += 2;
							}
							break;
						case 7:
							if (p->flag_move == 0) p->xx -= 1;
							else p->xx -= 2;
							break;
						case 8:
							if (p->flag_move == 0) {
								p->xx -= 1;
								p->yy -= 1;
							} else {
								p->xx -= 2;
								p->yy -= 2;
							}
							break;
					}
				}
				if (wolf_situation(field, rabit) == 1) {
					p->hunger -= 0.2;
					field[p->old_y][p->old_x].data = 0;
					p = p->next;
				} else try_move += 1;
				if (try_move >= 6) {
					p = p->next;
					try_move = 0;
				}
			}
		}
};

void start_field(struct field_data field[field_size][field_size]) {
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			field[i][j].data = 0;
			strcpy(field[i][j].symbol, " ");
			field[i][j].count = 0;
		}
	}
}

void prin_field(struct field_data field[field_size][field_size]) {
	for (int i = 0; i < field_size; i++) {
		std::cout << "  ";
		for (int j = 0; j < field_size; j++) {
			if (field[i][j].count <= 1) std::cout << "|" << field[i][j].symbol;
			else std::cout << "|" << field[i][j].symbol << field[i][j].count;
		}
		std::cout <<"|"<< std::endl;
	}
}

int wolf::count_wolf;

int main() {
	srand(time(NULL));
	int plant_live = 0, rabbit_move = 0, wolf_move = 0, key = 0;
	field_data field[field_size][field_size];
	start_field(field);
	plant pla=plant(field);
	rabbit rab=rabbit(field);
	wolf wol=wolf(field);
	pla.add_plant(field, 9);
	rab.rabbit_add(field, 9);
	wol.wolf_add(field, 9);
	pla.write(field);
	rab.write(field);
	wol.write(field);
	for (int c = 0; c < 30; c+=1) {
		system("CLS");
		if (plant_live == need_live_plant) {
			pla.add_plant(field, 10);
			plant_live = 0;
		} else plant_live += 1;
		prin_field(field);
		if (wolf_move == need_wolf_move) {
			wol.move(field, rab);
			wolf_move = 0;
		} else wolf_move += 1;
		if (rabbit_move == need_rabbit_move) {
			rab.move(field, pla);
			rabbit_move = 0;
		} else rabbit_move += 1;
		std::cout << std::endl << "             | " << std::endl << "             |" << std::endl << "             V " << std::endl << std::endl;
		pla.write(field);
		rab.write(field);
		wol.write(field);
		prin_field(field);
		std::cout << std::endl << std::endl << std::endl;
		_getch();
	}
	return 0;
}
