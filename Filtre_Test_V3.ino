#include <ESP8266WiFi.h>

// WiFi Bilgileri
const char* ssid = "RANCHU-0718";
const char* password = "71s3L1-6";

// Röle Pinleri
int RolePin1 = D0;
int RolePin2 = D1;
int RolePin3 = D2;

// Eklenen Sensör Pinleri
int sensorPin1 = D6;
int sensorPin2 = D7;

// Röle Durumları
int RoleDeger1 = LOW;
int RoleDeger2 = LOW;
int RoleDeger3 = LOW;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // Röle Pinleri çıkış olarak ayarlanıyor
  pinMode(RolePin1, OUTPUT);
  pinMode(RolePin2, OUTPUT);
  pinMode(RolePin3, OUTPUT);
  digitalWrite(RolePin1, LOW);
  digitalWrite(RolePin2, LOW);
  digitalWrite(RolePin3, LOW);

  // Sensör Pinleri giriş olarak ayarlanıyor
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);

  // WiFi ağına bağlanma
  Serial.println();
  Serial.println();
  Serial.print("Baglanilan ag: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi baglanildi…");

  // Server başlatılıyor
  server.begin();
  Serial.println("Server baslatildi….");

  // NodeMCU IP adresi
  Serial.print("Baglanmak icin kullanilacak IP : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("Yeni cihaz baglandi");
  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  
  // Sensör verilerini oku
  int sensorValue1 = analogRead(sensorPin1);
  int sensorValue2 = analogRead(sensorPin2);

  // HTML içeriğini gönder
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>Filtre_Test_Tablo</title>");
  client.println("<style>");
  client.println("  table { border-collapse: collapse; width: 80%; }");
  client.println("  th, td { border: 1px solid black; padding: 8px; text-align: left; }");
  client.println("  button { margin-left: 10px; }");
  client.println("  .error { color: red; font-weight: bold; }");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h2>Filtre_Test_Tablo</h2>");
  client.println("<table id='myTable'>");
  client.println("  <thead>");
  client.println("  <tr>");
  client.println("      <th>Sira No</th>");
  client.println("      <th>Seri No</th>");
  client.println("      <th>L_L</th>");
  client.println("      <th>N_N</th>");
  client.println("      <th>PE_PE</th>");
  client.println("      <th>L_N</th>");
  client.println("      <th>L_PE</th>");
  client.println("      <th>N_PE</th>");
  client.println("      <th>TEST_SONUCU</th>");
  client.println("      <th>EK_NOT</th>");
  client.println("  </tr>");
  client.println("  </thead>");
  client.println("  <tbody id='tableBody'>");
  client.println("  <tr>");
  client.println("      <td>1</td>");
  client.println("      <td><input type=\"text\" id=\"seriNo_0\"></td>");
  client.println("      <td>" + String(sensorValue1) + "</td>"); // L_L Sütununa Yazılıyor
  client.println("      <td>" + String(sensorValue2) + "</td>"); // N_N Sütununa Yazılıyor
  client.println("      <td></td>");
  client.println("      <td></td>");
  client.println("      <td></td>");
  client.println("      <td></td>");
  client.println("      <td></td>");
  client.println("      <td></td>");
  client.println("  </tr>");
  client.println("  </tbody>");
  client.println("</table>");
  client.println("<button onclick='addRow()'>Yeni Satır Ekle</button>");
  client.println("<button onclick='exportToCSV()'>CSV Aktar</button>");
  client.println("<p id='uyariMesaji' class='error' style='display:none;'>Seri No giriniz!</p>");
  client.println("<script>");
  client.println(" let rowCount = document.getElementById('tableBody').rows.length;");
  client.println(" function addRow() {");
  client.println("  const tableBody = document.getElementById('tableBody');");
  client.println("  const lastRow = tableBody.rows[tableBody.rows.length - 1];");
  client.println("  const seriNoInput = lastRow.querySelector('input[id^=\"seriNo_\"]');");
  client.println("  const uyariMesaji = document.getElementById('uyariMesaji');");
  client.println("  if (!seriNoInput || seriNoInput.value.trim() === \"\") {");
  client.println("  uyariMesaji.style.display = \"block\";");
  client.println("  return;");
  client.println("  } else {");
  client.println("  uyariMesaji.style.display = \"none\";");
  client.println("  }");
  client.println("  rowCount++;");
  client.println("  const newRow = tableBody.insertRow();");
  client.println("  let cell0 = newRow.insertCell();");
  client.println("  let cell1 = newRow.insertCell();");
  client.println("  let cell2 = newRow.insertCell();"); 
  client.println("  let cell3 = newRow.insertCell();"); 
  client.println("  let cell4 = newRow.insertCell();");
  client.println("  let cell5 = newRow.insertCell();");
  client.println("  let cell6 = newRow.insertCell();");
  client.println("  let cell7 = newRow.insertCell();");
  client.println("  let cell8 = newRow.insertCell();");
  client.println("  let cell9 = newRow.insertCell();");
  client.println("  cell0.innerHTML = rowCount;");
  client.println("  cell1.innerHTML = '<input type=\"text\" id=\"seriNo_' + (rowCount - 1) + '\">';");
  client.println("  cell2.innerHTML = '" + String(analogRead(sensorPin1)) + "';"); 
  client.println("  cell3.innerHTML = '" + String(analogRead(sensorPin2)) + "';"); 
  client.println("  cell4.innerHTML = '';");
  client.println("  cell5.innerHTML = '';");
  client.println("  cell6.innerHTML = '';");
  client.println("  cell7.innerHTML = '';");
  client.println("  cell8.innerHTML = '';");
  client.println("  cell9.innerHTML = '';");
  client.println(" }");

  client.println(" function exportToCSV() {");
  client.println("  const table = document.getElementById('myTable');");
  client.println("  const rows = table.rows;");
  client.println("  let csvContent = \"data:text/csv;charset=utf-8,\";");
  client.println("  for (let i = 0; i < rows.length; i++) {");
  client.println("  const rowData = [];");
  client.println("  const cells = rows[i].cells;");
  client.println("  for (let j = 0; j < cells.length; j++) {");
  client.println("  let cellText = cells[j].innerText;");
  client.println("  const inputElement = cells[j].querySelector('input[type=\"text\"]');");
  client.println("  if (inputElement) {");
  client.println("  cellText = inputElement.value;");
  client.println("  }");
  client.println("  rowData.push(cellText);");
  client.println("  }");
  client.println("  csvContent += rowData.join(\",\") + \"\\r\\n\";");
  client.println("  }");
  client.println("  const encodedUri = encodeURI(csvContent);");
  client.println("  const link = document.createElement(\"a\");");
  client.println("  link.setAttribute(\"href\", encodedUri);");
  client.println("  link.setAttribute(\"download\", \"tablo_verisi.csv\");");
  client.println("  document.body.appendChild(link);");
  client.println("  link.click();");
  client.println("  document.body.removeChild(link);");
  client.println(" }");
  client.println(" document.addEventListener('DOMContentLoaded', function() {");
  client.println("  const tableBody = document.getElementById('tableBody');");
  client.println("  if (tableBody.rows.length > 0) {");
  client.println("  tableBody.rows[0].cells[0].innerHTML = 1;");
  client.println("  }");
  client.println(" });");
  client.println("</script>");
  client.println("<h2>Not</h2>");
  client.println("<p>1-Sayfayi yenilediginizde ve kapattiginizda veriler gitmektedir. Bu yuzden kapatmadan once csv aktariniz.</p>");
  client.println("</body>");
  client.println("</html>");

  delay(100);
  Serial.println("Client bağlantı kapatıldı");
  Serial.println("");
}
