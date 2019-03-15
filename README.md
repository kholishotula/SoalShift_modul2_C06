# SoalShift_modul2_C06

Kholishotul Amaliah   05111740000030<br>
Nandha Himawan        05111740000180

1. Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

Langkah-langkah :

- Inisialisasi variabel
```
DIR *current;
struct dirent *temp;
char *lama;
char baru[200];
char dirlama[100];
```
current untuk menyimpan direktori yang sedang dicek <br>
temp adalah struct dirent untuk menyimpan file yang dicek dalam bentuk struct  <br>
lama adalah string untuk menyimpan nama file lama <br>
baru adalah string untuk menyimpan direktori dan nama file baru <br>
dirlama adalah string untuk menyimpan direktori file lama <br>

-	Membuka direktori file dan menyimpan direktori tersebut
```
current = opendir("/home/maya/sisop/modul2/Prak2/");
strcpy(dirlama, "/home/maya/sisop/modul2/Prak2/");
```
-	Loop untuk mengecek semua file yang ada di direktori tersebut. Jika file tersebut berekstensi .png, maka tambahkan nama file (lama) tersebut ke array untuk nama file baru (baru) yang sebelumnya telah berisi /home/maya/modul2/gambar/. Kemudian hapus 4 char terakhir (.png) dan tambahkan “_grey.png” pada array nama file baru (baru). Lalu, rename file tersebut (dirlama) ke direktori dengan nama file baru (baru)
```
while( (temp = readdir(current)) != NULL)
{
      int length = strlen(temp->d_name);
      lama = temp->d_name;
      if(lama[length-4] == '.' && lama[length-3] == 'p' && lama[length-2] == 'n' && lama[length-1] == 'g')
      {
           strcpy(baru, "/home/maya/modul2/gambar/");
           strcat(baru, lama);
           length = strlen(baru);
           baru[length-4] = '\0';
           strcat(baru, "_grey.png");
           strcat(dirlama, lama);
           rename(dirlama, baru);
       }
}
```
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
```
closedir(current);
```
2. Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

Langkah-langkah : <br>

-	Inisialisasi variabel
```
struct stat elen;
char dir[100];
strcpy(dir, "/home/maya/sisop/modul2/Prak2/hatiku/elen.ku");
```
elen adalah variabel untuk menyimpan status dari file dalam bentuk struct <br>
dir adalah string untuk menyimpan nama file elen.ku dan path nya

-	Jalankan stat untuk mengetahui status file elen.ku
```
stat(dir, &elen);
```
-	Dapatkan id owner dan group
```
struct passwd *owner = getpwuid(elen.st_uid);
struct group *group = getgrgid(elen.st_gid);
```
-	Dapatkan nama owner dan group
```
char owner_name[100];
strcpy(owner_name, owner->pw_name);
char group_name[100];
strcpy(group_name, group->gr_name);
```
-	Cek apakah nama owner dan nama group adalah www-data. Jika ya, maka ubah permission menjadi 777, lalu hapus file elen.ku setiap 3 detik
```
char data[100];
strcpy(data, "www-data");
if(strcmp(owner_name, data)==0 && strcmp(group_name, data)==0)
{
        chmod(dir, 0777);
        remove(dir);
        sleep(3);
}
```
3. Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak file zip tersebut.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
Catatan:  
- Gunakan fork dan exec.
- Gunakan minimal 3 proses yang diakhiri dengan exec.
- Gunakan pipe
- Pastikan file daftar.txt dapat diakses dari text editor

Langkah - langkah :<br>
unzip file dengan child proccess pertama, 
```
    if(child1 == 0){
      execl("/usr/bin/unzip","unzip", "campur2.zip", NULL);
    }
```
dapat kan list dalam folder tersebut dengan child proccess kedua, 
```
        if(child2==0){
          close(p1[0]);
          close(p1[2]);
          close(p1[3]);
          dup2(p1[1], STDOUT_FILENO);
          close(p1[1]);
          execl("/bin/ls", "ls" ,"campur2", NULL);
        }
```
ambil yang ekstensi nya .txt saja dengan grep pada child proccess ketiga
```
            if(child3==0){
              close(p1[1]);
              dup2(p1[0],STDIN_FILENO);
              close(p1[0]);

              close(p1[2]);
              dup2(p1[3],STDOUT_FILENO);
              close(p1[3]);
              execl("/bin/grep", "grep" ,".txt$", NULL);
            }
```
tuliskan outputnya kedalam file daftar.txt dengan parent proccess dari child proccess ketiga
```
else{
              close(p1[1]);
              close(p1[0]);
              close(p1[3]);
              int x = read(p1[2],isi,sizeof(isi));
              close(p1[2]);
              FILE* output;
              output = fopen("daftar.txt","w+");
              fputs(isi,output);
              fclose(output);
            }
```

4. Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).<br>
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:<br>
File makan_enak.txt terakhir dibuka pada detik ke-1<br>
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan: 
- dilarang menggunakan crontab
- Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

Langkah - langkah :<br>
untuk mendapatkan waktu saat file di akses menggunakan :
```
    struct stat detail;
    stat(nama, &detail); 
```
lalu untuk mendapatkan selisih antara waktu akses file dengan waktu saat ini adalah,
```
    long int diff = t - detail.st_atime;
```
untuk membuat file makan_sehat#.txt ketika selisih waktunya <=30 detik adalah,
```
    if(diff<=30){
        int i = 1;
        while(1){
        char newname[500000]="makan_sehat.txt";
        sprintf(newname,"makan_sehat%d.txt",i);
        if(!(find=fopen(newname, "r"))){
            FILE* makenew = fopen(newname,"w");
            fclose(makenew);break;
        }
          i++;
        }}

```

5. Kerjakan poin a dan b di bawah:<br>
a. Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log<br>
Ket:<br>
Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]<br>
Per menit memasukkan log#.log ke dalam folder tersebut<br>
‘#’ : increment per menit. Mulai dari 1<br>
b. Buatlah program c untuk menghentikan program di atas.<br>
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

Langkah - langkah :<br>
untuk mendapatkan waktu saat ini dan membuatnya dalam format yang diminta adalah,
```
        time_t timer = time(NULL);
        strftime(dateTime, 20, "%d:%m:%Y-%H:%M", localtime(&timer));
```

untuk membuat folder,
```
        sprintf(dirfile,"/home/nandha/log/%s", dateTime);
        mkdir(dirfile,ACCESSPERMS);
```
untuk membuat file log#.log didalam folder yang telah dibuat tersebut :
```
      sprintf(loglog, "/log%d.log.txt",i);
      strcpy(filename,dirfile);
      strcat(filename,loglog);
      in = fopen(syslog, "r");
      out = fopen(filename,"w+");
     
    while((fgets(isi,sizeof(isi),in))!=NULL) {
        fputs(isi,out);
    }
    fclose(in);
    fclose(out);
```
lalu program untuk menghentikan dari program diatas adalah, 
```
    FILE *getPIDS;
    char line[130];
    getPIDS = popen("pidof /home/nandha/Documents/soal5/soal5","r");
    if(fgets(line,sizeof line,getPIDS)) {
            int pid = atoi(line);
            printf("KILL PID: %d\n",pid);
            kill(pid,SIGKILL);
    }

```
