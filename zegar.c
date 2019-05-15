#include <io.h>
#include <stdio.h>
#include <stdlib.h>
void sekundnik();
void wyswietlanie();
void wyswgodz();
void wyswdaty();
void prz1ctrl();
void prz1funk();
void prz2ctrl();
void prz2funk();
void kalendarz();
void zmianagodziny();
void zmianadaty();
void wyswzmianygodz();
void wyswzmianydaty();
int tab[] = { 0b0111111,0b0000110,0b1011011,0b1001111,0b1100110,0b1101101,0b1111101,0b0000111,0b1111111,0b1101111,
0b10111111,0b10000110,0b11011011,0b11001111,0b11100110,0b11101101,0b11111101,0b10000111,0b11111111,0b11101111,0b00000000 };
int licznik = 0, s = 50, m = 59, h = 23, d = 1, mies = 1, y = 18;
int w1, w2, w3, w4, w5, w6;
int liczprz1 = 0;
int prz1 = 0, prz2 = 0;
int prz1flaga = 0, prz1czas = 0, prz1koncowy = 0;
int prz2flaga = 0;
int mode = 0, modeostatnie;
int pozycjagodziny = 0, pozycjadaty = 0;
int miganiekropek = 0, kropa = 0;
int miganiestalych = 0;


int main() {
	//	alt_putstr("Start\n");
	//	int t = IORD(PIO_TRIGGER_BASE, 0);
	while (1) {
		//		while (IORD(PIO_TRIGGER_BASE, 0) == t) { /* --- */ };
		//		t = IORD(PIO_TRIGGER_BASE, 0);

		//		prz1=IORD(PIO_KEYA_BASE,0);
		//		prz2=IORD(PIO_KEYB_BASE,0);
		switch (prz1) {
		case 1:
			prz1funk();
			break;
		default:
			prz1flaga = 0;
			break;
		}
		switch (prz2) {
		case 1:
			prz2funk();
			break;
		default:
			prz2flaga = 0;
			break;
		}
		mode = 0;
		switch (mode) {
		case 0:				//pokazany czas 
			sekundnik();
			wyswgodz();
			break;
		case 1:				//pokazana data
			sekundnik();
			wyswdaty();
			break;
		case 2:
			wyswzmianygodz();
			break;
		case 3:
			wyswzmianydaty();
			break;
		default:
			//			alt_putstr("error\n");
			break;
		}
		//		IOWR(PIO_LED_BASE, 0, i);
	};
	return 0;
}

void prz1funk() {
	switch (prz1flaga) {
	case 0:
		switch (mode) {
		case 0:
			mode = 1;
			break;
		case 1:
			mode = 0;
			break;
		case 2:
			zmianagodziny();
			break;
		case 3:
			zmianadaty();
			break;
		default:
			break;
		}
		prz1flaga = 1;
		break;
	default:
		break;
	}
}

void prz2funk() {
	modeostatnie = mode;
	switch (mode) {
	case 0:
		mode = 2;
		break;
	case 1:
		mode = 3;
		break;
	case 2:
		switch (pozycjagodziny) {
		case 0:
			pozycjagodziny = 1;
			break;
		default:
			pozycjagodziny = 0;
			mode = 0;
			break;
		}
		break;
	case 3:
		switch (pozycjadaty) {
		case 0:
			pozycjadaty = 1;
			break;
		case 1:
			pozycjadaty = 2;
			break;
		default:
			pozycjadaty = 0;
			mode = 1;
			break;
		}
		break;
	default:
		//tutaj zmiana zmiany;
		break;
	}
}

void prz1ctrl() {
	prz1czas = 1;
	while (prz1) {
		switch (liczprz1) {
		case 400:
			prz1czas = 2;
			liczprz1++;
			break;
		default:
			liczprz1++;
			break;
		}
	}
	prz1koncowy = prz1czas;
	prz1flaga = 0;
	prz1czas = 0;
}

void prz2ctrl() {
	//cos
}

void zmianagodziny() {
	switch (pozycjagodziny) {
	case 0:
		switch (h) {
		case 23:
			h = 0;
			break;
		default:
			h++;
			break;
		}
		break;
	default:
		switch (m) {
		case 59:
			m = 0;
			break;
		default:
			m++;
			break;
		}
		break;

	}
}

