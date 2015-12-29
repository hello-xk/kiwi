#include <QTextStream>
#include <QThread>
#include <QObject>
#include <QtCore/QCoreApplication>

class tcConsoleThrd;
class ConsoleInput;
class tcPlayApp;

class tcConsoleThrd : public QThread
{
public:
    tcConsoleThrd  (QObject *parent);
    void     run   ();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

    QTextStream ts;
};

bool tcConsoleThrd::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        //QKeyEvent base QtGui      
        qDebug("Ate key press %d", 1);
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

tcConsoleThrd::tcConsoleThrd (QObject *parent) :
ts(stdin), 
QThread (parent)
{
    ts.device()->installEventFilter(this);
}

void tcConsoleThrd::run ()
{
    while (1)
    {
        printf("kiwi$ ");
        QChar ch = ts.device()->getch();
        /*if (temp == "quit")
        {
            QEvent *ce = new QEvent (QEvent::Quit);
            QCoreApplication::postEvent (QCoreApplication::instance(), ce); 
            return;
        }*/
        printf ("%s", qPrintable (ch));
    }
}


class ConsoleInput : public QObject
{
    //Q_OBJECT
public:
    ConsoleInput(QObject *parent);
    ~ConsoleInput();
    tcConsoleThrd  *m_thread;
};

ConsoleInput::ConsoleInput (QObject *parent) : 
QObject(parent)
{
    m_thread = new tcConsoleThrd (this);
    m_thread->run();
}

ConsoleInput::~ConsoleInput() 
{
    delete m_thread;
}


class tcPlayApp : public QCoreApplication
{
public:
    tcPlayApp ( int & argc, char ** argv);
};


tcPlayApp::tcPlayApp ( int & argc, char ** argv)
: QCoreApplication (argc, argv)
{
    setApplicationName("Play App");
    setOrganizationName("Acme");
    setObjectName ("tcPlayApp");
}


#include "main.moc"
int main(int argc, char *argv[])
{
    printf ("Howdy\n");

    tcPlayApp a(argc, argv);
    ConsoleInput cn (&a);
    return a.exec();
}
