# SoalShift_modul2_C06

Kholishotul Amaliah   05111740000030<br>
Nandha Himawan        05111740000180

1. Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

Langkah-langkah :

- Inisialisasi variabel

> DIR *current; <br>
struct dirent *temp; <br>
char *lama; <br>
char baru[200]; <br>
char dirlama[100];

current untuk menyimpan direktori yang sedang dicek <br>
temp adalah struct dirent untuk menyimpan file yang dicek dalam bentuk struct  <br>
lama adalah string untuk menyimpan nama file lama <br>
baru adalah string untuk menyimpan direktori dan nama file baru <br>
dirlama adalah string untuk menyimpan direktori file lama <br>

-	Membuka direktori file dan menyimpan direktori tersebut

> current = opendir("/home/maya/sisop/modul2/Prak2/"); <br>
strcpy(dirlama, "/home/maya/sisop/modul2/Prak2/");

-	Loop untuk mengecek semua file yang ada di direktori tersebut. Jika file tersebut berekstensi .png, maka tambahkan nama file (lama) tersebut ke array untuk nama file baru (baru) yang sebelumnya telah berisi /home/maya/modul2/gambar/. Kemudian hapus 4 char terakhir (.png) dan tambahkan “_grey.png” pada array nama file baru (baru). Lalu, rename file tersebut (dirlama) ke direktori dengan nama file baru (baru)

> if(current) <br>
{ <br>
while( (temp = readdir(current)) != NULL) <br>
{ <br>
        int length = strlen(temp->d_name); <br>
        lama = temp->d_name; <br>
        if(lama[length-4] == '.' && lama[length-3] == 'p' && lama[length-2] == 'n' && lama[length-1] == 'g') <br>
        { <br>
            strcpy(baru, "/home/maya/modul2/gambar/"); <br>
            strcat(baru, lama); <br>
            length = strlen(baru); <br>
            baru[length-4] = '\0'; <br>
            strcat(baru, "_grey.png"); <br>
            strcat(dirlama, lama); <br>
            rename(dirlama, baru); <br>
            memset(baru, 0, 200); <br>
        } <br>
} <br>
}

Contoh ilustrasi : <br>
dirlama = /home/maya/sisop/modul2/Prak2/ <br>
--ada file dalam direktori tersebut <br>
temp = struct dirent file “fileku.png” <br>
length = 11 <br>
lama = fileku.png <br>
----masuk kondisi if, karena file berekstensi .png <br>
baru = /home/maya/modul2/gambar/ <br>
baru = /home/maya/modul2/gambar/fileku.png <br>
length = 36 <br>
baru = /home/maya/modul2/gambar/fileku <br>
baru = /home/maya/modul2/gambar/fileku_grey.png <br>
dirlama = /home/maya/sisop/modul2/Prak2/fileku.png <br>
dilakukan rename /home/maya/sisop/modul2/Prak2/fileku.png /home/maya/modul2/gambar/fileku_grey.png <br>
-	Setelah itu, tutup direktori tersebut

> closedir(current);

2. Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

3. Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak file zip tersebut.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
Catatan:  
- Gunakan fork dan exec.
- Gunakan minimal 3 proses yang diakhiri dengan exec.
- Gunakan pipe
- Pastikan file daftar.txt dapat diakses dari text editor

4. Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan: 
- dilarang menggunakan crontab
- Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

5. Kerjakan poin a dan b di bawah:
a. Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
Per menit memasukkan log#.log ke dalam folder tersebut
‘#’ : increment per menit. Mulai dari 1
b. Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

