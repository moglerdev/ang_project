#include <QApplication>

#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Qt wird instanziert mit QApplication, dabei werden Argumente über Parameter überliefert
    Widget w; // Widget Klasse wird deklariert 
    w.show(); // Diese wird mit "show" angezeigt
    return a.exec(); // Betritt "main-event-lopp" und verweilt solange, bis vom Program "exit()" aufgerufen wird. Wenn das Programm über "exit()" geschlossen wird, wird 0 zurückgegeben.
}
