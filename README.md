# Micromouse Robot Wizualizer
Projekt robota Micromouse wraz z algorytmami przeszukiwania labiryntu oraz wizualizacji na wyświetlaczu LCD i w oprogramowaniu RViZ.

---

## Opis projektu
Projekt składa się z dwóch projektów:
1. Projekt robota Micromouse - odpowiada za oprogramowanie do stworzonego robota micromouse. Składają się na niego funkcje odpowiedzialne za ruch robota, odczyt danych z czujników, odczyt danych z enkoderów oraz algorytmy odpowiedzialne za przeszukiwanie labiryntu, a następnie znalezienie w nim najkrótszej ścieżki i przejechanie jej.
2. Projekt wizualizacji robota micromouse - składają się na niego funkcje zaimplementowane z oprogramowaniu robota odpowiedzialne za komunikację z wyświetlaczem LCD znajdującym się na użytej płytce (STM32F429I-DISC1) i rysowanie na niej poznawanego labiryntu wraz z informacjami o stanie robota i jego aktualej pozycji w labiryncie. Druga część projektu znajduje się w folderze [ROS_RVIZ](/ROS_RVIZ) i odpowiada ona za wizualizację robota wraz z labiryntem na żywo w oprogramowaniu RViZ. Jest to możliwe dzięki połączeniu bluetooth z robotem.

---

## Efekt końcowy
### Robot

<img src=/docs/imgs/robot.jpg width="700">

### Wizualizacji w oprogramowaniu RViZ

<img src=/docs/imgs/rviz.png width="700">

### Wyświetlacz LCD robota

<img src=/docs/imgs/lcd.png width="700">

### Schemat elektroniczny
<img src=/docs/imgs/electric_diagram.png width="700">

---

### Uruchomienie części wizualizacyjnej
Aby uruchomić część 2 projektu należy mieć zainstalowane oprogramowanie ROS i pakiet RViZ oraz wykonać następujące kroki:
1. uruchom oprogowamowanie ROS
```shell
$ roscore
```
2. w nowej konsoli (nr. 2) uruchom program komunikujący się z programem RViZ i skryptem bluetooth
```shell
$ rosrun using_markers basic_shapes
```
3. w kolejnej konsoli (nr. 3) uruchom skrypt łączący się z modułem bluetooth
```shell
$ rosrun using_markers publisher_node.py
```
4. w kolejnej konsoli (nr. 4) uruchom program RViZ
```shell
$ rviz rviz
```
5. postępuj z instrukcjami widocznymi po uruchomieniu skryptu w konsoli nr. 3

