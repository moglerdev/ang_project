#include <QApplication>

#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Qt wird instanziert mit QApplication, dabei werden Argumente �ber Parameter �berliefert
    Widget w; // Widget Klasse wird deklariert 
    w.show(); // Diese wird mit "show" angezeigt
    return a.exec(); // Betritt "main-event-lopp" und verweilt solange, bis vom Program "exit()" aufgerufen wird. Wenn das Programm �ber "exit()" geschlossen wird, wird 0 zur�ckgegeben.
}
