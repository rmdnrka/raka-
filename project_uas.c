#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct untuk menyimpan data anggota
typedef struct {
    char nama[50];
    char jenis_kelamin[10];
    union {
        char seni[50];
        char tarung[50];
    } fokus_bidang;
    char pilihan_fokus[10];
} Anggota;

// Fungsi untuk membuat anggota baru
Anggota* buatAnggota() {
    Anggota* anggota = (Anggota*)malloc(sizeof(Anggota));
    if (anggota == NULL) {
        printf("Memori tidak cukup.\n");
        exit(1);
    }

    printf("Masukkan nama: ");
    fgets(anggota->nama, sizeof(anggota->nama), stdin);
    strtok(anggota->nama, "\n"); // Menghapus karakter newline

    printf("Masukkan jenis kelamin (Pria/Wanita): ");
    fgets(anggota->jenis_kelamin, sizeof(anggota->jenis_kelamin), stdin);
    strtok(anggota->jenis_kelamin, "\n");

    printf("Pilih fokus bidang (Seni/Tarung): ");
    fgets(anggota->pilihan_fokus, sizeof(anggota->pilihan_fokus), stdin);
    strtok(anggota->pilihan_fokus, "\n");

    if (strcmp(anggota->pilihan_fokus, "Seni") == 0) {
        printf("Masukkan detail fokus seni: ");
        fgets(anggota->fokus_bidang.seni, sizeof(anggota->fokus_bidang.seni), stdin);
        strtok(anggota->fokus_bidang.seni, "\n");
    } else if (strcmp(anggota->pilihan_fokus, "Tarung") == 0) {
        printf("Masukkan detail fokus tarung: ");
        fgets(anggota->fokus_bidang.tarung, sizeof(anggota->fokus_bidang.tarung), stdin);
        strtok(anggota->fokus_bidang.tarung, "\n");
    } else {
        printf("Pilihan fokus tidak valid.\n");
        free(anggota);
        return NULL;
    }

    return anggota;
}

// Fungsi untuk mencetak data anggota
void tampilkanAnggota(Anggota* anggota) {
    if (anggota == NULL) {
        printf("Data anggota tidak ada.\n");
        return;
    }

    printf("\n--- Data Anggota ---\n");
    printf("Nama           : %s\n", anggota->nama);
    printf("Jenis Kelamin  : %s\n", anggota->jenis_kelamin);
    if (strcmp(anggota->pilihan_fokus, "Seni") == 0) {
        printf("Fokus Bidang   : Seni (%s)\n", anggota->fokus_bidang.seni);
    } else if (strcmp(anggota->pilihan_fokus, "Tarung") == 0) {
        printf("Fokus Bidang   : Tarung (%s)\n", anggota->fokus_bidang.tarung);
    }
}

// Fungsi untuk mengedit data anggota
void editAnggota(Anggota* anggota) {
    if (anggota == NULL) {
        printf("Data anggota tidak ada.\n");
        return;
    }

    printf("\n--- Edit Data Anggota ---\n");

    printf("Masukkan nama baru (kosongkan jika tidak ingin mengubah): ");
    char buffer[50];
    fgets(buffer, sizeof(buffer), stdin);
    if (strcmp(buffer, "\n") != 0) {
        strtok(buffer, "\n");
        strcpy(anggota->nama, buffer);
    }

    printf("Masukkan jenis kelamin baru (kosongkan jika tidak ingin mengubah): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (strcmp(buffer, "\n") != 0) {
        strtok(buffer, "\n");
        strcpy(anggota->jenis_kelamin, buffer);
    }

    printf("Pilih fokus bidang baru (Seni/Tarung, kosongkan jika tidak ingin mengubah): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (strcmp(buffer, "\n") != 0) {
        strtok(buffer, "\n");
        strcpy(anggota->pilihan_fokus, buffer);
        if (strcmp(anggota->pilihan_fokus, "Seni") == 0) {
            printf("Masukkan detail fokus seni baru: ");
            fgets(anggota->fokus_bidang.seni, sizeof(anggota->fokus_bidang.seni), stdin);
            strtok(anggota->fokus_bidang.seni, "\n");
        } else if (strcmp(anggota->pilihan_fokus, "Tarung") == 0) {
            printf("Masukkan detail fokus tarung baru: ");
            fgets(anggota->fokus_bidang.tarung, sizeof(anggota->fokus_bidang.tarung), stdin);
            strtok(anggota->fokus_bidang.tarung, "\n");
        }
    }
}

int main() {
    int pilihan;
    Anggota** daftarAnggota = NULL;
    int jumlah = 0;

    do {
        printf("\n ==Keanggotaan Pencak Silat==\n");
        printf("\n--- Menu Utama ---\n");
        printf("1. Tambah Anggota Baru\n");
        printf("2. Tampilkan Semua Anggota\n");
        printf("3. Edit Data Anggota\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar(); // Membersihkan buffer newline

        switch (pilihan) {
            case 1: {
                printf("Masukkan jumlah anggota baru: ");
                int tambahan;
                scanf("%d", &tambahan);
                getchar(); // Membersihkan buffer newline

                daftarAnggota = (Anggota**)realloc(daftarAnggota, (jumlah + tambahan) * sizeof(Anggota*));
                if (daftarAnggota == NULL) {
                    printf("Memori tidak cukup.\n");
                    exit(1);
                }

                for (int i = 0; i < tambahan; i++) {
                    printf("\n--- Input Data Anggota %d ---\n", jumlah + i + 1);
                    daftarAnggota[jumlah + i] = buatAnggota();
                }
                jumlah += tambahan;
                printf("Anggota baru berhasil ditambahkan!\n");
                break;
            }

            case 2:
                if (jumlah == 0) {
                    printf("Belum ada anggota yang terdaftar.\n");
                } else {
                    printf("\n--- Data Semua Anggota ---\n");
                    for (int i = 0; i < jumlah; i++) {
                        printf("\nAnggota ke-%d:\n", i + 1);
                        tampilkanAnggota(daftarAnggota[i]);
                    }
                }
                break;

            case 3:
                if (jumlah == 0) {
                    printf("Belum ada anggota yang terdaftar.\n");
                } else {
                    printf("Masukkan nomor anggota yang ingin diedit (1-%d): ", jumlah);
                    int nomor;
                    scanf("%d", &nomor);
                    getchar(); // Membersihkan buffer newline
                    if (nomor < 1 || nomor > jumlah) {
                        printf("Nomor anggota tidak valid.\n");
                    } else {
                        editAnggota(daftarAnggota[nomor - 1]);
                        printf("Data anggota berhasil diperbarui!\n");
                    }
                }
                break;

            case 4:
                printf("Keluar dari program.\n");
                for (int i = 0; i < jumlah; i++) {
                    free(daftarAnggota[i]);
                }
                free(daftarAnggota);
                break;

            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 4);
	return 0;
}