void zmianadaty() {
	switch (pozycjadaty) {
	case 0:
		switch (mies) {
		case 2:
			switch (d) {
			case 28:
				d = 1;
				break;
			default:
				d++;
				break;
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			switch (d) {
			case 30:
				d = 1;
				break;
			default:
				d++;
				break;
			}
			break;

		default:
			switch (d) {
			case 31:
				d = 1;
				break;
			default:
				d++;
				break;
			}
			break;
		}
		break;
	case 1:
		switch (mies) {
		case 12:
			mies = 1;
			break;
		default:
			mies++;
			break;
		}
		break;
	default:
		switch (y) {
		case 99:
			y = 0;
			break;
		default:
			y++;
			break;
		}
		break;
	}
}







/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void wyswietlanie() {
	/*	IOWR(PIO_F_BASE, 0, tab[w6] ^ 0xFF);
	IOWR(PIO_E_BASE, 0, tab[w5] ^ 0xFF);
	IOWR(PIO_D_BASE, 0, tab[w4] ^ 0xFF);
	IOWR(PIO_C_BASE, 0, tab[w3] ^ 0xFF);
	IOWR(PIO_B_BASE, 0, tab[w2] ^ 0xFF);
	IOWR(PIO_A_BASE, 0, tab[w1] ^ 0xFF);
	*/
	printf("%d%d:%d%d:%d%d\n", w6, w5, w4, w3, w2, w1);
}

void wyswgodz() {
	w1 = s % 10;
	w2 = s / 10;
	w3 = m % 10;
	w4 = m / 10;
	w5 = h % 10;
	w6 = h / 10;
	switch (miganiekropek) {
	case 1:
		kropa = 1;
		break;
	case 50:
		kropa = 0;
		break;
	case 199:
		miganiekropek = 0;
		break;
	default:
		break;
	}
	miganiekropek++;
	switch (kropa) {
	case 0:
		break;
	case 1:
		w1 = w1 + 10;
		w3 = w3 + 10;
		w5 = w5 + 10;
		break;
	default:
		break;
	}
	wyswietlanie();
}

void wyswdaty() {
	w5 = (d % 10) + 10;
	w6 = d / 10;
	w3 = (mies % 10) + 10;
	w4 = mies / 10;
	w1 = y % 10;
	w2 = y / 10;
	wyswietlanie();
}

void wyswzmianygodz() {
	switch (miganiestalych) {
	case 1:
		kropa = 1;
		miganiestalych++;
		break;
	case 100:
		kropa = 0;
		miganiestalych++;
		break;
	case 199:
		miganiestalych = 0;
		break;
	default:
		miganiestalych++;
		break;
	}
	switch (kropa) {
	case 0:
		switch (pozycjagodziny) {
		case 0:
			w5 = h % 10;
			w6 = h / 10;
			w4 = 20;
			w3 = 20;
			w2 = 20;
			w1 = 20;
			break;
		case 1:
			w6 = 20;
			w5 = 20;
			w4 = m / 10;
			w3 = m % 10;
			w2 = 20;
			w1 = 20;
			break;
		default:
			break;
		}
		break;
	case 1:
		w1 = s % 10;
		w2 = s / 10;
		w3 = m % 10;
		w4 = m / 10;
		w5 = h % 10;
		w6 = h / 10;
		break;
	default:
		break;
	}
	wyswietlanie();
}

void wyswzmianydaty() {
	switch (miganiestalych) {
	case 1:
		kropa = 1;
		miganiestalych++;
		break;
	case 100:
		kropa = 0;
		miganiestalych++;
		break;
	case 199:
		miganiestalych = 0;
		break;
	default:
		miganiestalych++;
		break;
	}
	switch (kropa) {
	case 0:
		switch (pozycjadaty) {
		case 0:
			w5 = (d % 10) + 10;
			w6 = d / 10;
			w3 = 20;
			w4 = 20;
			w1 = 20;
			w2 = 20;
			break;
		case 1:
			w5 = 20;
			w6 = 20;
			w3 = (mies % 10) + 10;
			w4 = mies / 10;
			w1 = 20;
			w2 = 20;
			break;
		case 2:
			w5 = 20;
			w6 = 20;
			w3 = 20;
			w4 = 20;
			w1 = y % 10;
			w2 = y / 10;
			break;
		default:
			break;
		}
		break;
	case 1:
		w5 = (d % 10) + 10;
		w6 = d / 10;
		w3 = (mies % 10) + 10;
		w4 = mies / 10;
		w1 = y % 10;
		w2 = y / 10;
		break;
	default:
		break;
	}
	wyswietlanie();
}

void sekundnik() {
	switch (licznik) {
	case 199:
		switch (s) {
		case 59:
			s = 0;
			switch (m) {
			case 59:
				m = 0;
				switch (h) {
				case 23:
					h = 0;
					kalendarz();
					break;

				default:
					h++;
					break;
				}
				break;
			default:m++;
				break;
			}
			break;
		default:s++;
			break;
		}
		licznik = 0;
		break;
	default:
		licznik++;
		break;
	}
}

void kalendarz() {
	//	printf("%d...%d...%d\n", d, mies, y);
	switch (mies) {
	case 2:
		switch (d) {
		case 28:
			d = 1;
			mies++;
			break;
		default:
			d++;
			break;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		switch (d) {
		case 30:
			d = 1;
			mies++;
			break;
		default:
			d++;
			break;
		}
		break;
	
	default:
		switch (d) {
		case 31:
			d = 1;
			mies++;
			break;
		default:
			d++;
			break;
		}
		break;
	}
	switch (mies) {
	case 13:
		mies = 1;
		y++;
		break;
	default:
		break;
	}
	switch (y) {
	case 100:
		y = 0;
		break;
	dafault:
		break;
	}

}