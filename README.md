![](https://habrastorage.org/webt/tg/up/ac/tgupacoharpo_hnm56b9ju6bfma.png)

**[по-русски]**

Функция **char * WiFiAuto(int timeout = 5000)** производит поиск **Wi-Fi**-сетей, а затем ищет в файловой системе **SPIFFS** соответствующий **файл-профиль** и подключается к выбранной сети. В случае успешного подключения функция возвращает **SSID** (имя сети), в противном случае возвращетс **NULL**.

**Файл-профиль** – это файл имя которого есть **SSID** + **расширение .wifi**, а содержимое файла есть пароль от сети.

Функция автоматически удаляет символ **0x0A**.

**[English]**

The **char * WiFiAuto (int timeout = 5000)** function searches **for Wi-Fi** networks and then searches **SPIFFS** for the corresponding **file of profile** in the file system and connects to the selected network . If the connection is successful, the function returns **SSID** (network name), otherwise **NULL** is returned.

**file of profile** is a file whose name is **SSID** + **.wifi extension**, and the contents of the file have a network password.

The function automatically deletes the character **0x0A**.