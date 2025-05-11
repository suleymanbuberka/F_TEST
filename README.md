Filtre testi için hazırlandı. 
Devre şeması ve kod için TİNKERCAD LİNKİ : (https://www.tinkercad.com/things/kpA9Tk3IvE5-filtretest?sharecode=OSShi1-xc7GDn3jHb5tRiEhitsVtc03IHMNfYxJ07UA)
F_Test_V1  dosyası ile arduinoya yüklenebilir. Seri monitör üzerinden 5 saniye aralıklarla veri gönderirir. 
Sistem Line-line, line-nötr, line-toprak arasındaki bağlantıda herhangi bir problem olmadan çalışıyor. Fakat Line-nötr kısa devre iken 1 değerini verirken nötr-line arası kısa devre olduğıunda line - nötürü 1 çeviriyor. Bu koşul da bir tarafın nötürn açık devre olmasıyla oluyor. Bu durumda N-n yine 0 0 verdiği için sistem yine çalışmış sayılır. 


![image](https://github.com/user-attachments/assets/24ca3614-2b20-41b0-a1f6-5613ae36e505)
