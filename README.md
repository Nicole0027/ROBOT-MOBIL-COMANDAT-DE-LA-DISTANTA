# ROBOT-MOBIL-COMANDAT-DE-LA-DISTANTA

Configurare aplicație Android:<br />
  1. Instalare Android Studio<br />
  2. Instalare Java Developement Kit<br />
  3. Clonare Repo "ROBOT-MOBIL-COMANDAT-DE-LA-DISTANTA" cu comanda: <br />
     ````
     git clone https://github.com/Nicole0027/ROBOT-MOBIL-COMANDAT-DE-LA-DISTANTA.git
      ````
  4. Se deschide folder-ul cu proiectul prin Android Studio
  5. Este necesar un emulator instalat sau un telefon cu android
  6. Se apasa "Build" si "Run"



Configurare robot: <br />
  1. Instalare Arduino IDE<br />
  2. Se scot pinii de Rx si Tx de la modulul Bluetooth<br />
  3. Se incarca codul pe placa Arduino prin IDE din fiserul "Remote_control_code.ino"<br />



Pasii obligatorii pentru a controla masina:<br />
  1. Se activeaza WI-FI si Bluetooth
  2. Dupa incarcarea aplicatiei pe telefon, aceasta se acceseaza si se introduc<br />
credentialele codului, daca nu exista se merge in fereastra de inregistrare si se <br />
creeaza un cont.
  3. Dupa introducerea credentialelor se apasa pe butonul de conectare pentru ca<br />
aplicatia sa se conecteze la robot
  4. Se alege viteza cu care acesta sa se miste
  5. Se apasa pe butoanele cu sageti pentru a misca masinuta


Pasii pentru a pune masina sa urmareasca linia:
  1. Se incarca codul pe placa Arduino prin IDE din fisierul "Line_following_code.ino"<br />
  2. Se pune masina pe traseul stabilit cu senzorul de reflectivitate deasupra liniei<br />
  3. Se misca senzorul deasupra liniei in stanga si in dreapta pentru a trece pe deasupra liniei<br />
fiecare senzor de pe banda de senzori
  
     
