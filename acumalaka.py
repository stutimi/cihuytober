import random

def main():
    print("=" * 40)
    print("   SELAMAT DATANG DI GAME TEBAK ANGKA!   ")
    print("=" * 40)
    print("Saya sudah memilih angka antara 1 sampai 100.")
    print("Coba tebak kalau bisa! 😜\n")

    # Komputer memilih angka rahasia
    angka_rahasia = random.randint(1, 100)
    jumlah_tebakan = 0

    # Daftar respons lucu/galak
    respon_terlalu_rendah = [
        "Terlalu RENDAH! Memangnya angkanya di lantai?",
        "Naik lagi, dong! Masa segitu aja?",
        "Kurang... kurang... masih jauuuh!",
        "Hampir... tapi bohong. Naikin lagi!",
    ]
    
    respon_terlalu_tinggi = [
        "Ketinggian, bos! Mau sampai ke bulan?",
        "TURUN! Angkanya di bawah situ!",
        "Waduh, bablas... kebanyakan itu.",
        "Santai, jangan ngegas. Turunin dikit.",
    ]

    while True:
        # Minta input dari pengguna
        try:
            tebakan_str = input(f"Tebakan Anda (percobaan ke-{jumlah_tebakan + 1}): ")
            tebakan = int(tebakan_str)
            jumlah_tebakan += 1
        except ValueError:
            print("Hah? Itu bukan angka. Coba lagi yang benar!")
            continue

        # Periksa tebakan
        if tebakan < 1 or tebakan > 100:
            print("Woi, angkanya antara 1 dan 100 aja!")
            continue
            
        if tebakan < angka_rahasia:
            # Pilih respons acak dari daftar
            print(f"-> {random.choice(respon_terlalu_rendah)}\n")
        elif tebakan > angka_rahasia:
            # Pilih respons acak dari daftar
            print(f"-> {random.choice(respon_terlalu_tinggi)}\n")
        else:
            # Pengguna berhasil menebak
            print("\n" + "🎉" * 20)
            print(f"NAH, GITU DOANG! SELAMAT! Angkanya memang {angka_rahasia}.")
            print(f"Anda berhasil dalam {jumlah_tebakan} percobaan.")
            print("🎉" * 20)
            break

if __name__ == "__main__":
    main()
